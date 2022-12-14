/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : hi_drv_pq.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Description   :
******************************************************************************/

#ifndef __HI_DRV_PQ_V3_H__
#define __HI_DRV_PQ_V3_H__

#include <linux/ioctl.h>
#include "hi_module.h"

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_pq_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define HI_FATAL_PQ(fmt...) HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_PQ, fmt)
#define HI_ERR_PQ(fmt...)   HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_PQ, fmt)
#define HI_WARN_PQ(fmt...)  HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_PQ, fmt)
#define HI_INFO_PQ(fmt...)  HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_PQ, fmt)
#define HI_DEBUG_PQ(fmt...) HI_TRACE(HI_LOG_LEVEL_DBG, HI_ID_PQ, fmt)
#else
#define HI_FATAL_PQ(fmt...)
#define HI_ERR_PQ(fmt...)
#define HI_WARN_PQ(fmt...)
#define HI_INFO_PQ(fmt...)
#define HI_DEBUG_PQ(fmt...)
#endif


/* ????ģʽ */
typedef enum hiPQ_DEMO_E
{
    HI_PQ_DEMO_DB = 0    ,
    HI_PQ_DEMO_DR        ,
    HI_PQ_DEMO_DM        ,
    HI_PQ_DEMO_DBM       ,
    HI_PQ_DEMO_NR        ,
    HI_PQ_DEMO_SHARPNESS ,
    HI_PQ_DEMO_DCI       ,
    HI_PQ_DEMO_COLOR     ,
    HI_PQ_DEMO_SR        ,
    HI_PQ_DEMO_TNR       ,
    HI_PQ_DEMO_DEI       ,
    HI_PQ_DEMO_ALL       ,

    HI_PQ_DEMO_BUTT
}  HI_PQ_DEMO_E;

/* PQģ?? */
typedef enum hiHIPQ_MODULE_E
{
    HI_PQ_MODULE_FMD = 0      ,
    HI_PQ_MODULE_TNR          ,
    HI_PQ_MODULE_SNR          ,
    HI_PQ_MODULE_DB           ,
    HI_PQ_MODULE_DR           ,
    HI_PQ_MODULE_DM           ,
    HI_PQ_MODULE_DBM          ,
    HI_PQ_MODULE_HSHARPNESS   ,
    HI_PQ_MODULE_SHARPNESS    ,
    HI_PQ_MODULE_CCCL         ,
    HI_PQ_MODULE_DCI          ,
    HI_PQ_MODULE_COLOR        ,
    HI_PQ_MODULE_SR           ,
    HI_PQ_MODULE_FRC          ,
    HI_PQ_MODULE_ALL          ,

    HI_PQ_MODULE_BUTT
}  HI_PQ_MODULE_E;

/*????/?Աȶ?/ɫ??/???Ͷ??趨*/
typedef struct hiPQ_IMAGE_PARAM_S
{
    HI_U16 u16Brightness;
    HI_U16 u16Contrast;
    HI_U16 u16Hue;
    HI_U16 u16Saturation;

} HI_PQ_IMAGE_PARAM_S;

/*
 * ģ?鿪??????
 */
typedef struct hiPQ_MODULE_S
{
    HI_PQ_MODULE_E enModule;
    HI_U32 u32OnOff; /*????*/
} HI_PQ_MODULE_S;

/*
 * ????ģʽ????
 */
typedef struct hiPQ_DEMO_S
{
    HI_PQ_DEMO_E enModule;
    HI_BOOL bOnOff; /*????*/
} HI_PQ_DEMO_S;

/* ????ģʽ ??ʾ??ʽ*/
typedef enum hiPQ_DEMO_MODE_E
{
    HI_PQ_DEMO_MODE_FIXED_R = 0,
    HI_PQ_DEMO_MODE_FIXED_L,
    HI_PQ_DEMO_MODE_SCROLL_R,
    HI_PQ_DEMO_MODE_SCROLL_L,

    HI_PQ_DEMO_MODE_BUTT
} HI_PQ_DEMO_MODE_E;

/*
 * ?Ĵ???????
 */
typedef struct hiPQ_REGISTER_S
{
    HI_U32 u32RegAddr;     /* register addr */
    HI_U8  u8Lsb;          /* register lsb */
    HI_U8  u8Msb;          /* register msb */
    HI_U8  u8SourceMode;   /* video source */
    HI_U8  u8OutputMode;   /* output mode */
    HI_U32 u32Module;      /* module */
    HI_U32 u32Value;       /* register value */
} HI_PQ_REGISTER_S;

/*ACM ?Ĵ??????Ʋ????ṹ*/
typedef struct hiPQ_COLOR_CTRL_S
{
    HI_U32 u32En;
    HI_U32 u32DbgEn;
    HI_U32 u32Stretch;
    HI_U32 u32Cliprange;
    HI_U32 u32Cliporwrap;
    HI_U32 u32Cbcrthr;
} HI_PQ_COLOR_CTRL_S;

/*ACM table?ṹ*/
typedef struct hiPQ_DRV_ACM_LUT_S
{
    HI_U32 u32LutType;           /*ACM ???ұ?????????*/
    HI_S16 as16Lut[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /*ACM ???ұ?*/
} HI_PQ_ACM_LUT_S;

/*DCI???????ñ?*/
typedef struct hiPQ_DCI_WGT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} HI_PQ_DCI_WGT_S;

/*DCIֱ??ͼ?ṹ*/
typedef struct hiPQ_DCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} HI_PQ_DCI_HISTGRAM_S;

/*TNRͨ?ýṹ*/
typedef struct hiPQ_TNR_S
{
    HI_S32 s32MappingMax;
    HI_S32 s32MappingMin;
    HI_S32 s32MappingR[5];
    HI_S32 s32MappingT[6];
    HI_S32 s32MappingK[4];
} HI_PQ_TNR_S;

/* YFmotion ??ӳ??????  */
typedef struct hiPQ_TNR_FMOTION_S
{
    HI_S16 s16YFmotion[32];
    HI_S16 s16CFmotion[32];
} HI_PQ_TNR_FMOTION_S;


/*SNR??pixmean-ratio?ṹ*/
typedef struct hiPQ_SNR_PIXMEAN_2_RATIO_S
{
    HI_U8 u8EdgeMaxRatio;
    HI_U8 u8EdgeMinRatio;
    HI_U8 u8EdgeOriRatio;
    HI_U8 u8Reserve;
    HI_U16 u16EdgeMeanTh[8];
    HI_U8 u8EdgeMeanK[8];
    HI_U16 u16PixMeanRatio[8];
} HI_PQ_SNR_PIXMEAN_2_RATIO_S;

/*SNR ??pixdiff-edgestr?ṹ*/
typedef struct hiPQ_SNR_PIXDIFF_2_EDGESTR_S
{
    HI_U8 u8EdgeOriStrength;
    HI_U8 u8EdgeMaxStrength;
    HI_U8 u8EdgeMinStrength;
    HI_U8 u8Reserve1;
    HI_U16 u16EdgeStrTh[3];
    HI_U16 u16Reserve2;
    HI_U8 u8EdgeStrK[3];
    HI_U8 u8Reserve3;
    HI_U8 u8EdgeStr[3];
    HI_U8 u8Reserve4;
} HI_PQ_SNR_PIXDIFF_2_EDGESTR_S;

/*SR??ʾģʽ*/
typedef enum hiPQ_SR_DEMO_E
{
    HI_PQ_SR_DISABLE  = 0,/* ??SR,ֻZME */
    HI_PQ_SR_ENABLE_R,    /* ?ұ?SR */
    HI_PQ_SR_ENABLE_L,    /* ????SR */
    HI_PQ_SR_ENABLE_A,    /* ȫ?? */

    HI_PQ_SR_DEMO_BUTT
} HI_PQ_SR_DEMO_E;

typedef struct hiPQ_SIX_BASE_COLOR_S
{
    HI_U32  u32Red;
    HI_U32  u32Green;
    HI_U32  u32Blue;
    HI_U32  u32Cyan;
    HI_U32  u32Magenta;
    HI_U32  u32Yellow;
} HI_PQ_SIX_BASE_COLOR_S;

/*ACM GAIN ??Ϣ?ṹ*/
typedef struct hiPQ_COLOR_GAIN_S
{
    HI_U32 u32GainMode;   /* 0:SD;1:HD;2:UHD */
    HI_U32 u32Gainluma;   /* ??ʾ??Hue?????棬Range:0-1023 */
    HI_U32 u32Gainhue;    /* ??ʾ??Hue?????棬Range:0-1023 */
    HI_U32 u32Gainsat;    /* ??ʾ??Luma?????? */
} HI_PQ_COLOR_GAIN_S;

/*??ɫ??ǿ????*/
typedef enum hiPQ_COLOR_ENHANCE_E
{
    HI_PQ_COLOR_ENHANCE_FLESHTONE = 0,    /* ??ɫ??ǿ */
    HI_PQ_COLOR_ENHANCE_SIX_BASE,         /* ????ɫ??ǿ,?Զ?????ɫ????ǿ */
    HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE,  /* ?̶?ģʽ????ɫ??ǿģʽ */
    HI_PQ_COLOR_ENHANCE_BUTT
} HI_PQ_COLOR_ENHANCE_E;

/*????ɫ??ǿ????*/
typedef struct  hiPQ_SIX_BASE_S
{
    HI_U32  u32Red;       /* Range:0~100 */
    HI_U32  u32Green;     /* Range:0~100 */
    HI_U32  u32Blue;      /* Range:0~100 */

    HI_U32  u32Cyan;      /* Range:0~100 */
    HI_U32  u32Magenta;   /* Range:0~100 */
    HI_U32  u32Yellow;    /* Range:0~100 */
} HI_PQ_SIX_BASE_S;


/*??ɫ????????*/
typedef enum hiPQ_FLESHTONE_E
{
    HI_PQ_FLESHTONE_GAIN_OFF = 0,
    HI_PQ_FLESHTONE_GAIN_LOW,
    HI_PQ_FLESHTONE_GAIN_MID,
    HI_PQ_FLESHTONE_GAIN_HIGH,

    HI_PQ_FLESHTONE_GAIN_BUTT
}  HI_PQ_FLESHTONE_E;


/*??ɫ??ǿ????*/
typedef enum hiPQ_COLOR_SPEC_MODE_E
{
    HI_PQ_COLOR_MODE_RECOMMEND = 0, /* ?Ƽ?????ɫ??ǿģʽ */
    HI_PQ_COLOR_MODE_BLUE,          /* ?̶?????ɫ??ǿģʽ */
    HI_PQ_COLOR_MODE_GREEN,         /* ?̶?????ɫ??ǿģʽ */
    HI_PQ_COLOR_MODE_BG,            /* ?̶???????ɫ??ǿģʽ */
    HI_PQ_COLOR_MODE_BUTT
} HI_PQ_COLOR_SPEC_MODE_E;


/*??ɫ??ǿ????*/
typedef struct  hiPQ_COLOR_ENHANCE_S
{
    HI_PQ_COLOR_ENHANCE_E    enColorEnhanceType; /* ɫ????ǿ???? */
    union
    {
        HI_PQ_FLESHTONE_E    enFleshtone;        /* ??ɫ??ǿ???? */
        HI_PQ_SIX_BASE_S     stSixBase;          /* ????ɫ??ǿ???? */
        HI_PQ_COLOR_SPEC_MODE_E   enColorMode;   /* ?̶?????ɫ??ǿģʽ */

    } unColorGain;
} HI_PQ_COLOR_ENHANCE_S;

/*?û??ӿ?*/
//#define HIIOC_PQ_S_COLORTEMP            _IOW(HI_ID_PQ, 1, HI_PQ_COLOR_TEMP_S)         /* ????ɫ?²???*/
//#define HIIOC_PQ_G_COLORTEMP            _IOR(HI_ID_PQ, 2, HI_PQ_COLOR_TEMP_S)         /* ??ȡɫ?²???*/

#define HIIOC_PQ_S_SD_BRIGHTNESS        _IOW(HI_ID_PQ, 3, HI_U32)                     /* ???ñ???BRIGHTNESS level*/
#define HIIOC_PQ_G_SD_BRIGHTNESS        _IOR(HI_ID_PQ, 4, HI_U32)                     /* ??ȡ????BRIGHTNESS level*/

#define HIIOC_PQ_S_SD_CONTRAST          _IOW(HI_ID_PQ, 5, HI_U32)                     /* ???ñ???CONTRAST level*/
#define HIIOC_PQ_G_SD_CONTRAST          _IOR(HI_ID_PQ, 6, HI_U32)                     /* ??ȡ????CONTRAST level*/

