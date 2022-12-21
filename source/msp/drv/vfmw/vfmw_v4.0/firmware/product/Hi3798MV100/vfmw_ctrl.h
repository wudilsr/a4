
#ifndef __VFMV_CTRL_H__
#define __VFMV_CTRL_H__
#include "vfmw.h"
#include "fsp.h"
#include "sysconfig.h"
#ifdef VFMW_H263_SUPPORT
#include "sdec_imedia.h"
#endif
#include "syntax.h"

/*======================================================================*/
/*  ����                                                                */
/*======================================================================*/
#define VCTRL_OK                0
#define VCTRL_ERR              -1
#define VCTRL_ERR_VDM_BUSY     -2
#define VCTRL_ERR_NO_FSTORE    -3
#define VCTRL_ERR_NO_STREAM    -4
#define MAX_FRAME_SIZE 			2048*2048

#define VCTRL_FIND_PTS          0
#define VCTRL_PTS_ILLEAGLE     -1
#define VCTRL_SEEKING_PTS      -2

#define VCTRL_USER_OPTION     0
#define VCTRL_ADD_EXTRA        1
#define VCTRL_IGNOR_EXTRA     2

#define MAX_USRDEC_FRAME_NUM        (16)
/*======================================================================*/
/*  �ṹ��ö��                                                          */
/*======================================================================*/
/* ֡�漯�ϣ����ڵ���: ��ѯ�ж���֡�棬�����ݷֱ�Ϊ�� */
typedef struct hiVFMWFrameARRAY
{
    SINT32       s32FrameNum;
    SINT32       s32PixWidth;
    SINT32       s32PixHeight;
    SINT32       s32Stride;
    SINT32       s32ChromOfst;
    SINT32       s32PhyAddr[64];
} VFMW_FRAME_ARRAY_S;

/* ͨ����ص�ͳ����Ϣ */
typedef struct hiVFMW_CHAN_STAT
{
    UINT32        u32FrBeginTime;   /* ����֡�ʵĿ�ʼʱ�� */
	UINT32        u32FrImgNum;      /* ֡�� */
	UINT32        u32FrFrameRate;   /* ֡�� */

	/* ��֡ͳ�� */
	UINT32        u32SkipFind;        /* �⵽��skip֡��Ŀ */
	UINT32        u32SkipDiscard;     /* ���������skip֡��Ŀ */
    UINT32        u32IsFieldFlag;     /* ��ǰ��������е�֡�ǳ�ͼ��־������PVR������˻�ȡ����֡������ */
	
    VFMW_FRAME_ARRAY_S stFrameArray;
} VFMW_CHAN_STAT_S;

typedef struct hiVFMW_GLOBAL_STAT
{
    /* VDMռ����ͳ�� */
    UINT32        u32VaBeginTime;     /* ͳ��VDMռ���ʵ���ʼʱ�� */
    UINT32        u32VaLastStartTime; /* ��һ������Ӳ����ʱ�� */
	UINT32        u32VaVdmWorkTime;   /* VDM�ۼƹ���ʱ�� */
	UINT32        u32VaVdmLoad;       /* VDMռ���� */

    /* DNRռ����ͳ�� */
    UINT32        u32DaBeginTime;     /* ͳ��VDMռ���ʵ���ʼʱ�� */
    UINT32        u32DaLastStartTime; /* ��һ������Ӳ����ʱ�� */
	UINT32        u32DaDnrWorkTime;   /* DNR�ۼƹ���ʱ�� */
	UINT32        u32DaDnrLoad;       /* DNRռ���� */

	/* BTLռ����ͳ�� */
    UINT32        u32BaBeginTime;     /* ͳ��BTLռ���ʵ���ʼʱ�� */
    UINT32        u32BaLastStartTime; /* ��һ������Ӳ����ʱ�� */
	UINT32        u32BaBtlWorkTime;   /* BTL�ۼƹ���ʱ�� */
	UINT32        u32BaBtlLoad;       /* BTLռ���� */

    /* VDM��������ͳ�� */
    UINT32        u32PicNum;
    UINT32        u32AccVdmKiloCycle;
    UINT32        u32VaVdmKiloCycle;
    UINT32        u32StatTime;
        /* SCDռ����ͳ�� */
    UINT32        u32SaBeginTime;     /* ͳ��SCDռ���ʵ���ʼʱ�� */
    UINT32        u32SaLastStartTime; /* ��һ������Ӳ����ʱ�� */
    UINT32        u32SaScdWorkTime;   /* SCD�ۼƹ���ʱ�� */
    UINT32        u32SaScdLoad;       /* SCDռ���� */   

	UINT32 	      u32IsVdhEn;
} VFMW_GLOBAL_STAT_S;

