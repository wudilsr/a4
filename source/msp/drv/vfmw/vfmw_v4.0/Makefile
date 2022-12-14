#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
VFMW_DIR := $(MSP_DIR)/drv/vfmw/vfmw_v4.0

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)    \
                -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif
################################################################################################
#    PRODUCT
################################################################################################

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
include $(VFMW_DIR)/firmware/product/Hi3716CV200/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
include $(VFMW_DIR)/firmware/product/Hi3798CV100/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
include $(VFMW_DIR)/firmware/product/Hi3798MV100/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
include $(VFMW_DIR)/firmware/product/Hi3716MV410/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3751v100),)
include $(VFMW_DIR)/firmware/product/HiS5V100/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3751v200),)
include $(VFMW_DIR)/firmware/product/HiS5V200/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a),)
include $(VFMW_DIR)/firmware/product/Hi3798CV200/HD_FULL/vfmw_make.cfg
endif
EXTRA_CFLAGS += $(VFMW_CFLAGS)
EXTRA_CFLAGS += -fno-pic

ifeq ($(CFG_MSP_BUILDTYPE), y)
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VDEC_SVDEC_BUILTIN
endif
endif

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_vfmw

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := $(vfmw_obj_list)

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)cp -f $(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko
