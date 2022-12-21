/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

#include <linux/mman.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/version.h>
#include <linux/slab.h>
#include "hi_drv_dev.h"
#include "drv_media_mem.h"
#include "drv_mmz_ioctl.h"
#include "hi_kernel_adapt.h"

#ifdef MMB_SHARE_SUPPORT
#define MMB_SHARE_DEBUG    0

#define MMB_TYPE_NOMAL     0   // nomal, not share and not copy
#define MMB_TYPE_BASE      1   // share and new mmb information
#define MMB_TYPE_COPY      2   // share and copy mmb information

#define MMB_SHARE_NONE     0 
#define MMB_SHARE_SHM      1
#define MMB_SHARE_COM      2

static LIST_HEAD(mmb_share_list); 
static HI_DECLARE_MUTEX(share_list_lock);
#define SHARE_LIST_LOCK    down(&share_list_lock)
#define SHARE_LIST_UNLOCK  up(&share_list_lock)

static unsigned long share_com_phy_start = 0;
static int           share_com_size      = 0;
#else
#define MMB_SHARE_DEBUG    0
#define SHARE_LIST_LOCK      
#define SHARE_LIST_UNLOCK    
#endif

#define error(s...)    do{ PRINTK_CA(KERN_ERR     "DRV_MMZ:%d.%s.%d: ", current->tgid, __FUNCTION__, __LINE__); PRINTK_CA(s); }while(0)
#define warning(s...)  do{ PRINTK_CA(KERN_WARNING "DRV_MMZ:%d.%s.%d: ", current->tgid, __FUNCTION__, __LINE__); PRINTK_CA(s); }while(0)
#if MMB_SHARE_DEBUG
#define info(s...)     do{ PRINTK_CA(KERN_INFO    "DRV_MMZ:%d.%s.%d: ", current->tgid, __FUNCTION__, __LINE__); PRINTK_CA(s); }while(0)
//#define info(s...)     do{ HI_PRINT(KERN_INFO    "DRV_MMZ:%d.%s.%d: ", current->tgid, __FUNCTION__, __LINE__); HI_PRINT(s); }while(0)
#else
#define info(s...)     
#endif

/****************************fops*********************************/

struct mmz_userdev_info {
	pid_t pid;
	pid_t mmap_pid;
	struct semaphore sem;
	struct list_head list;
};

static int mmz_flush_dcache_mmb(struct mmb_info *pmi)
{
	hil_mmb_t *mmb;
	unsigned long flags;

	DEFINE_SPINLOCK(cache_lock);

	if (pmi == NULL)
		return -EINVAL;

	mmb = pmi->mmb;
	if (mmb == NULL || pmi->map_cached == 0){
        error("%s->%d,error![%ld,%d]\n", __func__, __LINE__, (unsigned long) mmb, pmi->map_cached);
		return -EINVAL;
	}
	spin_lock_irqsave(&cache_lock, flags);

	/* flush l1 cache, use vir addr */	
	__cpuc_flush_dcache_area((void *)pmi->mapped, pmi->size);
	/* flush l2 cache, use phy addr */
	outer_flush_range(mmb->phys_addr, mmb->phys_addr + mmb->length);

	spin_unlock_irqrestore(&cache_lock, flags);

	return 0;
}

static int mmz_flush_dcache_all(void)
{
	/* flush l1 all cache */
#ifdef CONFIG_SMP
	on_each_cpu((smp_call_func_t)__cpuc_flush_kern_all, NULL, 1);
#else
	__cpuc_flush_kern_all();
#endif
	/* flush l2 all cache */
	outer_flush_all();
	return 0;
}

int mmz_userdev_open(struct inode *inode, struct file *file)
{
	struct mmz_userdev_info *pmu;

	pmu = kmalloc(sizeof(*pmu), GFP_KERNEL);
	if(pmu ==NULL) {
		error("alloc mmz_userdev_info failed!\n");
		return -ENOMEM;
	}
	pmu->pid = current->tgid;
	pmu->mmap_pid = 0;
	HI_INIT_MUTEX(&pmu->sem);
	INIT_LIST_HEAD(&pmu->list);

	file->private_data = (void*)pmu;

	return 0;
}

static int ioctl_mmb_alloc(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *new_mmbinfo;
	hil_mmb_t *mmb;

	mmb = hil_mmb_alloc(pmi->mmb_name, pmi->size, pmi->align, pmi->gfp, pmi->mmz_name);
	if(mmb ==NULL) {
			  /* error("hil_mmb_alloc(%s, %lu, 0x%08lX, %lu, %s) failed!\n", 
				pmi->mmb_name, pmi->size, pmi->align, pmi->gfp, pmi->mmz_name);  */
		return -ENOMEM;
	}

	new_mmbinfo = kmalloc(sizeof(*new_mmbinfo), GFP_KERNEL);
	if(new_mmbinfo ==NULL) {
		hil_mmb_free(mmb);
		error("alloc mmb_info failed!\n");
		return -ENOMEM;
	}

	memcpy(new_mmbinfo, pmi, sizeof(*new_mmbinfo));
	new_mmbinfo->phys_addr = hil_mmb_phys(mmb);
	new_mmbinfo->mmb = mmb;
	new_mmbinfo->prot = PROT_READ;
	new_mmbinfo->flags = MAP_SHARED;
#ifdef MMB_SHARE_SUPPORT  
    new_mmbinfo->mmb_type = MMB_TYPE_NOMAL;
    new_mmbinfo->pid = pmu->pid;
    INIT_LIST_HEAD(&new_mmbinfo->share_list);
    if (iocmd) {  
        SHARE_LIST_LOCK;
        new_mmbinfo->mmb_type = MMB_TYPE_BASE;
        list_add_tail(&new_mmbinfo->list, &mmb_share_list);
        if(iocmd == MMB_SHARE_COM && !share_com_phy_start) {
            share_com_phy_start = new_mmbinfo->phys_addr;
            share_com_size = new_mmbinfo->size;	
        }
        info( "[MMZ]:alloc share mmb [0x%08lX, 0x%08lX].%d\n", new_mmbinfo->phys_addr,new_mmbinfo->size,new_mmbinfo->pid);
        SHARE_LIST_UNLOCK;
    }
    else 
#else
	new_mmbinfo->pid = current->tgid;
#endif	
	list_add_tail(&new_mmbinfo->list, &pmu->list);

	pmi->phys_addr = new_mmbinfo->phys_addr;

	hil_mmb_get(mmb);

	return 0;
}