#if 0
typedef struct
{
    SYNTAX_EXTRA_DATA_S *pstExtraData;	
    IMAGE_VO_QUEUE     ImageQue;
    SINT32        	   ChanID;
} USER_CTX_S;
#endif

/* ArrangeMem�������ô��ݵ�ָʾ������ */
typedef enum
{
    CAP_HEVC_SPECIFIC     = -2,
    INVALID_CHAN_ID       = -1,   
    VALID_CHAN_ID_START   = 0,  
} ARRANGE_FLAG_E;

typedef enum
{
    VDM_SUPPORT_VP6       = 1,  /* 1<<0 */
    VDM_SUPPORT_BPD       = 2,  /* 1<<1 */
    VDM_SUPPORT_VCMP      = 4,  /* 1<<2 */
    VDM_SUPPORT_GMC       = 8,   /* 1<<3 */    
    VDM_SUPPORT_DNR       = 16   /* 1<<4 */        
} VDM_CHARACTER_E;

/* �̵߳�״̬ */
typedef enum hiTASKSTATE_E
{
    TASK_STATE_EXIT = 0,        /* �˳�, �߳�δ������������ */
    TASK_STATE_STOP,            /* ֹͣ���߳��Ѵ��������ڿ�ת������ֹͣ */
    TASK_STATE_RUNNING,         /* ���� */
    TASK_STATE_BUTT
} TASK_STATE_E;

/* ���̷߳�����ָ�� */
typedef enum hiTASKCMD_E
{
    TASK_CMD_NONE = 0,        /* ��ָ�� */
    TASK_CMD_START,           /* ����ָ���������ֹͣ״̬���߳� */
    TASK_CMD_STOP,            /* ָֹͣ�ֹͣ��������״̬���߳� */
    TASK_CMD_KILL,            /* ����ָ�ʹ�������л�ֹͣ״̬���߳���Ȼ�˳� */
    TASK_CMD_BUTT
} TASK_CMD_E;

/* ͨ���Ľ������ */
typedef enum hiChanDecCore
{
    DEC_CORE_VDM,
	DEC_CORE_IMEDIA_H263,
	DEC_CORE_IMEDIA_SORENSON,
	DEC_CORE_IMEDIA_VP6,
    DEC_CORE_IMEDIA_VP6F,
    DEC_CORE_IMEDIA_VP6A,
	DEC_CORE_BUTT
} CHAN_DEC_CORE_E;

/* ���һ֡״̬���� */
typedef enum hiLastFrameState
{
    LAST_FRAME_INIT = 0,
    LAST_FRAME_RECEIVE,
    LAST_FRAME_REPORT_SUCCESS,
    LAST_FRAME_REPORT_FAILURE,
    LAST_FRAME_REPORT_FRAMEID,
	LAST_FRAME_BUTT
} LAST_FRAME_STATE_E;

/*l00273086 ͨ������״̬*/
typedef enum
{
    CHAN_NORMAL,  //ͨ������Run
    CHAN_FRAME_STORE_ALLOC, //ͨ�����ڷ���֡��
    CHAN_DESTORY,    //ͨ����������         
} VFMW_CHANNEL_CONTROL_STATE_E;

typedef struct hiDRV_MEM_S
{
    MEM_RECORD_S  stVdmHalMem[MAX_VDH_NUM];      /* VDM HAL�ڴ� */
    MEM_RECORD_S  stScdCmnMem[MAX_SCD_NUM];      /* SCD �����ڴ� */
//    MEM_RECORD_S  stFodCmnMem;      /* FOD �����ڴ� */
    MEM_RECORD_S  stBTLReg;
    MEM_RECORD_S  stVdmReg[MAX_VDH_NUM];
    MEM_RECORD_S  stFodReg;
    MEM_RECORD_S  stScdReg[MAX_SCD_NUM];
    MEM_RECORD_S  stBpdReg;
    MEM_RECORD_S  stSystemReg;      /* ϵͳ�Ĵ��������縴λFOD,VDM,SCD�� */
} DRV_MEM_S;