#define HIIOC_PQ_S_SD_SATURATION        _IOW(HI_ID_PQ, 7, HI_U32)                     /* ???ñ???SATURATION level*/
#define HIIOC_PQ_G_SD_SATURATION        _IOR(HI_ID_PQ, 8, HI_U32)                     /* ??ȡ????SATURATION level*/

#define HIIOC_PQ_S_SD_HUE               _IOW(HI_ID_PQ, 9, HI_U32)                     /* ???ñ???HUE level*/
#define HIIOC_PQ_G_SD_HUE               _IOR(HI_ID_PQ, 10, HI_U32)                    /* ??ȡ????HUE level*/

#define HIIOC_PQ_S_TNR                  _IOW(HI_ID_PQ, 11, HI_U32)                    /* ????TNR level*/
#define HIIOC_PQ_G_TNR                  _IOR(HI_ID_PQ, 12, HI_U32)                    /* ??ȡTNR level*/

#define HIIOC_PQ_S_SHARPNESS            _IOW(HI_ID_PQ, 13, HI_U32)                    /* ????SHARPNESS level*/
#define HIIOC_PQ_G_SHARPNESS            _IOR(HI_ID_PQ, 14, HI_U32)                    /* ??ȡSHARPNESS level*/

#define HIIOC_PQ_S_DB                   _IOW(HI_ID_PQ, 15, HI_U32)                    /* ????De-blocking level*/
#define HIIOC_PQ_G_DB                   _IOR(HI_ID_PQ, 16, HI_U32)                    /* ??ȡDe-blocking level*/

#define HIIOC_PQ_S_DR                   _IOW(HI_ID_PQ, 17, HI_U32)                    /* ????De-Ring level*/
#define HIIOC_PQ_G_DR                   _IOR(HI_ID_PQ, 18, HI_U32)                    /* ??ȡDe-Ring level*/

#define HIIOC_PQ_S_COLORGAIN            _IOW(HI_ID_PQ, 19, HI_U32)                    /* ????Color gain level*/
#define HIIOC_PQ_G_COLORGAIN            _IOR(HI_ID_PQ, 20, HI_U32)                    /* ??ȡColor gain level*/

#define HIIOC_PQ_S_FLESHTONE            _IOW(HI_ID_PQ, 21, HI_PQ_FLESHTONE_E)         /* ????FleshTone level*/
#define HIIOC_PQ_G_FLESHTONE            _IOR(HI_ID_PQ, 22, HI_PQ_FLESHTONE_E)         /* ??ȡFleshTone level*/

#define HIIOC_PQ_S_BACKLIGHT            _IOW(HI_ID_PQ, 23, HI_U32)                    /* ????BackLight level*/
#define HIIOC_PQ_G_BACKLIGHT            _IOR(HI_ID_PQ, 24, HI_U32)                    /* ??ȡBackLight level*/

#define HIIOC_PQ_S_GAMMAIDX             _IOW(HI_ID_PQ, 25, HI_S32)                    /* ????GAMMA index*/
#define HIIOC_PQ_G_GAMMANUM             _IOR(HI_ID_PQ, 26, HI_S32)                    /* ??ȡGAMMA num*/

#define HIIOC_PQ_S_MODULE               _IOW(HI_ID_PQ, 27, HI_PQ_MODULE_S)            /* ???ø??㷨ģ?鿪??*/
#define HIIOC_PQ_G_MODULE               _IOWR(HI_ID_PQ, 28, HI_PQ_MODULE_S)           /* ??ȡ???㷨ģ?鿪??*/

#define HIIOC_PQ_S_DEMO                 _IOW(HI_ID_PQ, 29, HI_PQ_DEMO_S)              /* ???ø??㷨ģ??????ģʽ????*/

#define HIIOC_PQ_S_SIXBASECOLOR         _IOW(HI_ID_PQ, 30, HI_PQ_SIX_BASE_COLOR_S)    /* ???? ????ɫ????*/
#define HIIOC_PQ_G_SIXBASECOLOR         _IOR(HI_ID_PQ, 31, HI_PQ_SIX_BASE_COLOR_S)    /* ??ȡ????ɫ????*/