#ifndef CFG_MMZ_MINI
static int ioctl_mmb_alloc_v2(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *new_mmbinfo;
	hil_mmb_t *mmb;

	mmb = hil_mmb_alloc_v2(pmi->mmb_name, pmi->size, pmi->align, pmi->gfp, pmi->mmz_name, pmi->order);
	if(mmb ==NULL) {
		error("hil_mmb_alloc(%s, %lu, 0x%08lX, %lu, %s) failed!\n", 
				pmi->mmb_name, pmi->size, pmi->align, pmi->gfp, pmi->mmz_name);
		return -ENOMEM;
	}

	//new_mmbinfo = kmalloc(sizeof(*new_mmbinfo), GFP_KERNEL);
	new_mmbinfo = kmalloc(sizeof(struct mmb_info), GFP_KERNEL);
	if(new_mmbinfo ==NULL) {
		hil_mmb_free(mmb);
		error("alloc mmb_info failed!\n");
		return -ENOMEM;
	}

	memcpy(new_mmbinfo, pmi, sizeof(*new_mmbinfo));
	new_mmbinfo->phys_addr = hil_mmb_phys(mmb);
	new_mmbinfo->mmb = mmb;
	new_mmbinfo->prot = PROT_READ;
	new_mmbinfo->flags = MAP_SHARED;
	new_mmbinfo->pid = current->tgid;
	list_add_tail(&new_mmbinfo->list, &pmu->list);

	pmi->phys_addr = new_mmbinfo->phys_addr;

	hil_mmb_get(mmb);

	return 0;
}
#endif

#ifdef MMB_SHARE_SUPPORT
//the position of the same phy_add in the share list
static struct mmb_info* get_baseshare_mmbinfo(unsigned long addr)
{
    struct mmb_info *p;

    list_for_each_entry(p, &mmb_share_list, list) {
        if (p->phys_addr == addr) {
            return p;
        }           
    }
    
    return NULL;
}

//get mmb information used by current process in the share list
static struct mmb_info* get_currpidshare_mmbinfo(unsigned long addr, struct mmz_userdev_info *pmu)
{
    struct mmb_info *p,*pShare;

    list_for_each_entry(p, &mmb_share_list, list) {
        if (p->phys_addr == addr) {
            if(p->pid == pmu->pid) {
                 return p;
            }
            
            list_for_each_entry(pShare, &p->share_list, share_list) {
                if (pShare->pid == pmu->pid) {
                    return pShare;
                }            
            }  
            break;
        }           
    }
    
    return NULL;   
}

//get mmb information used by current process in the share mmb list, p is the header
static struct mmb_info* get_currpidshare_mapmmbinfo(struct mmb_info *pbase, struct mmz_userdev_info *pmu)
{
    struct mmb_info *pShare;

     if(pbase->pid == pmu->pid) {
          return pbase;
     }    
            
     list_for_each_entry(pShare, &pbase->share_list, share_list) {
         if (pShare->pid == pmu->pid) {
             return pShare;
         }            
     }  

     return NULL;
}

static struct mmb_info* get_mmbinfo_byusraddr_from_share(unsigned long addr, struct mmz_userdev_info *pmu)
{
    struct mmb_info *p,*pShare;

    list_for_each_entry(p, &mmb_share_list, list) {
        if(p->pid == pmu->pid ) {
            if ( ((unsigned long)p->mapped <= addr) && 
                 ((unsigned long)p->mapped + p->size > addr) ) {
                return p;
            }
        }
        
        list_for_each_entry(pShare, &p->share_list, share_list) {
            if(pShare->pid == pmu->pid ) {
                if ( ((unsigned long)pShare->mapped <= addr) && 
                     ((unsigned long)pShare->mapped + p->size > addr) ) {
                    return pShare;
                }
            }           
        }   
    }

    return NULL;
}
#endif

static struct mmb_info* get_mmbinfo(unsigned long addr, struct mmz_userdev_info *pmu)
{
	struct mmb_info *p;

	list_for_each_entry(p, &pmu->list, list) {
		if(p->phys_addr ==addr)
			break;
	}
	if( &p->list == &pmu->list)
		return NULL;

	return p;
}

static struct mmb_info* get_mmbinfo_safe(unsigned long addr, struct mmz_userdev_info *pmu)
{
	struct mmb_info *p;

	p = get_mmbinfo(addr, pmu);

	if( p ==NULL) {
#ifdef MMB_SHARE_SUPPORT
        p = get_currpidshare_mmbinfo(addr, pmu);
        if(p) {
            return p;         
        }
#endif
		error("mmb(0x%08lX) not found!\n", addr);
		return NULL;
	}

	return p;
}