typedef struct hiDRV_IRQ_RECORD_S
{
    SINT32 VdhIrq[MAX_VDH_NUM];
    SINT32 ScdIrq[MAX_SCD_NUM];
    SINT32 DnrIrq;
    SINT32 BtlIrq;
}DRV_IRQ_RECORD_S;

/* �������������ݼ� */
typedef struct hiVFMW_CTRL_DATA_S
{
    SINT32        s32IsVCTRLOpen;   /* ��־VCTRL�Ƿ�ȫ�ִ� */
    OSAL_TASK_MUTEX stDecMutex;
    OSAL_EVENT    eventVdmReady;

    TASK_STATE_E  eTaskState;       /* �߳�״̬ */
    TASK_CMD_E    eTaskCommand;     /* �߳�ָ�� */
    OSAL_TASK     hThread;          /* �߳̾�� */

    SINT32        s32ThreadPos;    /* �߳�λ�� */

    SINT32        s32ThisChanIDPlus1;    /* ��ǰ���ڽ����﷨�����ͨ���� */
    DRV_MEM_S     stDrvMem;
    SINT32        (*event_report_vdec)(SINT32 ChanID, SINT32 type, VOID* p_args );
    SINT32        (*event_report_omxvdec)(SINT32 ChanID, SINT32 type, VOID* p_args );
    DRV_IRQ_RECORD_S stIrqRecord;  
} VFMW_CTRL_DATA_S;

typedef struct hiVFMW_CHAN_FRM_BUF_S
{
    MEM_RECORD_S stFrameBuffer;
    UINT8 u8BufferNodeState; //0:Ԥ����õ��Ľڵ�, 1:��̬����õ��Ľڵ�,0xFF:���нڵ�
} VFMW_CHAN_FRM_BUF_S; //l00273086
////l00273086
/* ����ͨ���ڴ��¼ */
typedef struct hiVFMW_CHAN_MEM_S
{
    MEM_RECORD_S   stChanMem;       /* ��ͨ���Ĵ洢��Դ */

    MEM_RECORD_S   stChanMem_vdh;       /* ��ͨ����֡��洢��Դ */
    MEM_RECORD_S   stChanMem_scd;       /* ��ͨ����SCD�洢��Դ */
    MEM_RECORD_S   stChanMem_ctx;       /* ��ͨ���������Ĵ洢��Դ */ 
    MEM_RECORD_S   stChanMem_dsp;       /* ��ͨ����DSP�����Ĵ洢��Դ */
    
    SINT32         s32SelfAllocChanMem_vdh;  /* ��ʶͨ�� vdh �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_scd;  /* ��ʶͨ�� scd �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_ctx;  /* ��ʶͨ�� ctx �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    STREAM_INTF_S  stStreamIntf;    /* �����ӿ� */	
    UINT32          u32DynamicAllocEn; /*�Ƿ�Ϊ��̬֡�淽ʽl00273086*/
    VFMW_CHAN_FRM_BUF_S* pstChanFrmBuf;//l00273086
} VFMW_CHAN_MEM_S;
//l00273086
typedef struct hiVFMW_MEM_ARRANGE_INFO_S
{
    VDMHAL_MEM_ARRANGE_S stMemArrange;
    SINT32 ImgSlotLen;
    SINT32 PmvSlotLen;
} VFMW_MEM_ARRANGE_INFO_S;

typedef struct hiVFMW_DYNAMIC_FS_TIMESTAMP_S
{
    UINT32 u32StartTime;
    UINT32 u32PreEndTime;
    UINT32 u32MMZEndTime;
    UINT32 u32PreAllocTime;
    UINT32 u32MMZAllocTime;
    UINT32 u32AllTime;
} VFMW_DYNAMIC_FS_TIMESTAMP_S;
//l00273086 end