//#define HIIOC_PQ_S_PQ_PATH              _IOW(HI_ID_PQ, 32, HI_PQ_PATE_S)              /* ???? PQ?ļ?·??*/

#define HIIOC_PQ_S_NR_AUTO              _IOW(HI_ID_PQ, 33, HI_U32)                    /* ????NR?Զ?ģʽ*/
#define HIIOC_PQ_G_NR_AUTO              _IOR(HI_ID_PQ, 34, HI_U32)                    /* ??ȡNR?Զ?ģʽ*/

#define HIIOC_PQ_S_SR_DEMO              _IOW(HI_ID_PQ, 35, HI_PQ_SR_DEMO_E)           /* ????SR??ʾģʽ*/
#define HIIOC_PQ_G_SR_DEMO              _IOR(HI_ID_PQ, 36, HI_PQ_SR_DEMO_E)           /* ??ȡSR??ʾģʽ*/

/*???Խӿ?*/
#define HIIOC_PQ_S_3DSHARP              _IOW(HI_ID_PQ, 40, HI_U32)                    /* ????3D SHARP mode*/
#define HIIOC_PQ_G_3DSHARP              _IOR(HI_ID_PQ, 41, HI_U32)                    /* ??ȡ3D SHARP mode*/

//#define HIIOC_PQ_S_CSCMODE                    _IOW(HI_ID_PQ, 42, HI_PQ_CSC_S)                          /* ????CSC mode*/
//#define HIIOC_PQ_G_CSCMODE                    _IOR(HI_ID_PQ, 43, HI_PQ_CSC_S)                           /* ??ȡCSC mode*/

#define HIIOC_PQ_S_REGISTER             _IOW(HI_ID_PQ, 44, HI_PQ_REGISTER_S)          /* д?Ĵ???*/
#define HIIOC_PQ_G_REGISTER             _IOWR(HI_ID_PQ, 45, HI_PQ_REGISTER_S)         /*???Ĵ???*/

//#define HIIOC_PQ_S_GAMMA                      _IOW(HI_ID_PQ, 46, HI_PQ_GAMMA_TABLE_S)            /* дGAMMA????*/
//#define HIIOC_PQ_G_GAMMA                      _IOR(HI_ID_PQ, 47, HI_PQ_GAMMA_TABLE_S)             /*??GAMMA????*/

#define HIIOC_PQ_S_DCI                 _IOW(HI_ID_PQ, 48, HI_PQ_DCI_WGT_S)            /*дDCI????*/
#define HIIOC_PQ_G_DCI                 _IOR(HI_ID_PQ, 49, HI_PQ_DCI_WGT_S)            /*??DCI????*/

#define HIIOC_PQ_S_ACM_GAIN            _IOW(HI_ID_PQ, 50, HI_PQ_COLOR_GAIN_S)         /*дCOLOR GAIN*/
#define HIIOC_PQ_G_ACM_GAIN            _IOR(HI_ID_PQ, 51, HI_PQ_COLOR_GAIN_S)         /*??COLOR GAIN*/

#define HIIOC_PQ_S_ACM_LUMA            _IOW(HI_ID_PQ, 52, HI_PQ_ACM_LUT_S)            /*дCOLOR LUMA????*/
#define HIIOC_PQ_G_ACM_LUMA            _IOR(HI_ID_PQ, 53, HI_PQ_ACM_LUT_S)            /*??COLOR LUMA????*/

#define HIIOC_PQ_S_ACM_HUE             _IOW(HI_ID_PQ, 54, HI_PQ_ACM_LUT_S)            /*дCOLOR HUE????*/
#define HIIOC_PQ_G_ACM_HUE             _IOR(HI_ID_PQ, 55, HI_PQ_ACM_LUT_S)            /*??COLOR HUE????*/

#define HIIOC_PQ_S_ACM_SAT             _IOW(HI_ID_PQ, 56, HI_PQ_ACM_LUT_S)            /*дCOLOR SAT????*/
#define HIIOC_PQ_G_ACM_SAT             _IOR(HI_ID_PQ, 57, HI_PQ_ACM_LUT_S)            /*??COLOR SAT????*/

#define HIIOC_PQ_G_DCI_HIST            _IOR(HI_ID_PQ, 58, HI_PQ_DCI_HISTGRAM_S)       /*??DCIֱ??ͼ*/