static int _usrdev_mmb_free(struct mmb_info *p)
{
	int ret = 0;
#ifdef MMB_SHARE_SUPPORT
    struct mmb_info *pShare,*pn, *pBase; 

    info( "[%s]:delete share mmb base:%d.[0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->mmb_type, p->phys_addr, p->size, p->pid);
    if ( p->mmb_type == MMB_TYPE_BASE) {
        pBase = p;
        list_for_each_entry_safe(pShare, pn, &p->share_list, share_list) {
            info( "[%s]:delete share mmb base[0x%08lX, 0x%08lX].%d\n", __FUNCTION__, pShare->phys_addr,pShare->size,pShare->pid);
            
            hil_mmb_put(pShare->mmb);
            list_del(&pShare->share_list);
            kfree(pShare);
        }  
    } else if (p->mmb_type == MMB_TYPE_COPY) {
        // TODO: may to delete one time for check list
        pBase = get_baseshare_mmbinfo(p->phys_addr);          
        list_for_each_entry_safe(pShare, pn, &pBase->share_list, share_list) {
            info( "[%s]:delete share mmb copy[0x%08lX, 0x%08lX].%d\n",  __FUNCTION__, pShare->phys_addr,pShare->size,pShare->pid);
            hil_mmb_put(pShare->mmb);
            list_del(&pShare->share_list);
            kfree(pShare);
        }  
    } else {
        pBase = p;
        info( "[%s]:delete nomal mmb [0x%08lX, 0x%08lX].%d\n",  __FUNCTION__, pBase->phys_addr,pBase->size,pBase->pid);
    }
    
    ret = hil_mmb_put(pBase->mmb);
    info( "[%s]:hil_mmb_put ret = %d\n", __FUNCTION__, ret);	
    
    list_del(&pBase->list);
    ret = hil_mmb_free(pBase->mmb);
    info( "[%s]:hil_mmb_free ret = %d\n", __FUNCTION__, ret);	 
		
    if(pBase->mmb->phys_addr == share_com_phy_start) {
        share_com_phy_start = 0;
        share_com_size = 0;
    }
	
    kfree(pBase); 
    p = NULL;
#else
	list_del(&p->list);
	hil_mmb_put(p->mmb);
	ret = hil_mmb_free(p->mmb);
	kfree(p);
#endif

	return ret;
}

static int ioctl_mmb_free(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	int ret = 0;
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *p;
    
#ifdef MMB_SHARE_SUPPORT   
    SHARE_LIST_LOCK;
    if ((p = get_mmbinfo(pmi->phys_addr, pmu)) != NULL) {
        //found in the nomal used list.
        if (p->delayed_free) {
            warning("mmb<%s> is delayed_free, can not free again!\n", p->mmb->name);
            SHARE_LIST_UNLOCK;
            return -EBUSY;
        }
    
        if (p->map_ref > 0 || p->mmb_ref > 0) {
            warning("mmb<%s>.1 is still used!%d\n", p->mmb->name,p->pid);
            p->delayed_free = 1;
            SHARE_LIST_UNLOCK;
            return -EBUSY;
        }   
        
        ret = _usrdev_mmb_free(p);
    } else if ((p = get_baseshare_mmbinfo(pmi->phys_addr)) != NULL) {
        //found in the share list
        struct mmb_info *pShare,*pn;
        int busy;
        
        info( "%s.share list [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->phys_addr, p->size, p->pid);
        list_for_each_entry_safe(pShare, pn, &p->share_list, share_list) {
            info( "%s.check [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);
            busy = 0;
            
            if (pShare->delayed_free) {
                warning("mmb<%s> is delayed_free, can not free again!\n",pShare->mmb->name);
                busy = 1;
            }
            
            if (pShare->map_ref > 0 || pShare->mmb_ref > 0) {
                //alloc and map in process A  ->  map in process B -> unmap and delete in process B then go into here because it is still used and not unmaped by process B.
                info("mmb<%s>.2 is still used!%d\n", pShare->mmb->name,pShare->pid);
                pShare->delayed_free = 1;
                busy = 1;
            }

            //if unmap then delete the mmb info in the share mmb list
            if(/*pShare->pid == pmu->pid && */busy == 0) {
                info( "%s.list_del [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);
                list_del(&pShare->share_list);
                kfree(pShare);       
            }
        } 
        
        if (p->delayed_free) {
            //alloc and map in process A  ->  map in process B -> unmap and delete in process B then go into here because it is still used and not unmaped by process B.
            info("mmb<%s> is delayed_free, can not free again!\n", p->mmb->name); 
            SHARE_LIST_UNLOCK;
            return -EBUSY;
        }   
        
        if (p->map_ref > 0 || p->mmb_ref > 0) { 
            //alloc and map in process A  ->  map in process B -> unmap and delete in process B then go into here because it is still used and not unmaped bu prcess A
            info("mmb<%s>.3 is still used!%d,%d,%d\n", p->mmb->name,p->map_ref,p->mmb_ref,p->pid);
            p->delayed_free = 1;
            SHARE_LIST_UNLOCK;
            return -EBUSY;
        }   

        if(&p->share_list == p->share_list.next) {
            //only one the same phy_addr share list
            info( "%s.delete base(one) [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->phys_addr, p->size, p->pid);
            ret = _usrdev_mmb_free(p);          
        } else {
            pShare = list_entry(p->share_list.next, struct mmb_info, share_list);
            pShare->mmb_type = MMB_TYPE_BASE;
            info( "%s.delete base [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);
            list_add(&pShare->list, p->list.prev);
            list_del(&p->list);  
            
            hil_mmb_put(p->mmb);
            list_del(&p->share_list);            
            kfree(p);            
        }           
    }
    else {
        //alloc and map in process A  ->  map in process B -> unmap and delete in process A(B) -> unmap and delete in process B(A)
        //then go into here becuase it had be free after unmap,delete and unmap in the two processes, the last delete is unwanted.
        info("mmb<%s> not found![0x%08lX, 0x%08lX].%d.%d\n", pmi->mmb_name,pmi->phys_addr,pmi->size,pmi->pid,pmi->mmb_type);
        SHARE_LIST_UNLOCK;
        return -EPERM;
   }
#else
	if ( (p=get_mmbinfo_safe(pmi->phys_addr, pmu)) ==NULL)
		return -EPERM;

	if(p->delayed_free) {
		warning("mmb<%s> is delayed_free, can not free again!\n", p->mmb->name);
		return -EBUSY;
	}

	if(p->map_ref>0 || p->mmb_ref>0) {
		warning("mmb<%s> is still used!\n", p->mmb->name);
		p->delayed_free = 1;
		return -EBUSY;
	}

	ret = _usrdev_mmb_free(p);
#endif
    SHARE_LIST_UNLOCK;

	return ret;
}

#ifdef MMB_SHARE_SUPPORT  
static int _usrdev_mmb_force_free(struct mmb_info *p)
{
    int ret = 0;

    struct mmb_info *pShare,*pn, *pBase;  
    if ( p->mmb_type == MMB_TYPE_BASE) {
        pBase = p;
        list_for_each_entry_safe(pShare, pn, &p->share_list, share_list) {
           info( "[MMZ]:delete share mmb base[0x%08lX, 0x%08lX].%d\n", pShare->phys_addr,pShare->size,pShare->pid);
            hil_mmb_force_put(pShare->mmb);
            list_del(&pShare->share_list);
            kfree(pShare);
        }  
    } else if (p->mmb_type == MMB_TYPE_COPY) {
        // TODO: may to delete one time for check list
        pBase = get_baseshare_mmbinfo(p->phys_addr);          
        list_for_each_entry_safe(pShare, pn, &pBase->share_list, share_list) {
           info( "[MMZ]:delete share mmb copy[0x%08lX, 0x%08lX].%d\n", pShare->phys_addr,pShare->size,pShare->pid);
            hil_mmb_force_put(pShare->mmb);
            list_del(&pShare->share_list);
            kfree(pShare);
        }  
    } else {
        pBase = p;
        info( "[MMZ]:delete nomal mmb [0x%08lX, 0x%08lX].%d\n", pBase->phys_addr,pBase->size,pBase->pid);
    }
    
    hil_mmb_force_put(pBase->mmb);
    list_del(&pBase->list);
    ret = hil_mmb_free(pBase->mmb);
    if(pBase->mmb->phys_addr == share_com_phy_start) {
        share_com_phy_start = 0;
        share_com_size = 0;
    }
    kfree(pBase);    
    p = NULL;
    info( "[MMZ]:ret = %d\n",ret);

	return ret;
}

static int ioctl_mmb_force_free(struct mmb_info *pmi)
{
    int ret = 0;
    struct mmb_info *p;

    SHARE_LIST_LOCK;
    if ((p = get_baseshare_mmbinfo(pmi->phys_addr)) != NULL) {
        //foudn in the share list
        struct mmb_info *pShare,*pn;
        info( "%s.share list [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->phys_addr, p->size, p->pid);
        list_for_each_entry_safe(pShare, pn, &p->share_list, share_list) {
#if MMB_SHARE_DEBUG
            info( "%s.check [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);                                  
            if (pShare->delayed_free) {
                warning("mmb<%s> is delayed_free, can not free again!\n",pShare->mmb->name);
            }        
            if (pShare->map_ref > 0 || pShare->mmb_ref > 0) {               
                warning("mmb<%s>.2 is still used!%d\n", pShare->mmb->name,pShare->pid);

                pShare->delayed_free = 1;
            }
            info( "%s.list_del [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);
#endif                                                       
            list_del(&pShare->share_list);
            kfree(pShare);       
        } 
#if MMB_SHARE_DEBUG            
        if (p->delayed_free) {            
            warning("mmb<%s> is delayed_free, can not free again!\n", p->mmb->name); 
        }    
        if (p->map_ref > 0 || p->mmb_ref > 0) {        
            warning("mmb<%s>.3 is still used!%d,%d,%d\n", p->mmb->name,p->map_ref,p->mmb_ref,p->pid);
            p->delayed_free = 1;
        }   
#endif
        if(&p->share_list == p->share_list.next) {
            //only one the same phy_addr share list
            info( "%s.delete base(one) [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->phys_addr, p->size, p->pid);
            ret = _usrdev_mmb_force_free(p);          
        } else {
            pShare =  list_entry(p->share_list.next, struct mmb_info, share_list);
            pShare->mmb_type = MMB_TYPE_BASE;
            info( "%s.delete base [0x%08lX, 0x%08lX].%d\n", __FUNCTION__,pShare->phys_addr,pShare->size,pShare->pid);
            list_add(&pShare->list, p->list.prev);
            list_del(&p->list);     
            
            hil_mmb_put(p->mmb);
            
            list_del(&p->share_list);     
            
            kfree(p);            
        }           
    }
    else {    
        info("mmb<%s> not found![0x%08lX, 0x%08lX].%d.%d\n", pmi->mmb_name,pmi->phys_addr,pmi->size,pmi->pid,pmi->mmb_type);
        SHARE_LIST_UNLOCK;
        return -EPERM;
   }

   SHARE_LIST_UNLOCK;
   return ret;
}
#endif 

static int ioctl_mmb_attr(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *p;

	if ( (p=get_mmbinfo_safe(pmi->phys_addr, pmu)) ==NULL)
		return -EPERM;

	memcpy(pmi, p, sizeof(*pmi));
	return 0;
}

static int ioctl_mmb_user_remap(struct file *file, unsigned int iocmd, struct mmb_info *pmi, int cached)
{
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *p;
	#if !(LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	unsigned long round_up_len;
	#endif


	unsigned long addr, len, prot, flags, pgoff;
#ifdef MMB_SHARE_SUPPORT
     struct mmb_info *pMapped;

     SHARE_LIST_LOCK;
     if((p = get_mmbinfo(pmi->phys_addr, pmu)) == NULL) { 
        //not in the share list
        if ((p = get_baseshare_mmbinfo(pmi->phys_addr)) == NULL) {
             SHARE_LIST_UNLOCK;
             return -EPERM;       
        }        
        // in the share list, but not mapped
        if ((pMapped = get_currpidshare_mapmmbinfo(p, pmu)) == NULL) {
            struct mmb_info *pNew = kmalloc(sizeof(struct mmb_info), GFP_KERNEL);
            if (pNew == NULL) {
                error("alloc mmb_info failed!\n");
                SHARE_LIST_UNLOCK;
                return -ENOMEM;
            }    
            memcpy(pNew, p, sizeof(struct mmb_info));
            pNew->mmb_type = MMB_TYPE_COPY;
            pNew->mapped = 0;			
            pNew->map_ref = 0;
            pNew->mmb_ref = 0;
            pNew->map_cached = 0;
            pNew->pid = pmu->pid;
            list_add_tail(&pNew->share_list, &p->share_list);
            info( "%s.new copy [0x%08lX, 0x%08lX].%d--from[0x%08lX].%d\n", __FUNCTION__ ,pNew->phys_addr,pNew->size,pNew->pid,p->phys_addr,p->pid);
   
#if MMB_SHARE_DEBUG
            if(p == NULL || p->mmb == NULL) {
                 info( "%s fatal error,please debug\n", __FUNCTION__ );
            } else {
                 info( "%s copy mmb info[0x%08lX, 0x%08lX].%ld\n", __FUNCTION__, p->mmb->phys_addr , p->mmb->length , p->mmb->flags);
            } 
#endif 
            p = pNew; 
        } else {
            info( "%s.base map [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, pMapped->phys_addr, pMapped->size,pMapped->pid);
            p = pMapped;
        }
    }
#else
	if ( (p=get_mmbinfo_safe(pmi->phys_addr, pmu)) ==NULL)
		return -EPERM;
#endif   
	
	if( p->mapped && p->map_ref>0) {
		if(cached != p->map_cached) {
			error("mmb<%s> already mapped %s, can not be remap to %s.\n", p->mmb->name, 
					p->map_cached ? "cached" : "non-cached",
					cached ? "cached" : "non-cached");
            SHARE_LIST_UNLOCK;
			return -EINVAL;
		}

		p->map_ref++;
		p->mmb_ref++;

		hil_mmb_get(p->mmb);

		pmi->mapped = p->mapped;

        SHARE_LIST_UNLOCK;
		return 0;
	}

	if(p->phys_addr & ~PAGE_MASK) {
        SHARE_LIST_UNLOCK;
		return -EINVAL;
    }

	addr = 0;
	pgoff = p->phys_addr >> PAGE_SHIFT;
    //pgoff = p->phys_addr; //add for do_mmap

	len = PAGE_ALIGN(p->size);

	prot = pmi->prot;
	flags = pmi->flags;
	if(prot ==0)
		prot = p->prot;
	if(flags ==0)
		flags = p->flags;

    p->map_cached = cached;
    //SHARE_LIST_UNLOCK;

    down_write(&current->mm->mmap_sem);
	pmu->mmap_pid = current->tgid;
	#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
	addr = do_mmap_pgoff(file, addr, len, prot, flags, pgoff);
	#else
	addr = do_mmap_pgoff(file, addr, len, prot, flags, pgoff,&round_up_len);
	#endif
	pmu->mmap_pid = 0;
	up_write(&current->mm->mmap_sem);

	if(IS_ERR_VALUE(addr)) {
		error("do_mmap_pgoff(file, 0, %lu, 0x%08lX, 0x%08lX, 0x%08lX) return 0x%08lX\n", 
				len, prot, flags, pgoff, addr);
        SHARE_LIST_UNLOCK;
		return addr;
	}
    
    //SHARE_LIST_LOCK;
	p->mapped = (void*)addr;
	p->prot = prot;
	p->flags = flags;

	p->map_ref++;
	p->mmb_ref++;
	hil_mmb_get(p->mmb);

	pmi->mapped = p->mapped;
    SHARE_LIST_UNLOCK;
    
	return 0;
}

static int ioctl_mmb_user_unmap(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	int ret;
	unsigned long addr, len;
	struct mmb_info *p;
	struct mmz_userdev_info *pmu = file->private_data;
#ifdef MMB_SHARE_SUPPORT
    struct mmb_info *pBase = NULL;
    struct mmb_info *pMapped = NULL;
    
    SHARE_LIST_LOCK;
    if ((p = get_mmbinfo(pmi->phys_addr, pmu)) == NULL)  {
        if ((pBase = get_baseshare_mmbinfo(pmi->phys_addr)) == NULL) {
            info( "%s.pBase unmap not found!\n", __FUNCTION__);
            SHARE_LIST_UNLOCK;
            return -EPERM;       
        }  
        if ((pMapped = get_currpidshare_mapmmbinfo(pBase, pmu)) == NULL) {
            info( "%s.pMapped unmap not found!\n", __FUNCTION__);
            SHARE_LIST_UNLOCK;
            return -EPERM;  
        }
        info( "%s.%s unmap [0x%08lX, 0x%08lX, %d].[0x%08lX, 0x%08lX, %d].%d\n", __FUNCTION__, (pMapped->pid == pBase->pid)?"base":"copy",pMapped->phys_addr, pMapped->size,pMapped->pid, pBase->phys_addr, pBase->size,pBase->pid, current->tgid);

        p = pMapped;
    }    
#else
	if ( (p=get_mmbinfo_safe(pmi->phys_addr, pmu)) ==NULL)
		return -EPERM;
#endif    
	if(!p->mapped) {
        warning("mmb(0x%08lX) have'nt been user-mapped yet!\n", p->phys_addr);
		pmi->mapped = NULL;
        SHARE_LIST_UNLOCK;
		return -EIO;
	}

	if(!(p->map_ref>0 && p->mmb_ref>0)) {
		error("mmb<%s> has invalid refer: map_ref = %d, mmb_ref = %d.\n", p->mmb->name, p->map_ref, p->mmb_ref);
        SHARE_LIST_UNLOCK;
		return -EIO;
	}

	p->map_ref--;
	p->mmb_ref--;
	hil_mmb_put(p->mmb);

	if(p->map_ref >0) {
        SHARE_LIST_UNLOCK;
		return 0;
    }
    //SHARE_LIST_UNLOCK;

	addr = (unsigned long)p->mapped;
	len  = PAGE_ALIGN(p->size);

    down_write(&current->mm->mmap_sem);
	ret = do_munmap(current->mm, addr, len);
	up_write(&current->mm->mmap_sem);

	if(!IS_ERR_VALUE(ret)) {
		/** the memory may be used by system later so clean the L2 cache(L1 cache is guaranted by do_munmap)  **/
		if(p->map_cached)
			outer_flush_range(pmi->phys_addr,len);
		p->mapped = NULL;
		pmi->mapped = NULL;
	}

    //SHARE_LIST_LOCK;
#ifdef MMB_SHARE_SUPPORT
    if((p->mmb_type == MMB_TYPE_COPY || p->mmb_type == MMB_TYPE_BASE) && pBase)
    {
        struct mmb_info *pShare,*pn,*pNext;
        list_for_each_entry_safe(pShare, pn, &pBase->share_list, share_list) {     
             if(pShare->delayed_free && pShare->mmb_ref == 0 && pShare->mmb_ref == 0) {
                 // delete this phy_add same list node if delayed free
                info( "%s.check delayed free [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, pShare->phys_addr, pShare->size, pShare->pid);
                list_del(&pShare->share_list);
                kfree(pShare);
             }           
        }        
       
        if(pBase->delayed_free && pBase->mmb_ref == 0 && pBase->mmb_ref == 0) {
            if(&pBase->share_list == pBase->share_list.next) {
                //only one in the same phy_addr list, the free when check delayed free
                info( "%s.base node delay free [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, pBase->phys_addr, pBase->size, pBase->pid);
                _usrdev_mmb_free(pBase);
            } else {
                //delete the base phy_add same list node if exist other nodes
                info( "%s.delete base [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, pBase->phys_addr, pBase->size, pBase->pid);
                pNext = list_entry(pBase->share_list.next, struct mmb_info, share_list);                
                pNext->mmb_type = MMB_TYPE_BASE;                
                list_add(&pNext->list, pBase->list.prev);
                list_del(&pBase->list);                
                list_del(&pBase->share_list);     
                kfree(pBase);                 
            }
        } 
    } else 
#endif
	if(p->delayed_free && p->mmb_ref==0 && p->mmb_ref==0) {
		_usrdev_mmb_free(p);
	}
    SHARE_LIST_UNLOCK;

	return ret;
}


// find mmbinfo by use addr
static struct mmb_info* get_mmbinfo_byusraddr(unsigned long addr, struct mmz_userdev_info *pmu)
{
	struct mmb_info *p;

	list_for_each_entry(p, &pmu->list, list) {
		if( ((unsigned long)p->mapped <= addr) && 
			((unsigned long)p->mapped + p->size > addr) 
#ifndef MMB_SHARE_SUPPORT
             &&(p->pid == current->tgid)
#endif
			)
				break;
	}
    if ( &p->list == &pmu->list) {
#ifdef MMB_SHARE_SUPPORT
        SHARE_LIST_LOCK;
        if((p = get_mmbinfo_byusraddr_from_share(addr, pmu))) {
            SHARE_LIST_UNLOCK;
            return p;
        }
        SHARE_LIST_UNLOCK;
#endif
        return NULL;
    }
	return p;
}

/*To make sure ref get and release, both get and put interface shoude be exist, 
	but customers make sure theirselves, will not release in using */
/*CNcomment: 应当有 get/put两个接口，保证ref的获取释放，不过用户对该接口暂时自己确认，使用中不进行释放*/
static int ioctl_mmb_user_getphyaddr(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
	struct mmb_info *p;
	struct mmz_userdev_info *pmu = file->private_data;

	p = get_mmbinfo_byusraddr((unsigned long)pmi->mapped, pmu);
	if ( p ==NULL)
		return -EPERM;

	if(!(p->map_ref>0 && p->mmb_ref>0)) {
		error("mmb<%s> has invalid refer: map_ref = %d, mmb_ref = %d.\n", p->mmb->name, p->map_ref, p->mmb_ref);
		return -EIO;
	}

	pmi->phys_addr = p->phys_addr + ((unsigned long)pmi->mapped - (unsigned long)p->mapped);
	pmi->size = p->size - ((unsigned long)pmi->mapped - (unsigned long)p->mapped);
	return 0;
}

#ifdef MMZ_V2_SUPPORT
static int ioctl_mmb_user_getphyaddr_start(struct file *file, unsigned int iocmd, struct mmb_info *pmi)
{
    struct mmb_info *p;
    struct mmz_userdev_info *pmu = file->private_data;

    p = get_mmbinfo_byusraddr((unsigned long)pmi->mapped, pmu);
    if ( p == NULL) 
        return -EPERM;   

    if (!(p->map_ref > 0 && p->mmb_ref > 0)) {
        error("mmb<%s> has invalid refer: map_ref = %d, mmb_ref = %d.\n", p->mmb->name, p->map_ref, p->mmb_ref);
        return -EIO;
    }

    pmi->mapped = p->mapped;
    pmi->phys_addr = p->phys_addr;
    pmi->size = p->size;
    
    return 0;
}
#endif

static int mmz_userdev_ioctl_m(struct inode *inode, struct file *file, unsigned int cmd, struct mmb_info *pmi)
{
	int ret = 0;
	switch(_IOC_NR(cmd)) {
		case _IOC_NR(IOC_MMB_ALLOC):
#ifdef MMB_SHARE_SUPPORT	
            ret = ioctl_mmb_alloc(file, MMB_SHARE_NONE, pmi);
#else
			ret = ioctl_mmb_alloc(file, cmd, pmi);
#endif
			break;
#ifndef CFG_MMZ_MINI
		case _IOC_NR(IOC_MMB_ALLOC_V2):
			ret = ioctl_mmb_alloc_v2(file, cmd, pmi);
			break;
#endif
		case _IOC_NR(IOC_MMB_ATTR):
			ret = ioctl_mmb_attr(file, cmd, pmi);
			break;
		case _IOC_NR(IOC_MMB_FREE):
			ret = ioctl_mmb_free(file, cmd, pmi);
			break;

		case _IOC_NR(IOC_MMB_USER_REMAP):
			ret = ioctl_mmb_user_remap(file, cmd, pmi, 0);
			break;
		case _IOC_NR(IOC_MMB_USER_REMAP_CACHED):
			ret = ioctl_mmb_user_remap(file, cmd, pmi, 1);
			break;
		case _IOC_NR(IOC_MMB_USER_UNMAP):
			ret = ioctl_mmb_user_unmap(file, cmd, pmi);
			break;
		case _IOC_NR(IOC_MMB_USER_GETPHYADDR):
			ret = ioctl_mmb_user_getphyaddr(file, cmd, pmi);
			break;
#ifdef MMB_SHARE_SUPPORT			
        case _IOC_NR(IOC_MMB_ALLOC_SHARE):
            ret = ioctl_mmb_alloc(file, MMB_SHARE_SHM, pmi);
            break;  
            
        case _IOC_NR(IOC_MMB_ALLOC_SHM_COM): 
            if(share_com_phy_start) {
	         ret = -ENOMEM;
            } else {
                ret = ioctl_mmb_alloc(file, MMB_SHARE_COM, pmi);
            }
            break;  
            
        case _IOC_NR(IOC_MMB_GET_SHM_COM):  
            pmi->phys_addr = share_com_phy_start;
            pmi->size = share_com_size;
            break;  

        case _IOC_NR(IOC_MMB_FORCE_FREE):
            ret = ioctl_mmb_force_free(pmi);
            break;				  			
#endif
#ifdef MMZ_V2_SUPPORT
        case _IOC_NR(IOC_MMB_USER_GETPHYADDR_S):
            ret = ioctl_mmb_user_getphyaddr_start(file, cmd, pmi);
            break;
#endif            

		default:
			error("invalid ioctl cmd = %08X\n", cmd);
			ret = -EINVAL;
			break;
	}

	return ret;
}

static int mmz_userdev_ioctl_r(struct inode *inode, struct file *file, unsigned int cmd, struct mmb_info *pmi)
{
	switch(_IOC_NR(cmd)) {
		case _IOC_NR(IOC_MMB_ADD_REF):
			pmi->mmb_ref++;
			hil_mmb_get(pmi->mmb);
			break;
		case _IOC_NR(IOC_MMB_DEC_REF):
			if(pmi->mmb_ref <=0) {
				error("mmb<%s> mmb_ref is %d!\n", pmi->mmb->name, pmi->mmb_ref);
				return -EPERM;
			}
			pmi->mmb_ref--;
			hil_mmb_put(pmi->mmb);
			if(pmi->delayed_free && pmi->mmb_ref==0 && pmi->mmb_ref==0) {
				_usrdev_mmb_free(pmi);
			}
			break;
		default:
			return -EINVAL;
			break;
	}

	return 0;
}

/* just for test */
static int mmz_userdev_ioctl_t(struct inode *inode, struct file *file, unsigned int cmd, struct mmb_info *pmi)
{
	return 0;
}

long mmz_userdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret = 0;
	struct mmz_userdev_info *pmu = file->private_data;

	down(&pmu->sem);

	if(_IOC_TYPE(cmd) == 'm') {

		struct mmb_info mi;

		if(_IOC_SIZE(cmd) > sizeof(mi) || arg==0) {
			error("_IOC_SIZE(cmd)=%d, arg==0x%08lX\n", _IOC_SIZE(cmd), arg);
			ret = -EINVAL;
			goto __error_exit;
		}
		memset(&mi, 0, sizeof(mi));
		if (copy_from_user(&mi, (void*)arg, _IOC_SIZE(cmd)))
		{
            error("\nmmz_userdev_ioctl: copy_from_user error.\n");
            ret = -EFAULT;
			goto __error_exit;
		}

		ret = mmz_userdev_ioctl_m(file->f_dentry->d_inode,file, cmd, &mi);

		if(!ret && (cmd&IOC_OUT))
		{
			if (copy_to_user((void*)arg, &mi, _IOC_SIZE(cmd)))
			{
                error("\nmmz_userdev_ioctl: copy_to_user error.\n");
                ret = -EFAULT;
			    goto __error_exit;
		    }
		}

	} else if(_IOC_TYPE(cmd) == 'r') {
		struct mmb_info *pmi;
		if ( (pmi=get_mmbinfo_safe(arg, pmu)) ==NULL) {
			ret = -EPERM;
			goto __error_exit;
		}

		ret = mmz_userdev_ioctl_r(file->f_dentry->d_inode, file, cmd, pmi);

	} else if(_IOC_TYPE(cmd) == 'c') {

		struct mmb_info *pmi;
		if (arg == 0){
			mmz_flush_dcache_all();	
			goto __error_exit;
		}
		if ( (pmi=get_mmbinfo_safe(arg, pmu)) ==NULL) {
			ret = -EPERM;
			goto __error_exit;
		}

		switch(_IOC_NR(cmd)) {
			case _IOC_NR(IOC_MMB_FLUSH_DCACHE):
				mmz_flush_dcache_mmb(pmi);
				break;
			default:
				ret = -EINVAL;
				break;
		}

	} else if(_IOC_TYPE(cmd) == 't') {
		struct mmb_info mi;
		struct mmb_info *pmi;

		memset(&mi, 0, sizeof(mi));
		if (copy_from_user(&mi, (void*)arg, _IOC_SIZE(cmd)))
		{
            error("\nmmz_userdev_ioctl: copy_from_user error.\n");
            ret = -EFAULT;
            goto __error_exit;
		}

		if ( (pmi=get_mmbinfo_safe(mi.phys_addr, pmu)) ==NULL) {
			ret = -EPERM;
			goto __error_exit;
		}

		ret = mmz_userdev_ioctl_t(file->f_dentry->d_inode, file, cmd, pmi);
	} else {
		ret = -EINVAL;
	}

__error_exit:

	up(&pmu->sem);

	return ret;
}

int mmz_userdev_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct mmb_info *p;
	struct mmz_userdev_info *pmu = file->private_data;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;

	if(current->tgid != pmu->mmap_pid) {
		error("do not call mmap() yourself!\n");
		return -EPERM;
	}
	
#ifdef MMB_SHARE_SUPPORT
    p = get_mmbinfo_safe(offset, pmu);
#else
	p = get_mmbinfo(offset, pmu);
#endif	
	if( p ==NULL) {
		error("I'm confused, mmb(0x%08lX) not found?!\n", offset);
		return -EPERM;
	}
	if(p->mapped) {
            error("I'm confused, mmb(0x%08lX, 0x%08lX,, pid = %d) have been mapped yet?!\n", offset, (unsigned long)p->mapped, current->tgid);
		return -EIO;
	}
#if 0
	if(offset >= PHYS_OFFSET && offset <  __pa(high_memory) ) {
		error("map address 0x%08lX in kernel range!\n", offset);
		return -EINVAL;
	}
#endif

#if defined(pgprot_noncached)
	if (file->f_flags & O_SYNC) {
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	} else {
		if(p->map_cached)
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
 			vma->vm_page_prot = __pgprot(pgprot_val(vma->vm_page_prot) | L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_DIRTY | L_PTE_WRITE | L_PTE_MT_DEV_CACHED);
#else
			vma->vm_page_prot = __pgprot(pgprot_val(vma->vm_page_prot) | L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_DIRTY | L_PTE_RDONLY | L_PTE_MT_DEV_CACHED);
#endif
		else
			vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}
#endif

	/* Remap-pfn-range will mark the range VM_IO and VM_RESERVED */
	if (remap_pfn_range(vma,
			    vma->vm_start,
			    vma->vm_pgoff,
			    vma->vm_end-vma->vm_start,
			    vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}


int mmz_userdev_release(struct inode *inode, struct file *file)
{
	struct mmz_userdev_info *pmu = file->private_data;
	struct mmb_info *p, *n;
#ifdef MMB_SHARE_SUPPORT
    struct mmb_info *pShare,*pn,*pNext;

    SHARE_LIST_LOCK;
#endif

	list_for_each_entry_safe(p, n, &pmu->list, list) {
	    /*
		warning( "MMB LEAK(pid=%d): 0x%08lX, %lu bytes, '%s'\n", \
				pmu->pid, hil_mmb_phys(p->mmb), \
				hil_mmb_length(p->mmb),
				hil_mmb_name(p->mmb));
		*/
		/* we do not need to release mapped-area here, system will do it for us */
		/*
		if(p->mapped)
			warning("mmz_userdev_release: mmb<0x%08lX> mapped to userspace 0x%p will be force unmaped!\n", p->phys_addr, p->mapped);
		*/
		for(; p->mmb_ref>0; p->mmb_ref--)
			hil_mmb_put(p->mmb);
		_usrdev_mmb_free(p);
	}

#ifdef MMB_SHARE_SUPPORT
    list_for_each_entry_safe(p, n, &mmb_share_list, list) {        
        list_for_each_entry_safe(pShare, pn, &p->share_list, share_list) {
            //if ((pShare->pid == current->tgid) || (pShare->pid == current->tgid) || (pShare->map_ref == 0 && pShare->mmb_ref == 0 && (!pShare->delayed_free))) {
            if ((pShare->pid == current->tgid) || (pShare->pid == pmu->pid) || (pShare->map_ref == 0 && pShare->mmb_ref == 0 && (!pShare->delayed_free))) {
                info( "%s.found in share list [0x%08lX, 0x%08lX].%d.%d\n", __FUNCTION__, pShare->phys_addr,pShare->size,pShare->pid, pmu->pid);
                for (; pShare->mmb_ref > 0; pShare->mmb_ref--) {
                    hil_mmb_put(pShare->mmb);
                }             
                list_del(&pShare->share_list);
                kfree(pShare);                
            }            
        }    
        
        //if ((p->pid == current->tgid) || (p->pid == current->tgid) ||(p->map_ref == 0 && p->mmb_ref == 0 && (!p->delayed_free))) {
        if ((p->pid == current->tgid) || (p->pid == pmu->pid) ||(p->map_ref == 0 && p->mmb_ref == 0 && (!p->delayed_free))) {
            if(&p->share_list == p->share_list.next) {
                //only one in the same phy_addr list
                info( "%s.delete one [0x%08lX, 0x%08lX].%d,%d\n", __FUNCTION__, p->phys_addr,p->size,p->pid, current->tgid);
                for (; p->mmb_ref > 0; p->mmb_ref--) {
                    hil_mmb_put(p->mmb);
                }
                _usrdev_mmb_free(p);                
            } else {
                info( "%s.delete base [0x%08lX, 0x%08lX].%d\n", __FUNCTION__, p->phys_addr,p->size,p->pid);
                pNext = list_entry(p->share_list.next, struct mmb_info, share_list);
                pNext->mmb_type = MMB_TYPE_BASE;
                list_add(&pNext->list, p->list.prev);
                list_del(&p->list);  
                
                for (; p->mmb_ref > 0; p->mmb_ref--) {
                    hil_mmb_put(p->mmb);
                }                    
                list_del(&p->share_list);                
                kfree(p);                 
            }
        }        
    }
#endif

	file->private_data = NULL;
	kfree(pmu);

    SHARE_LIST_UNLOCK;
	return 0;
}

static struct file_operations mmz_userdev_fops = {
	.owner	= THIS_MODULE,
	.open	= mmz_userdev_open,
	.release= mmz_userdev_release,
	.unlocked_ioctl  = mmz_userdev_ioctl,
	.mmap	= mmz_userdev_mmap,
};

#if !(LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
static int proc_mmz_read(struct inode *inode, struct file *file)
{
	return single_open(file, mmz_read_proc, PDE_DATA(inode));
}

static struct file_operations proc_mmz_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_mmz_read,
	.read           = seq_read,
        .llseek         = seq_lseek,
	.write		= NULL,
        .release        = single_release,
};
#endif
/****************************proc**********************************/
#define MEDIA_MEM_NAME  "media-mem"
static int media_mem_proc_init(void)
{
#if !(0 == HI_PROC_SUPPORT)
	struct proc_dir_entry *p;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
	p = create_proc_entry(MEDIA_MEM_NAME, 0444,NULL);
	if(p == NULL)
		return -1;
	p->read_proc = mmz_read_proc;
	p->write_proc = NULL;
#else
	p = proc_create(MEDIA_MEM_NAME, 0444, NULL,&proc_mmz_fops);
	if(p == NULL)
		return -1;
#endif

#endif
        return 0;
}


static void media_mem_proc_exit(void)
{
#if !(0 == HI_PROC_SUPPORT)
	remove_proc_entry(MEDIA_MEM_NAME, NULL);
#endif
}


/********************init**************************/

static PM_DEVICE_S mmz_userdev = {
	.minor	= HIMEDIA_DYNAMIC_MINOR,
	.name	= "mmz_userdev",
	.owner = THIS_MODULE,
	.app_ops= &mmz_userdev_fops 
};

int DRV_MMZ_ModInit(void)
{
    HI_S32 s32Ret = 0;

	HI_DRV_MMZ_Init();
    
	media_mem_proc_init();
	s32Ret = HI_DRV_PM_Register(&mmz_userdev);
    if(s32Ret != HI_SUCCESS)
    {
        media_mem_proc_exit();
	    HI_DRV_MMZ_Exit();
        return HI_FAILURE;
    }

#ifdef MODULE
    HI_PRINT("Load hi_mmz.ko success.\t\t(%s)\n", VERSION_STRING);
#endif

	return 0;
}

void DRV_MMZ_ModExit(void)
{
	HI_DRV_PM_UnRegister(&mmz_userdev);
	media_mem_proc_exit();
    
	HI_DRV_MMZ_Exit();

#ifdef MODULE
    HI_PRINT("remove hi_mmz.ko success.\n");
#endif
}


#ifdef MODULE
module_init(DRV_MMZ_ModInit);
module_exit(DRV_MMZ_ModExit);
#endif

EXPORT_SYMBOL(DRV_MMZ_ModInit);
EXPORT_SYMBOL(DRV_MMZ_ModExit);
    

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liu jiandong");