/* ����ͨ�� */
typedef struct hiVFMW_CHAN_S
{
    SINT32         s32BtlMemAddr;
	SINT32         s32BtlMemSize;
    SINT32         s32ChanID;       /* ͨ��ID */
    SINT32         s32IsOpen;       /* 0: δ�򿪣�1: �� */
    SINT32         s32IsRun;        /* 0: ��������, 1: ���У��ɱ�����  */
    SINT32         s32IsInit;       /* 0: ��������״̬, 1: �ճ�ʼ����δ����*/
    SINT32         s32Priority;     /* ���ȼ���0��������ȼ�(�Ӳ�����) ~ 255(������ȼ��������ȵ���) */
    SINT32         s32StopSyntax;  /* ͣ��syntax���룬������stopͨ����ʱ����ͣ���Σ��������������У���������
                                        ��DecParam���ĸɾ����Ӷ�ʵ�ְ�ȫ��ͨ��stop��reset���� */
    SINT32         MatchVdhIdPlus1;  //��¼��ǰͨ��ƥ���Vdhid +1; -1->��ͨ��DSP��������δ���������ܴ�����0->���ʹ��VDH���룻1->�̶�ѡ��VDH0���룻2->�̶�ѡ��VDH1����...;                                     
    VDEC_ADAPTER_TYPE_E   eAdapterType;   /* ָʾ��ͨ������vdec/omxvdec���� */
    VDEC_CHAN_CAP_LEVEL_E eChanCapLevel;  /* ͨ������������ */
    UINT32         u32timeLastDecParamReady;
	
    VDEC_CHAN_CFG_S     stChanCfg;       /* �����û����ã����ڲ�ѯ�ӿ�ʵ�� */
    STREAM_INTF_S  stStreamIntf;    /* �����ӿ� */
    IMAGE_INTF_S   stImageIntf;     /* ͼ��ӿ� */
	FRAME_INTF_S   stFrameIntf;

    SINT32         s32SCDInstID;    /* ��ͨ����Ӧ��SCDʵ��ID */
    SINT32         s32VDMInstID;    /* ��ͨ����Ӧ��VDMʵ��ID */
    SINT32         s32FODInstID;    /* ��ͨ����Ӧ��FODʵ��ID */

    SINT32         s32OneChanMem;  /*��ͨ���ڴ����ⲿ����Ϊһ�飬ӳ��Ȳ���ʱ��Ҫ��Ϊ����������*/
    MEM_RECORD_S   stChanMem;       /* ��ͨ���Ĵ洢��Դ */

//    SINT32         s32CreatWithMem;     /* 1:��ͨ���ڴ���Դ���ⲿ���롢�ⲿ�ͷ� */
    MEM_RECORD_S   stChanMem_vdh;       /* ��ͨ����֡��洢��Դ */
    MEM_RECORD_S   stChanMem_scd;       /* ��ͨ����SCD�洢��Դ */
    MEM_RECORD_S   stChanMem_ctx;       /* ��ͨ���������Ĵ洢��Դ */ 
    
//    SINT32         s32SelfAllocChanMem;  /* ��ʶͨ���洢��Դ�Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_vdh;  /* ��ʶͨ�� vdh �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_scd;  /* ��ʶͨ�� scd �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_ctx;  /* ��ʶͨ�� ctx �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32VdmChanMemAddr;
    SINT32         s32VdmChanMemSize;    /* VDMͨ����ռ�ݵĴ洢�ռ��С */
	SINT32         s32OffLineDnrMemAddr;
	SINT32         s32OffLineDNRMemSize; /* ����DNR��ռ�ݵĴ洢�ռ��С  */
    SINT32         s32ScdChanMemAddr;
    SINT32         s32SdecMemAddr;       /* ��������ʹ�õĴ洢�ռ䣬ΪDNR+VDM�Ŀռ� */
    SINT32         s32SdecMemSize;
    SINT32         s32ScdChanMemSize;    /* SCDͨ����ռ�ݵĴ洢�ռ��С */

    SINT32         s32BpdChanMemAddr;
    SINT32         s32BpdChanMemSize;    /* BPDͨ����ռ�ݵĴ洢�ռ��С */

    SINT32         s32Vp8SegIdChanMemAddr;
    SINT32         s32Vp8SegIdChanMemSize;    /* SegIdͨ����ռ�ݵĴ洢�ռ��С */	
	
	//IMAGE          stRecentImg;     /* ����IMAGE�ṹ�� */
    UINT32         stRecentImgformat;
    FRAME_PACKING_TYPE_E  stRecentImgPackingType;

    SINT32         s32NoStreamFlag; /* ���ڸ�ͨ��û���㹻��������δ�����ɽ������decparam */
    SINT32         s32LastFrameIdPlus2;  /* ���һ֡���ʱ�����ڼ�¼���һ֡��image_id + 2 ��1D ת2Dʱ������BTL/DNR���õ�*/
    LAST_FRAME_STATE_E eLastFrameState;  /* �������һ֡��ǵ�״̬ */

    SINT32         s32CountNoDecparamFlag; /* ����û�н��������ʼ��ʱ��־ */    
    UINT32         u32NoDecparamStartTime;
	
    /* �û�̬������Ҫ��VDM memory��֡ӳ����ȥ. ����ʱ�γɷָ������Ϣ��¼֡��ķָ��ʹ��״�� */
    SINT32         s32UsrdecFrameUsed[MAX_USRDEC_FRAME_NUM];
    SINT32         s32UsrdecFramePhyAddr[MAX_USRDEC_FRAME_NUM];
    SINT32         s32UsrdecFrameSize;
    SINT32         s32UsrdecFrameNum;
    USRDEC_FRAME_DESC_S  stRecentUsrdecFrame;

    VID_STD_E      eVidStd;
	
    SYNTAX_EXTRA_DATA_S stSynExtraData;
	CHAN_DEC_CORE_E eDecCore;
    SM_INSTANCE_S   SmInstArray;
    FSP_INST_S      FspInst;
    //l00273086 start
    SINT32 s32CurFsSize;
    SINT32 s32RefNum; 
    SINT32 s32NeededFrameNum;
    SINT32 s32PreAllocFrmNum;
    SINT32 s32MMZFrmNum;
    SINT32 s32NeedMMZ;
    SINT32 s32RefNumChanged;    
	SINT32 s32SendStreamAgainFlag;
    VFMW_CHAN_FRM_BUF_S stFrmBuf[MAX_FRAME_NUM];
    VFMW_MEM_ARRANGE_INFO_S stMemArrangeInfo;
    VFMW_DYNAMIC_FS_TIMESTAMP_S stDynamicFSTimestamp;
    //l00273086 end
    UINT32 u32DynamicFrameStoreAllocEn;
    UINT32 u32CurSavePicBitDepth;
	SINT32 s32H264Score;
	SINT32 s32Mpeg2Score;
	SINT32 s32FindStartCodeCnt;
	SINT32 s32LastTwoStartCode;
	SINT32 s32LastOneStartCode;
	SINT32 s32CurrentStartCode;
    SYNTAX_CTX_S   stSynCtx;//�˳�Ա����������һ������,����ͨ��ʱ��ʹmvc support���������õ�����������mvc��صģ��ýṹ���ڴ�Ҳֻ����δ��CTX���裬�Դﵽ�ڴ�ü�Ŀ�ġ� l00225186

} VFMW_CHAN_S;