//#define HIIOC_PQ_S_DIM                          _IOW(HI_ID_PQ, 60, HI_PQ_DIM_LUT_S)                     /*дDIMӳ??????*/
//#define HIIOC_PQ_G_DIM                          _IOR(HI_ID_PQ, 61, HI_PQ_DIM_LUT_S)                      /*??DIMӳ??????*/

#define HIIOC_PQ_S_TNR_Y_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 62, HI_PQ_TNR_S)        /*дTNR??????PixMean-to-Ratio*/
#define HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO       _IOR(HI_ID_PQ, 63, HI_PQ_TNR_S)        /*??TNR??????PixMean-to-Ratio*/

#define HIIOC_PQ_S_TNR_C_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 64, HI_PQ_TNR_S)        /*дTNR ɫ??PixMean-to-Ratioӳ??????*/
#define HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO       _IOR(HI_ID_PQ, 65, HI_PQ_TNR_S)        /*??TNR ɫ??PixMean-to-Ratioӳ??????*/

#define HIIOC_PQ_S_TNR_Y_MOTION_MAPPING        _IOW(HI_ID_PQ, 66, HI_PQ_TNR_S)        /*дTNR????MotionMapping????*/
#define HIIOC_PQ_G_TNR_Y_MOTION_MAPPING        _IOR(HI_ID_PQ, 67, HI_PQ_TNR_S)        /*??TNR????MotionMapping????*/

#define HIIOC_PQ_S_TNR_C_MOTION_MAPPING        _IOW(HI_ID_PQ, 68, HI_PQ_TNR_S)        /*дTNRɫ??MotionMapping????*/
#define HIIOC_PQ_G_TNR_C_MOTION_MAPPING        _IOR(HI_ID_PQ, 69, HI_PQ_TNR_S)        /*??TNRɫ??MotionMapping????*/

#define HIIOC_PQ_S_TNR_Y_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 70, HI_PQ_TNR_S)        /*дTNR????FINAL MotionMapping????*/
#define HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING  _IOR(HI_ID_PQ, 71, HI_PQ_TNR_S)        /*??TNR????FINAL MotionMapping????*/

#define HIIOC_PQ_S_TNR_C_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 72, HI_PQ_TNR_S)        /*дTNRɫ??FINAL MotionMapping????*/
#define HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING  _IOR(HI_ID_PQ, 73, HI_PQ_TNR_S)        /*??TNRɫ??FINAL MotionMapping????*/

#define HIIOC_PQ_S_SNR_PIXMEAN_2_RATIO         _IOW(HI_ID_PQ, 74, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*дSNR ??pixmean-ratioӳ??????*/
#define HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO         _IOR(HI_ID_PQ, 75, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*??SNR ??pixmean-ratioӳ??????*/

#define HIIOC_PQ_S_SNR_PIXDIFF_2_EDGESTR       _IOW(HI_ID_PQ, 76, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*дSNR ??pixdiff-edgestrӳ??????*/
#define HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR       _IOR(HI_ID_PQ, 77, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*??SNR ??pixdiff-edgestrӳ??????*/

#define HIIOC_PQ_S_HD_BRIGHTNESS        _IOW(HI_ID_PQ, 84, HI_U32)                    /* ???ø???BRIGHTNESS level*/
#define HIIOC_PQ_G_HD_BRIGHTNESS        _IOR(HI_ID_PQ, 85, HI_U32)                    /* ??ȡ????BRIGHTNESS level*/

#define HIIOC_PQ_S_HD_CONTRAST          _IOW(HI_ID_PQ, 86, HI_U32)                    /* ???ø???CONTRAST level*/
#define HIIOC_PQ_G_HD_CONTRAST          _IOR(HI_ID_PQ, 87, HI_U32)                    /* ??ȡ????CONTRAST level*/

#define HIIOC_PQ_S_HD_SATURATION        _IOW(HI_ID_PQ, 88, HI_U32)                    /* ???ø???SATURATION level*/
#define HIIOC_PQ_G_HD_SATURATION        _IOR(HI_ID_PQ, 89, HI_U32)                    /* ??ȡ????SATURATION level*/