/* �̵߳�״̬ */
typedef enum hiDSPSTATE_E
{
    DSP_STATE_NORMAL = 0,      /* DSP ��û�м����κδ���  */
    DSP_STATE_SCDLOWDLY,       /* DSP �Ѿ�������SCD���ӵĴ��룬˵������һ��ͨ�����ڵ��ӳ�ģʽ */
    DSP_STATE_AVS,             /* DSP �Ѿ�������AVS+�Ĵ��룬˵������һ��ͨ��������AVSЭ�� */
    DSP_STATE_BUTT
} DSP_STATE_E;

/*======================================================================*/
/*  ȫ�ֱ���                                                            */
/*======================================================================*/
extern VFMW_CHAN_STAT_S g_VfmwChanStat[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern SINT32 g_VdmCharacter;
extern VDM_VERSION_E g_eVdmVersion;
extern SINT32  (*AcceleratorCharacter)(DECPARAM_INF_S *pDecParamInfo); 

/*======================================================================*/
/*  ��������                                                            */
/*======================================================================*/
SINT32 VCTRL_SetCallBack(VDEC_ADAPTER_TYPE_E eType, SINT32 (*event_report)(SINT32 ChanID, SINT32 type, VOID* p_args));
SINT32 VCTRL_OpenVfmw(VOID);
SINT32 VCTRL_StopTask(VOID);
SINT32 VCTRL_StartTask(VOID);
SINT32 VCTRL_CloseVfmw(VOID);
VOID   VCTRL_Suspend(VOID);
VOID   VCTRL_Resume(VOID);
SINT32 VCTRL_CreateChan(VDEC_CHAN_CAP_LEVEL_E eCapLevel, MEM_DESC_S *pChanMem);
SINT32 VCTRL_CreateChanWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, SINT32 flag, SINT32 OneChanMemFlag);
SINT32 VCTRL_DestroyChan(SINT32 ChanID);
SINT32 VCTRL_DestroyChanWithOption(SINT32 ChanID);
SINT32 VCTRL_StartChan(SINT32 ChanID);
SINT32 VCTRL_StartChanWithOption(SINT32 ChanID, MEM_DESC_S*  pChanMemVdh);
SINT32 VCTRL_StopChan(SINT32 ChanID);
SINT32 VCTRL_StopChanWithCheck(SINT32 ChanID);
SINT32 VCTRL_GetChanCfg(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_CmpConfigParameter(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ConfigChan(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ResetChanWithOption(SINT32 ChanID, VDEC_CHAN_RESET_OPTION_S *pOption);
SINT32 VCTRL_ReleaseStream(SINT32 ChanID);
SINT32 VCTRL_ResetChan(SINT32 ChanID);
SINT32 VCTRL_GetChanMemSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32 *VdmMemSize, SINT32 *ScdMemSize);
VOID   VCTRL_GetChanState(SINT32 ChanID, VDEC_CHAN_STATE_S *pstChanState);
SINT32 VCTRL_SetSendStreamAgainFlag( SINT32 ChanID, SINT32 flag);
SINT32 VCTRL_GetSendStreamAgainFlag( SINT32 ChanID);
SINT32 VCTRL_SetStreamInterface( SINT32 ChanID, VOID *pstStreamIntf );
STREAM_INTF_S *VCTRL_GetStreamInterface(SINT32 ChanID);
SINT32 VCTRL_SetFrameInterface( SINT32 ChanID, FRAME_INTF_S *pstFrameIntf );
FRAME_INTF_S *VCTRL_GetFrameInterface( SINT32 ChanID);

VOID  *VCTRL_GetSyntaxCtx(SINT32 ChanID);
IMAGE_INTF_S *VCTRL_GetImageInterface(SINT32 ChanID);
SINT32 VCTRL_GetChanMemSizeWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, DETAIL_MEM_SIZE *pDetailMemSize,SINT32 flag);
VOID   VCTRL_GetChanCtxSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32* s32ChanCtxSize);
SINT32 VCTRL_GetStreamSize(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_SetDiscardPicParam(SINT32 ChanID, VDEC_DISPIC_PARAM_S *pArgs);    //add by z00222166, 2012.11.20
UINT32 VCTRL_ArrangeMem(SINT32 ChanID, SINT32 MaxWidth, SINT32 MaxHeight, SINT32 MemAddr, SINT32 MemSize);

#ifdef VFMW_BVT_SUPPORT
SINT32 VCTRL_SetFspFrameInterface(FSP_FRAME_INTF_S *pstFspFrameIntf);
#endif

#ifdef VFMW_USER_SUPPORT
SINT32 VCTRL_GetUsrdecFrame(SINT32 ChanID, MEM_DESC_S *pMem);
SINT32 VCTRL_PutUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pUsrdecFrame);
SINT32 USERDEC_Init(USER_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData);
SINT32 USERDEC_RecycleImage(USER_CTX_S *pCtx,UINT32 ImgID);
SINT32 VDH_PutUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pstUsrdecFrame);
#endif

SINT32 VCTRL_ChanDecparamInValidFlag(SINT32 ChanId);

VID_STD_E VCTRL_GetVidStd(SINT32 ChanId);
VOID  *VCTRL_GetDecParam(SINT32 ChanId);
VOID   VCTRL_VdmPostProc( SINT32 ChanId, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic, LUMA_INFO_S *pLumaInfo,SINT32 VdhId);

SINT32 VCTRL_GetChanImage( SINT32 ChanID, IMAGE *pImage );
SINT32 VCTRL_ReleaseChanImage( SINT32 ChanID, IMAGE *pImage );

SINT32 VCTRL_RunProcess(VOID);
VOID   VCTRL_InformVdmFree(SINT32 ChanID);
VOID   VCTRL_ExtraWakeUpThread(VOID);
SINT32 VCTRL_FlushDecoder(SINT32 ChanID);
SINT32 VCTRL_GetImageBuffer( SINT32 ChanId );
SINT32 VCTRL_GetChanIDByCtx(VOID *pCtx);
SINT32 VCTRL_GetChanIDByMemAddr(SINT32 PhyAddr);
SINT32 VCTRL_IsChanDecable( SINT32 ChanID );
SINT32 VCTRL_IsChanSegEnough( SINT32 ChanID );
SINT32 VCTRL_IsChanActive( SINT32 ChanID );
VOID VCTRL_GetChanImgNum( SINT32 ChanID, SINT32 *pRefImgNum, SINT32 *pReadImgNum, SINT32 *pNewImgNum );
VDEC_CHAN_CAP_LEVEL_E  VCTRL_GetChanCapLevel(SINT32 ChanID);