#define HIIOC_PQ_S_HD_HUE               _IOW(HI_ID_PQ, 90, HI_U32)                    /* ???ø???HUE level*/
#define HIIOC_PQ_G_HD_HUE               _IOR(HI_ID_PQ, 91, HI_U32)                    /* ??ȡ????HUE level*/

#define HIIOC_PQ_S_DCI_LEVEL            _IOW(HI_ID_PQ, 92, HI_U32)                    /* ????DCI level*/
#define HIIOC_PQ_G_DCI_LEVEL            _IOR(HI_ID_PQ, 93, HI_U32)                    /* ??ȡDCI level*/

#define HIIOC_PQ_G_BIN_ADDR             _IOR(HI_ID_PQ, 94, HI_U32)                    /* ??ȡPQBin????????ַ*/

#define HIIOC_PQ_S_COLOR_ENHANCE_MODE   _IOW(HI_ID_PQ, 95, HI_PQ_COLOR_SPEC_MODE_E)   /* ??????ɫ??ǿģʽ*/
#define HIIOC_PQ_G_COLOR_ENHANCE_MODE   _IOR(HI_ID_PQ, 96, HI_PQ_COLOR_SPEC_MODE_E)   /* ??ȡ??ɫ??ǿģʽ*/

#define HIIOC_PQ_S_ACM_CTRL             _IOW(HI_ID_PQ, 97, HI_PQ_COLOR_CTRL_S)        /* ????ACM ???ƼĴ???*/
#define HIIOC_PQ_G_ACM_CTRL             _IOR(HI_ID_PQ, 98, HI_PQ_COLOR_CTRL_S)        /* ??ȡACM ???ƼĴ???*/

#define HIIOC_PQ_S_DEMO_MODE            _IOW(HI_ID_PQ, 99, HI_PQ_DEMO_MODE_E)         /* ???ø??㷨ģ??????ģʽ??ʾ??ʽ*/
#define HIIOC_PQ_G_DEMO_MODE            _IOR(HI_ID_PQ, 100, HI_PQ_DEMO_MODE_E)        /* ??ȡ???㷨ģ??????ģʽ??ʾ??ʽ*/

#define HIIOC_PQ_S_GRAPH_SD_PARAM       _IOW(HI_ID_PQ, 101, HI_PQ_IMAGE_PARAM_S)               /* ????ͼ?α???????*/
#define HIIOC_PQ_G_GRAPH_SD_PARAM       _IOR(HI_ID_PQ, 102, HI_PQ_IMAGE_PARAM_S)               /* ??ȡͼ?α???????*/

#define HIIOC_PQ_S_GRAPH_HD_PARAM       _IOW(HI_ID_PQ, 103, HI_PQ_IMAGE_PARAM_S)               /* ????ͼ?θ???????*/
#define HIIOC_PQ_G_GRAPH_HD_PARAM       _IOR(HI_ID_PQ, 104, HI_PQ_IMAGE_PARAM_S)               /* ??ȡͼ?θ???????*/

#define HIIOC_PQ_S_VIDEO_SD_PARAM       _IOW(HI_ID_PQ, 105, HI_PQ_IMAGE_PARAM_S)               /* ??????Ƶ????????*/
#define HIIOC_PQ_G_VIDEO_SD_PARAM       _IOR(HI_ID_PQ, 106, HI_PQ_IMAGE_PARAM_S)               /* ??ȡ??Ƶ????????*/

#define HIIOC_PQ_S_VIDEO_HD_PARAM       _IOW(HI_ID_PQ, 107, HI_PQ_IMAGE_PARAM_S)               /* ??????Ƶ????????*/
#define HIIOC_PQ_G_VIDEO_HD_PARAM       _IOR(HI_ID_PQ, 108, HI_PQ_IMAGE_PARAM_S)               /* ??ȡ??Ƶ????????*/

#define HIIOC_PQ_S_TNR_FMOTION_MAPPING  _IOW(HI_ID_PQ, 109, HI_PQ_TNR_FMOTION_S)               /*дTNR FMotionMapping ????*/
#define HIIOC_PQ_G_TNR_FMOTION_MAPPING  _IOR(HI_ID_PQ, 110, HI_PQ_TNR_FMOTION_S)               /*??TNR FMotionMapping ????*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HI_DRV_PQ_H__ */