#ifdef VFMW_H263_SUPPORT
SINT32 VCTRL_RegisterSoftDecoder(iMediaSDEC_FUNC_S *pstSdecFunc);
VOID   VCTRL_UnRegisterSoftDecoder(VOID);
#endif

SINT32 VCTRL_ExtAccGetDecParam(DECPARAM_INF_S * pDecParamInfo);
VOID   VCTRL_ExtAccPostProcess(SINT32 ChanID, SINT32 ErrorRatio, HI_U32 u32LumaPixSum);

SINT32 VCTRL_SetMoreGapEnable(SINT32 ChanID, SINT32 MoreGapEnable);

VOID   VCTRL_MaskAllInt(VOID);
VOID   VCTRL_EnableAllInt(VOID);
SINT32 VCTRL_SeekPts(SINT32 ChanID, UINT64 *pArgs);

#if defined(VFMW_SCD_LOWDLY_SUPPORT) || defined(VFMW_AVSPLUS_SUPPORT)
SINT32 VCTRL_LoadDspCode(SINT32 ChanID);
SINT32 VCTRL_ReloadDspCode(SINT32 ChanID);
#endif

SINT32 VCTRL_ConfigFFFBSpeed(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_ConfigPVRInfo(SINT32 ChanID, VFMW_CONTROLINFO_S *pArgs);

SINT32 VCTRL_GetChanMemInfo(SINT32 ChanId, MEM_RECORD_S *pstMemRec);
SINT32 VCTRL_SetDbgOption ( UINT32 opt, UINT8* p_args );

SINT32 VCTRL_GetChanWidth(SINT32 ChanID);
SINT32 VCTRL_GetChanHeight(SINT32 ChanID);
VOID   VCTRL_SetVdecExtra(SINT32 new_extra_ref, SINT32 new_extra_disp);

SINT32 VCTRL_GetLastFrameIdPlus2(SINT32 ChanID);
VOID   VCTRL_SetLastFrameIdPlus2(SINT32 ChanID, SINT32 Value);      
VOID VCTRL_SetLastFrameState(SINT32 ChanID, LAST_FRAME_STATE_E eState);       

SINT32 VCTRL_OutputLastFrame(SINT32 ChanId);  
VOID   VCTRL_SvdecLastFrame(SINT32 ChanId, UINT32 LastFrameID);

UINT32 VCTRL_GetImageWidth(SINT32 ChanId);
UINT32 VCTRL_GetImageHeight(SINT32 ChanId);
//l00273086
SINT32 VCTRL_RequestChanMem(SINT32 ChanID);
SINT32 VCTRL_RlsAllFrameNode(SINT32 ChanID); 
SINT32 VCTRL_GetCurChanFsSize(SINT32 ChanID);
SINT32 VCTRT_SetChanCtrlState(SINT32 ChanID, VFMW_CHANNEL_CONTROL_STATE_E ChanCtrlState);
VOID   VCTRL_SetFsParamToChan(SINT32 ChanID, VDEC_CHAN_FRAME_STORE_PARAM_S* ChanMem);
VOID   VCTRL_SetChanFsPartitionState(SINT32 ChanID, FSP_PARTITION_STATE_E state);
VOID   VCTRL_OpenHardware(SINT32 ChanID);
VOID   VCTRL_CloseHardware(VOID);

#ifdef ENV_ARMLINUX_KERNEL
int   vfmw_proc_init(void);
void  vfmw_proc_exit(void);
#else
#define IRQ_HANDLED 0
#endif

#endif
