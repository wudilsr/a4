/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NKtG06vaX0WeWNkkjMzfG9L0/39FA6YL5STDYVh
3bRFxdZe16GQWhcZ60NONAQrxsKA3AXQxIZmjfUjxNFXNgMpToq9DtDzPa+uj7WGuX50biwm
9lThNCPrSqKO2moZfp27gQlljALK+34HOSNqavVXMq0PYKCEAbhv+2/JbwAFDA==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/






















#include "vpss_hal_3716mv410.h"
#include "linux/kthread.h"
#include "vpss_common.h"

#include <asm/barrier.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

VPSS_HAL_CTX_S  stHalCtx[VPSS_IP_BUTT] = 
{
    {
        .bInit = HI_FALSE,
        .bClockEn = HI_FALSE,
        .u32LogicVersion = HAL_VERSION_3798M,
        .u32BaseRegPhy   = VPSS0_BASE_ADDR,
        .u32BaseRegVir   = 0,
    },
    
    {
        .bInit = HI_FALSE,
        .bClockEn = HI_FALSE,
        .u32LogicVersion = HAL_VERSION_3798M,
        .u32BaseRegPhy   = VPSS1_BASE_ADDR,
        .u32BaseRegVir   = 0,
    }
};

VPSS_REG_PORT_E VPSS_HAL_AllocPortId(VPSS_HAL_PORT_INFO_S *pstHalPort,
    HI_BOOL abPortUsed[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER])
{
    if (HI_FALSE == abPortUsed[VPSS_REG_HD])
    {
         abPortUsed[VPSS_REG_HD] = HI_TRUE;
         return VPSS_REG_HD;
    }
#if 0
    if (HI_FALSE == abPortUsed[VPSS_REG_STR])
    {
         abPortUsed[VPSS_REG_STR] = HI_TRUE;
         return VPSS_REG_STR;
    }

    if (HI_FALSE == abPortUsed[VPSS_REG_SD])
    {
         abPortUsed[VPSS_REG_SD] = HI_TRUE;
         return VPSS_REG_SD;
    }
#endif

    return VPSS_REG_BUTT;
}

ZME_FORMAT_E VPSS_HAL_GetZmeFmt(HI_DRV_PIX_FORMAT_E enFormat)
{
    ZME_FORMAT_E enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP420;
    
    switch(enFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP420;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:  
        //case HI_DRV_PIX_FMT_ARGB8888:   //sp420->sp422->csc->rgb
        //case HI_DRV_PIX_FMT_ABGR8888:
        //case HI_DRV_PIX_FMT_KBGR8888:
            enZmeFmt = HI_PQ_ALG_PIX_FORMAT_SP422;
            break;
        default:
            VPSS_FATAL("REG ERROR format %d\n",enFormat);
    }

    return enZmeFmt;
}

HI_S32 VPSS_HAL_SetZmeCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, 
                            VPSS_HAL_INFO_S *pstHalInfo,
                            VPSS_REG_PORT_E enPort,
                            HI_U32 u32PortCnt)
{
    VPSS_HAL_PORT_INFO_S *pstHalPort = HI_NULL;
    HI_PQ_ZME_PARA_IN_S stZmeDrvPara;
    HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara;
    VPSS_HAL_FRAME_S *pstInInfo; 
    HI_PQ_VPSS_ZME_LAYER_E enPqPort = HI_PQ_VPSS_LAYER_ZME_BUTT;

	if (VPSS_REG_BUTT <= enPort)
	{
		VPSS_ERROR("Invalid enPort %d\n",enPort);	
		return HI_FAILURE;
	}
    
    pstHalPort = &pstHalInfo->astPortInfo[u32PortCnt];

    pstInInfo = &(pstHalInfo->stInInfo);
    
    pstZmeDrvPara  = &(stZmeDrvPara);
    
    memset(pstZmeDrvPara,0,sizeof(HI_PQ_ZME_PARA_IN_S));

#if 0
    if (pstInInfo->bProgressive != HI_TRUE)
    {
        pstZmeDrvPara->bZmeFrmFmtIn = 1;
    }
    else
    {
        if (pstInInfo->enFieldMode == HI_DRV_FIELD_ALL)
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 1;
        }
        else
        {
            pstZmeDrvPara->bZmeFrmFmtIn = 0;
        }
    }
#else
	pstZmeDrvPara->bZmeFrmFmtIn = 1;
#endif
    pstZmeDrvPara->bZmeFrmFmtOut = 1;

#if 0
    if (pstInInfo->enFieldMode == HI_DRV_FIELD_TOP)
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
    else if (pstInInfo->enFieldMode == HI_DRV_FIELD_BOTTOM)
    {
        pstZmeDrvPara->bZmeBFIn = 1;
    }
    else
    {
        pstZmeDrvPara->bZmeBFIn = 0;
    }
#else
	pstZmeDrvPara->bZmeBFIn = 0;
#endif
    pstZmeDrvPara->bZmeBFOut = 0;

    if (pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV61
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_NV16
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV422_1X2
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV420p
        || pstInInfo->enFormat == HI_DRV_PIX_FMT_YUV410p
        )
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    }
    else
    {
        pstZmeDrvPara->u8ZmeYCFmtIn = 1;//PQ_ALG_ZME_PIX_FORMAT_SP422;
    }
    
    if (pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV21
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV12
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstHalPort->stOutInfo.enFormat == HI_DRV_PIX_FMT_NV12_CMP)
    {
        pstZmeDrvPara->u8ZmeYCFmtOut = 0;//PQ_ALG_ZME_PIX_FORMAT_SP420;
    }
    else
    {
        pstZmeDrvPara->u8ZmeYCFmtOut = 1;//PQ_ALG_ZME_PIX_FORMAT_SP422;
    }
    
    pstZmeDrvPara->u32ZmeFrmHIn = pstInInfo->u32Height;
    pstZmeDrvPara->u32ZmeFrmWIn = pstInInfo->u32Width;

#if 0
    if (pstInInfo->bProgressive == HI_TRUE)
    {
        if (pstInInfo->enFieldMode != HI_DRV_FIELD_ALL)
        {
            pstZmeDrvPara->u32ZmeFrmHIn = pstZmeDrvPara->u32ZmeFrmHIn*2;
        }
    }
#endif
    
    pstZmeDrvPara->u32ZmeFrmHOut = pstHalPort->stVideoRect.s32Height;
    pstZmeDrvPara->u32ZmeFrmWOut = pstHalPort->stVideoRect.s32Width;
    
	#if 0
    VPSS_ERROR("IN W %d H %d  W %d H %d\n",
        pstZmeDrvPara->u32ZmeFrmWIn,
        pstZmeDrvPara->u32ZmeFrmHIn,
        pstZmeDrvPara->u32ZmeFrmWOut,
        pstZmeDrvPara->u32ZmeFrmHOut);
	#endif
	
    pstZmeDrvPara->stOriRect.s32X = 0;
    pstZmeDrvPara->stOriRect.s32Y = 0;
    pstZmeDrvPara->stOriRect.s32Width = pstInInfo->u32Width;
    pstZmeDrvPara->stOriRect.s32Height = pstInInfo->u32Height;
    pstZmeDrvPara->u32InRate = 25000;     
    pstZmeDrvPara->u32OutRate = 25000;
    pstZmeDrvPara->bDispProgressive = HI_TRUE;
    pstZmeDrvPara->u32Fidelity = 0; 

    switch(enPort)
    {
        case VPSS_REG_HD:
            enPqPort = HI_PQ_VPSS_PORT0_LAYER_ZME;
            break;
        case VPSS_REG_SD:
            enPqPort = HI_PQ_VPSS_PORT1_LAYER_ZME;
            break;
        case VPSS_REG_STR:
            enPqPort = HI_PQ_VPSS_PORT2_LAYER_ZME;
            break;
        default:
            break;
    }
    DRV_PQ_SetVpssZme(enPqPort,
                      (VPSS_REG_S*)u32AppVir,
                      pstZmeDrvPara,
                      HI_TRUE);

    return HI_SUCCESS;
}

HI_BOOL VPSS_HAL_CheckNeedCmp(VPSS_HAL_FRAME_S *pstOutFrm)
{
    if((HI_DRV_PIX_FMT_NV12_CMP == pstOutFrm->enFormat)
        || (HI_DRV_PIX_FMT_NV21_CMP == pstOutFrm->enFormat)
        || (HI_DRV_PIX_FMT_NV16_CMP == pstOutFrm->enFormat)
        || (HI_DRV_PIX_FMT_NV61_CMP == pstOutFrm->enFormat)
        || (HI_DRV_PIX_FMT_NV16_2X1_CMP == pstOutFrm->enFormat)
        || (HI_DRV_PIX_FMT_NV61_2X1_CMP == pstOutFrm->enFormat)
        )
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}
/******************************************************************************
brief      : CNcomment:  Config Port Compression info
attention  :
param[in]  :
retval     : HI_S32
see        :
author	   :f00241306
******************************************************************************/

HI_S32 VPSS_HAL_SetPortCmpCfg(HI_U32 u32AppVir,VPSS_REG_PORT_E ePort, VPSS_HAL_PORT_INFO_S *pstHalPort)
{
    HI_BOOL bIs_lossless;
    HI_BOOL bCmp_Mode;
    HI_U32 u32Dw_Mode;
    HI_U32 u32CmpRatioY;
    HI_U32 u32CmpRatioC;
    HI_U32 u32YMaxQp;
    HI_U32 u32CMaxQp;
    HI_DRV_PIXEL_BITWIDTH_E  enBitWidth;
    ZME_FORMAT_E enOutFormat;
    REG_CMP_DATA_S stYcmpData;
    REG_CMP_DATA_S stCcmpData;
    VPSS_HAL_FRAME_S *pstOutFrm;

    if(VPSS_REG_HD != ePort)
    {
        VPSS_FATAL("Vpss cmp error,only VHD support!!\n");
        return HI_FAILURE;
    }

    pstOutFrm =  &(pstHalPort->stOutInfo);
    enBitWidth = pstHalPort->stOutInfo.enBitWidth;

	if( ! ((HI_DRV_PIXEL_BITWIDTH_8BIT == enBitWidth) || (HI_DRV_PIXEL_BITWIDTH_10BIT == enBitWidth)) )
    {
        VPSS_FATAL("Vpss cmp error,only 8BIT and 10BIT support!!\n");
        return HI_FAILURE;
    }

    u32CmpRatioY = (enBitWidth == 1) ? 140 : 130;
    u32CmpRatioC = (enBitWidth == 1) ? 140 : 130;
    u32YMaxQp  = (enBitWidth == 1) ? 4 : 2;
    u32CMaxQp  = (enBitWidth == 1) ? 4 : 2;

    if(0 == enBitWidth)
    {
        if(u32CmpRatioY < 135)
        {
            u32YMaxQp = 2;
        }
        else if((u32CmpRatioY >= 135) && (u32CmpRatioY < 160))
        {
            u32YMaxQp = 3;
        }
        else
        {
            u32YMaxQp = 4;
        }

        if(u32CmpRatioC < 135)
        {
            u32CMaxQp = 2;
        }
        else if((u32CmpRatioC >= 135) && (u32CmpRatioC < 160))
        {
            u32CMaxQp = 3;
        }
        else
        {
            u32CMaxQp = 4;
        }

    }
    else
    {
        if(u32CmpRatioY < 135)
        {
            u32YMaxQp = 3;
        }
        else if((u32CmpRatioY >= 135) && (u32CmpRatioY < 160))
        {
            u32YMaxQp = 4;
        }
        else
        {
            u32YMaxQp = 5;
        }

        if(u32CmpRatioC < 135)
        {
            u32CMaxQp = 3;
        }
        else if((u32CmpRatioC >= 135) && (u32CmpRatioC < 160))
        {
            u32CMaxQp = 4;
        }
        else
        {
            u32CMaxQp = 5;
        }
    }

    bIs_lossless = !(pstHalPort->bCmpLoss);//vdp will control

    bCmp_Mode = HI_FALSE;//cmp mode
    u32Dw_Mode = (enBitWidth == 1) ? 0 : 1;

    if(pstOutFrm->u32Width < 128)
    {
        bIs_lossless = HI_TRUE;
    }

	if ( pstOutFrm->u32Width < 32 || pstOutFrm->u32Width > 8192 || 
		 pstOutFrm->u32Height < 32 || pstOutFrm->u32Height > 8192)
	{
		VPSS_FATAL("Vpss cmp error, input IMG Width or Height not support!!\n");
        return HI_FAILURE;
	}

    enOutFormat = VPSS_HAL_GetZmeFmt(pstOutFrm->enFormat);
//calc y cmp config
    stYcmpData.u32Width = pstOutFrm->u32Width ;
    stYcmpData.u32Height = pstOutFrm->u32Height ;
    stYcmpData.u32Cfg0_Mb_bits = 32 * 100 * ((enBitWidth == 0) ? 10 : 8) / u32CmpRatioY;
    stYcmpData.u32Cfg0_Ri_bits = (enBitWidth == 1) ? 3 : 3;
    stYcmpData.u32Cfg0_Max_rg_comp_bits = (enBitWidth == 1) ? 12 : 10;
    stYcmpData.u32Cfg1_Max_qp = u32YMaxQp;
    stYcmpData.u32Cfg1_Rc_smth_ngain = (enBitWidth == 1) ? 1 : 1;
    stYcmpData.u32Cfg1_Sad_bits_ngain = (enBitWidth == 1) ? 1 : 1;
    stYcmpData.u32Cfg2_Pix_diff_thr = (enBitWidth == 1) ? 200 : 50;
    stYcmpData.u32Cfg2_Smth_pix_num_thr = (enBitWidth == 1) ? 4 : 4;
    stYcmpData.u32Cfg2_Smth_thr = (enBitWidth == 1) ? 12 : 3;
    stYcmpData.u32Cfg3_Adj_sad_bit_thr = (enBitWidth == 1) ? 25 : 20;
    stYcmpData.u32Cfg3_Adj_sad_thr = (enBitWidth == 1) ? 1280 : 320;
    stYcmpData.u32Cfg4_Qp_chg1_bits_thr = (enBitWidth == 1) ? 35 : 28;
    stYcmpData.u32Cfg4_Qp_chg2_bits_thr = (enBitWidth == 1) ? 75 : 60;
    stYcmpData.u32Cfg5_Smth_lftbits_thr0 = (enBitWidth == 1) ? 12 : 10;
    stYcmpData.u32Cfg5_Smth_lftbits_thr1 = (enBitWidth == 1) ? 25 : 20;
    stYcmpData.u32Cfg5_Smth_qp0 = (enBitWidth == 1) ? 1 : 1;
    stYcmpData.u32Cfg5_Smth_qp1 = (enBitWidth == 1) ? 2 : 2;
//calc c cmp config
    stCcmpData.u32Width = pstOutFrm->u32Width / 2 ;
    stCcmpData.u32Height = (HI_PQ_ALG_PIX_FORMAT_SP422 == enOutFormat) ? pstOutFrm->u32Height : pstOutFrm->u32Height / 2;
    stCcmpData.u32Cfg0_Mb_bits = 64 * 100 * ((enBitWidth == 0) ? 10 : 8) / u32CmpRatioC;
    stCcmpData.u32Cfg0_Ri_bits = (enBitWidth == 1) ? 7 : 6;
    stCcmpData.u32Cfg0_Max_rg_comp_bits = (enBitWidth == 1) ? 25 : 20;
    stCcmpData.u32Cfg1_Max_qp = u32CMaxQp;
    stCcmpData.u32Cfg1_Rc_smth_ngain = (enBitWidth == 1) ? 0 : 0;
    stCcmpData.u32Cfg1_Sad_bits_ngain = (enBitWidth == 1) ? 1 : 1;
    stCcmpData.u32Cfg2_Pix_diff_thr = (enBitWidth == 1) ? 200 : 50;
    stCcmpData.u32Cfg2_Smth_pix_num_thr = (enBitWidth == 1) ? 4 : 4;
    stCcmpData.u32Cfg2_Smth_thr = (enBitWidth == 1) ? 12 : 3;
    stCcmpData.u32Cfg3_Adj_sad_bit_thr = (enBitWidth == 1) ? 50 : 40;
    stCcmpData.u32Cfg3_Adj_sad_thr = (enBitWidth == 1) ? 1920 : 480;
    stCcmpData.u32Cfg4_Qp_chg1_bits_thr = (enBitWidth == 1) ? 70 : 56;
    stCcmpData.u32Cfg4_Qp_chg2_bits_thr = (enBitWidth == 1) ? 150 : 120;
    stCcmpData.u32Cfg5_Smth_lftbits_thr0 = (enBitWidth == 1) ? 12 : 10;
    stCcmpData.u32Cfg5_Smth_lftbits_thr1 = (enBitWidth == 1) ? 25 : 20;
    stCcmpData.u32Cfg5_Smth_qp0 = (enBitWidth == 1) ? 1 : 1;
    stCcmpData.u32Cfg5_Smth_qp1 = (enBitWidth == 1) ? 2 : 2;

    VPSS_REG_SetLcmpEn(u32AppVir, HI_TRUE);

    //:Y
	VPSS_REG_Set_Y_Is_Lossless(u32AppVir,bIs_lossless);
	VPSS_REG_Set_Y_Cmp_Mode(u32AppVir,bCmp_Mode);
	VPSS_REG_Set_Y_Dw_Mode(u32AppVir,u32Dw_Mode);

	VPSS_REG_Set_Y_Frame_Width(u32AppVir, stYcmpData.u32Width);
	VPSS_REG_Set_Y_Frame_Height(u32AppVir, stYcmpData.u32Height);

	VPSS_REG_Set_Y_MbBits(u32AppVir,stYcmpData.u32Cfg0_Mb_bits);
	VPSS_REG_Set_Y_RiBits(u32AppVir, stYcmpData.u32Cfg0_Ri_bits);
	VPSS_REG_Set_Y_MaxRgCompBits(u32AppVir, stYcmpData.u32Cfg0_Max_rg_comp_bits);

	VPSS_REG_Set_Y_MaxQp(u32AppVir, stYcmpData.u32Cfg1_Max_qp);
	VPSS_REG_Set_Y_SadNgain(u32AppVir, stYcmpData.u32Cfg1_Sad_bits_ngain);
	VPSS_REG_Set_Y_RcSmthNgain(u32AppVir, stYcmpData.u32Cfg1_Rc_smth_ngain);

	VPSS_REG_Set_Y_SmthThr(u32AppVir, stYcmpData.u32Cfg2_Smth_thr);
	VPSS_REG_Set_Y_SmthPixNumThr(u32AppVir, stYcmpData.u32Cfg2_Smth_pix_num_thr);
	VPSS_REG_Set_Y_PixDiffThr(u32AppVir, stYcmpData.u32Cfg2_Pix_diff_thr);

	VPSS_REG_Set_Y_AdjSadThr(u32AppVir, stYcmpData.u32Cfg3_Adj_sad_thr);
	VPSS_REG_Set_Y_AdjSadBitThr(u32AppVir, stYcmpData.u32Cfg3_Adj_sad_bit_thr);

	VPSS_REG_Set_Y_QpChg1BitsThr(u32AppVir, stYcmpData.u32Cfg4_Qp_chg1_bits_thr);
	VPSS_REG_Set_Y_QpChg2BitsThr(u32AppVir, stYcmpData.u32Cfg4_Qp_chg2_bits_thr);

	VPSS_REG_Set_Y_SmthQp0(u32AppVir, stYcmpData.u32Cfg5_Smth_qp0);
	VPSS_REG_Set_Y_SmthQp1(u32AppVir, stYcmpData.u32Cfg5_Smth_qp1);
	VPSS_REG_Set_Y_SmthLftBThr0(u32AppVir, stYcmpData.u32Cfg5_Smth_lftbits_thr0);
	VPSS_REG_Set_Y_SmthLftBThr1(u32AppVir, stYcmpData.u32Cfg5_Smth_lftbits_thr1);

	//:C
	VPSS_REG_Set_C_Is_Lossless(u32AppVir,bIs_lossless);
	VPSS_REG_Set_C_Cmp_Mode(u32AppVir,bCmp_Mode);
	VPSS_REG_Set_C_Dw_Mode(u32AppVir,u32Dw_Mode);

	VPSS_REG_Set_C_Frame_Width(u32AppVir, stCcmpData.u32Width);
	VPSS_REG_Set_C_Frame_Height(u32AppVir, stCcmpData.u32Height);

	VPSS_REG_Set_C_MbBits(u32AppVir,stCcmpData.u32Cfg0_Mb_bits);
	VPSS_REG_Set_C_RiBits(u32AppVir, stCcmpData.u32Cfg0_Ri_bits);
	VPSS_REG_Set_C_MaxRgCompBits(u32AppVir, stCcmpData.u32Cfg0_Max_rg_comp_bits);

	VPSS_REG_Set_C_Max_Qp(u32AppVir, stCcmpData.u32Cfg1_Max_qp);
	VPSS_REG_Set_C_SadNgain(u32AppVir, stCcmpData.u32Cfg1_Sad_bits_ngain);
	VPSS_REG_Set_C_RcSmthNgain(u32AppVir, stCcmpData.u32Cfg1_Rc_smth_ngain);

	VPSS_REG_Set_C_SmthThr(u32AppVir, stCcmpData.u32Cfg2_Smth_thr);
	VPSS_REG_Set_C_SmthPixNumThr(u32AppVir, stCcmpData.u32Cfg2_Smth_pix_num_thr);
	VPSS_REG_Set_C_PixDiffThr(u32AppVir, stCcmpData.u32Cfg2_Pix_diff_thr);

	VPSS_REG_Set_C_AdjSadThr(u32AppVir, stCcmpData.u32Cfg3_Adj_sad_thr);
	VPSS_REG_Set_C_AdjSadBitThr(u32AppVir, stCcmpData.u32Cfg3_Adj_sad_bit_thr);

	VPSS_REG_Set_C_QpChg1BitsThr(u32AppVir, stCcmpData.u32Cfg4_Qp_chg1_bits_thr);
	VPSS_REG_Set_C_QpChg2BitsThr(u32AppVir, stCcmpData.u32Cfg4_Qp_chg2_bits_thr);

	VPSS_REG_Set_C_SmthQp0(u32AppVir, stCcmpData.u32Cfg5_Smth_qp0);
	VPSS_REG_Set_C_SmthQp1(u32AppVir, stCcmpData.u32Cfg5_Smth_qp1);
	VPSS_REG_Set_C_SmthLftBThr0(u32AppVir, stCcmpData.u32Cfg5_Smth_lftbits_thr0);
	VPSS_REG_Set_C_SmthLftBThr1(u32AppVir, stCcmpData.u32Cfg5_Smth_lftbits_thr1);

    return HI_SUCCESS;
}
/* 
*  VPSS_HAL_SetPortCfg???????????????? VPSS_HAL_PORT_INFO_S??????????????
*  ???????????????????? ??????????VPSS_HAL_INFO_S????????????????????????????????????
*/
HI_S32 VPSS_HAL_SetPortCfg(VPSS_IP_E enIP,HI_U32 u32AppVir, HI_U32 u32AppPhy,
    VPSS_HAL_INFO_S *pstHalInfo)
{
    HI_U32 u32Count;
	HI_U32 u32PortAvailable = DEF_VPSS_HAL_PORT_NUM;
	HI_U32 VPSS_VHD0_LCMP_ADDR;

    HI_BOOL abPortUsed[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER]
        = {HI_FALSE, HI_FALSE, HI_FALSE};
    
    /* ??????????HD???????????? */
    VPSS_REG_EnPort(u32AppVir, VPSS_REG_HD, HI_FALSE);
    
    for (u32Count = 0; (u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER) && (u32PortAvailable > 0); u32Count ++)
    {
        VPSS_HAL_PORT_INFO_S *pstHalPort = HI_NULL;

        pstHalPort = &pstHalInfo->astPortInfo[u32Count];

        if (pstHalPort->bEnable && pstHalPort->bConfig == HI_FALSE)
        {
            VPSS_REG_PORT_E enPort = VPSS_REG_BUTT;
            VPSS_HAL_FRAME_S *pstOutFrm = HI_NULL;
            HI_DRV_VID_FRAME_ADDR_S *pstOutAddr = HI_NULL;
            
            enPort = VPSS_HAL_AllocPortId(pstHalPort, abPortUsed);
            if (enPort == VPSS_REG_BUTT)
            {
                HI_ASSERT(0);
            }
			else
			{
				u32PortAvailable--;
			}

            pstOutFrm = &pstHalPort->stOutInfo;
            pstOutAddr = &pstOutFrm->stAddr;

            /* Flip&Mirro */
            VPSS_REG_SetPortMirrorEn(u32AppVir, enPort,pstHalPort->bNeedMirror);  
            VPSS_REG_SetPortFlipEn(u32AppVir, enPort,pstHalPort->bNeedFlip);    
            
            /* UV???? */
			VPSS_REG_SetVHD0_UVINVERT(u32AppVir, pstOutFrm->bUVInver);

            /* PreZme */
            //VPSS_REG_SetFrmPreZmeEn(u32AppVir, enPort, HI_FALSE, HI_FALSE);
            
            /*ZME*/
            VPSS_HAL_SetZmeCfg(enIP,u32AppVir, pstHalInfo,enPort,u32Count);
         
            /* LBX */
            VPSS_REG_SetLBABg(u32AppVir, enPort, 0x108080, 0x7f);
            VPSS_REG_SetLBAVidPos(u32AppVir, enPort, 
                                    (HI_U32)pstHalPort->stVideoRect.s32X,
                                    (HI_U32)pstHalPort->stVideoRect.s32Y,
                                    pstHalPort->stVideoRect.s32Height,
                                    pstHalPort->stVideoRect.s32Width);
            VPSS_REG_SetLBADispPos(u32AppVir, enPort, 0, 0, 
                                   pstOutFrm->u32Height, pstOutFrm->u32Width);
            VPSS_REG_SetLBAEn(u32AppVir, enPort, HI_TRUE);
                       
            /* ???????? */
            VPSS_REG_SetFrmSize(u32AppVir,enPort,pstOutFrm->u32Height, pstOutFrm->u32Width);
            VPSS_REG_SetFrmAddr(u32AppVir,enPort,pstOutAddr->u32PhyAddr_Y, pstOutAddr->u32PhyAddr_C);
            VPSS_REG_SetFrmStride(u32AppVir,enPort,pstOutAddr->u32Stride_Y,pstOutAddr->u32Stride_C);
            VPSS_REG_SetFrmFormat(u32AppVir,enPort,pstOutFrm->enFormat);
 
            if(enPort == VPSS_REG_HD &&  VPSS_HAL_CheckNeedCmp(pstOutFrm))
            {
                //????????
				VPSS_VHD0_LCMP_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_VHD0_LCMP_YINFO) - sizeof(HI_U32);
				VPSS_REG_SetAddr(u32AppVir, REG_VPSS_VHD0_LCMP_ADDR, VPSS_VHD0_LCMP_ADDR);

                VPSS_HAL_SetPortCmpCfg(u32AppVir, enPort, pstHalPort);
                //VPSS_REG_SetPortMirrorEn(u32AppVir, enPort,HI_FALSE);//????????????????????????               
            }
			pstHalPort->bConfig = HI_TRUE;

            VPSS_REG_EnPort(u32AppVir, enPort, HI_TRUE);
        }    
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetAllAlgCfgAddr(HI_U32 u32AppVir, HI_U32 u32AppPhy)
{
#if 0
    VPSS_REG_SetVc1StrCfgAddr(u32AppVir, u32AppPhy+0x2400);
    VPSS_REG_SetZmeCfgAddr(u32AppVir, u32AppPhy+0x2000);
    VPSS_REG_SetHspCfgAddr(u32AppVir, u32AppPhy+0x2100);
    VPSS_REG_SetSnrCfgAddr(u32AppVir, u32AppPhy+0x3000);
    VPSS_REG_SetDbCfgAddr(u32AppVir, u32AppPhy+0x2200);
    VPSS_REG_SetDrCfgAddr(u32AppVir, u32AppPhy+0x2300);
    VPSS_REG_SetDeiCfgAddr(u32AppVir, u32AppPhy+0x1000);
    VPSS_REG_SetTnrCfgAddr(u32AppVir, u32AppPhy+0x3800);
    VPSS_REG_SetTnrClutCfgAddr(u32AppVir, u32AppPhy+0x3b00);
    VPSS_REG_SetEsCfgAddr(u32AppVir, u32AppPhy+0x2500);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetRwzbCfg(HI_U32 u32AppAddr,VPSS_RWZB_INFO_S *pstRwzbInfo)
{
	HI_U32 u32Count;

	if( pstRwzbInfo->u32EnRwzb == 0x1)
	{
		for(u32Count = 0; u32Count < 6; u32Count++)
		{
			VPSS_REG_SetDetBlk(u32AppAddr,u32Count,&(pstRwzbInfo->u32Addr[u32Count][0]));
#if 1
			VPSS_INFO("adddr X %d Y %d\n",pstRwzbInfo->u32Addr[u32Count][0],
					pstRwzbInfo->u32Addr[u32Count][1]);
#endif
		}

	}
	VPSS_REG_SetDetEn(u32AppAddr,pstRwzbInfo->u32EnRwzb);
	VPSS_REG_SetDetMode(u32AppAddr,pstRwzbInfo->u32Mode);

	return HI_SUCCESS;
}


HI_S32 VPSS_HAL_SetDeiCfg(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir,HI_U32 u32AppPhy)

{
    HI_U32  VPSS_DEI_ADDR;

    HI_DRV_VID_FRAME_ADDR_S *pstRef  = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstCur  = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt1 = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstNxt2 = HI_NULL;

    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);

	/* ?????????? */
    pstRef  = &pstHalInfo->stInRefInfo[0].stAddr;
    pstCur  = &pstHalInfo->stInRefInfo[1].stAddr;
    pstNxt1 = &pstHalInfo->stInRefInfo[2].stAddr;
    pstNxt2 = &pstHalInfo->stInInfo.stAddr;

    /*dei*/
    VPSS_REG_SetImgReadMod(u32AppVir, HI_TRUE);
    VPSS_REG_EnDei(u32AppVir, HI_TRUE);
    VPSS_REG_SetDeiTopFirst(u32AppVir, pstHalInfo->stInInfo.bTopFirst);

    switch(pstHalInfo->stInInfo.enFieldMode)
    {
        case HI_DRV_FIELD_BOTTOM:
            VPSS_REG_SetDeiFieldMode(u32AppVir, HI_TRUE);
            break;
        case HI_DRV_FIELD_TOP:
            VPSS_REG_SetDeiFieldMode(u32AppVir, HI_FALSE);
            break;
        default:
            VPSS_FATAL("No spt field Type:%d!\n", pstHalInfo->stInInfo.enFieldMode);
            return HI_FAILURE;
    }
    
    VPSS_REG_SetModeEn(u32AppVir,REG_DIE_MODE_CHROME,HI_TRUE);
    VPSS_REG_SetModeEn(u32AppVir,REG_DIE_MODE_LUMA,HI_TRUE);

    VPSS_DEI_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_DIECTRL)-sizeof(HI_U32);
    VPSS_REG_SetDeiParaAddr(u32AppVir,VPSS_DEI_ADDR);

    VPSS_REG_SetMode(u32AppVir, REG_DIE_MODE_ALL, 1);//0??5????????1??4????????2??3??????

    /*********************************ref**************************************/
    if (pstHalInfo->stInRefInfo[0].enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInRefInfo[0].enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInRefInfo[0].enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInRefInfo[0].enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir, LAST_FIELD, HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir, LAST_FIELD, HI_FALSE);
    }	
    VPSS_REG_SetImgAddr(u32AppVir, LAST_FIELD, pstRef->u32PhyAddr_Y,
						pstRef->u32PhyAddr_C, pstRef->u32PhyAddr_Cr);
    VPSS_REG_SetImgStride(u32AppVir,LAST_FIELD, pstRef->u32Stride_Y, pstRef->u32Stride_C);
	
    /************************* Cur **********************************/
    if (pstHalInfo->stInRefInfo[1].enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInRefInfo[1].enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInRefInfo[1].enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInRefInfo[1].enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }
	VPSS_REG_SetRefSize(u32AppVir,pstHalInfo->stInRefInfo[1].u32Width,pstHalInfo->stInRefInfo[1].u32Height);
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,pstCur->u32PhyAddr_Y,pstCur->u32PhyAddr_C,0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);
	
    /*******************************next1**************************************/
    if (pstHalInfo->stInRefInfo[2].enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInRefInfo[2].enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInRefInfo[2].enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInRefInfo[2].enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir, NEXT1_FIELD, HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir, NEXT1_FIELD, HI_FALSE);
    }
    VPSS_REG_SetImgAddr(u32AppVir, NEXT1_FIELD, pstNxt1->u32PhyAddr_Y,
						pstNxt1->u32PhyAddr_C, pstNxt1->u32PhyAddr_Cr);
    VPSS_REG_SetImgStride(u32AppVir, NEXT1_FIELD, pstNxt1->u32Stride_Y, pstNxt1->u32Stride_C);

    /*****************************next2****************************************/
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir, NEXT2_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir, NEXT2_FIELD,HI_FALSE);
    }

    VPSS_REG_SetImgAddr(u32AppVir, NEXT2_FIELD, pstNxt2->u32PhyAddr_Y,
								pstNxt2->u32PhyAddr_C, pstNxt2->u32PhyAddr_Cr);
    VPSS_REG_SetImgStride(u32AppVir, NEXT2_FIELD, pstNxt2->u32Stride_Y, pstNxt2->u32Stride_C);	

    return HI_SUCCESS;
}



HI_S32 VPSS_HAL_SetFrameNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir, HI_U32 u32AppPhy)
{
	HI_U32 VPSS_Tnr_ADDR;
	HI_U32 VPSS_Tnr_CLUT_ADDR;
	HI_U32 VPSS_DBM_ADDR;
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstRef = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstRfr = HI_NULL;
    VPSS_NRMADCFG_S *pstNrMad = HI_NULL;
    
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);

    /* ???????????????????????? */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);

	VPSS_REG_SetRfrEn(u32AppVir, HI_TRUE);/* ?????????????? */
    VPSS_REG_SetTnrEn(u32AppVir, HI_TRUE);/* ????????TNR???? */

    /*tunnel*/
    if (pstHalInfo->stInInfo.u32TunnelAddr)
    {
        VPSS_REG_SetCurTunlEn(u32AppVir, HI_TRUE);
        VPSS_REG_SetCurTunlAddr(u32AppVir, CUR_FRAME, pstHalInfo->stInInfo.u32TunnelAddr);
    }
    else
    {
        VPSS_REG_SetCurTunlEn(u32AppVir, HI_FALSE);
    }
    
    #if 1
	/*rwzb*/
    VPSS_HAL_SetRwzbCfg(u32AppVir, &(pstHalInfo->stRwzbInfo));
    #endif
    
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }

    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);

    /* ?????????? */
    pstCur = &pstHalInfo->stInInfo.stAddr;
    VPSS_REG_SetImgSize(u32AppVir, 
				pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
				pstHalInfo->stInInfo.bProgressive);
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,pstCur->u32PhyAddr_Y,pstCur->u32PhyAddr_C,0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);
	
    /* ?????????? */
	pstRef = &pstHalInfo->stInRefInfo[0].stAddr;
	VPSS_REG_SetRefSize(u32AppVir,pstHalInfo->stInRefInfo[0].u32Width,pstHalInfo->stInRefInfo[0].u32Height);
    VPSS_REG_SetImgAddr(u32AppVir,LAST_FIELD,pstRef->u32PhyAddr_Y,pstRef->u32PhyAddr_C,0);
    VPSS_REG_SetImgStride(u32AppVir,LAST_FIELD, pstRef->u32Stride_Y, pstRef->u32Stride_C);

    /* ?????????? */
    pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
	VPSS_REG_SetRfrAddr(u32AppVir, pstRfr->u32PhyAddr_Y, pstRfr->u32PhyAddr_C);
	VPSS_REG_SetRfrStride(u32AppVir, pstRfr->u32Stride_Y, pstRfr->u32Stride_C);

	/* ???????? */
    pstNrMad = &pstHalInfo->stNrInfo.stNrMadCfg;
	VPSS_REG_SetMadRaddr(u32AppVir, pstNrMad->u32Tnrmad_raddr);
	VPSS_REG_SetMadWaddr(u32AppVir, pstNrMad->u32Tnrmad_waddr);
	VPSS_REG_SetMadStride(u32AppVir, pstNrMad->u32madstride);
    
    /*DBM*/
	VPSS_DBM_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_DB_CTRL) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_DBM_ADDR, VPSS_DBM_ADDR);
	VPSS_REG_SetDbmEn(u32AppVir,HI_TRUE);

	VPSS_REG_SetIglbEn(u32AppVir,HI_FALSE);
	VPSS_REG_SetIfmdEn(u32AppVir,HI_FALSE);

    /* ????Port???? */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, u32AppPhy, pstHalInfo);

	VPSS_Tnr_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_TNR_MODE) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_TNR_ADDR, VPSS_Tnr_ADDR);

	VPSS_Tnr_CLUT_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_TNR_CLUT10) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_TNR_CLUT_ADDR, VPSS_Tnr_CLUT_ADDR);

	VPSS_REG_SetSttWrAddr(u32AppVir, pstHalInfo->u32stt_w_phy_addr);

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_Set5FieldNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, 
    HI_U32 u32AppVir,HI_U32 u32AppPhy)
{
	HI_U32 VPSS_Tnr_ADDR;
	HI_U32 VPSS_Tnr_CLUT_ADDR;
	HI_U32 VPSS_DBM_ADDR;
		
    HI_DRV_VID_FRAME_ADDR_S *pstRfr  = HI_NULL;
//    HI_DRV_VID_FRAME_ADDR_S *pstPr1  = HI_NULL;
//    HI_DRV_VID_FRAME_ADDR_S *pstPr2  = HI_NULL;

    VPSS_DIESTCFG_S *pstDeiSt = HI_NULL;
    VPSS_NRMADCFG_S *pstNrMad = HI_NULL;
  
    VPSS_REG_ResetAppReg(u32AppVir, pstHalInfo->pstPqCfg);
    
    /* ???????????????????????? */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);

	VPSS_REG_SetRfrEn(u32AppVir, HI_TRUE);/* ?????????????? */
    VPSS_REG_SetTnrEn(u32AppVir, HI_TRUE);/* ????????TNR???? */

    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

	//	  pstPr1 = &pstHalInfo->stCCCLInfo.stInRefInfo[0].stAddr;
	//	  pstPr2 = &pstHalInfo->stCCCLInfo.stInRefInfo[1].stAddr;

    /*DEI*/
    VPSS_HAL_SetDeiCfg(enIP, pstHalInfo, u32AppVir, u32AppPhy);

    /* ?????????? */
    pstRfr = &pstHalInfo->stInWbcInfo.stAddr;
	VPSS_REG_SetRfrAddr(u32AppVir, pstRfr->u32PhyAddr_Y, pstRfr->u32PhyAddr_C);
	VPSS_REG_SetRfrStride(u32AppVir, pstRfr->u32Stride_Y, pstRfr->u32Stride_C);

	/* ????????  DEI*/
	pstDeiSt = &pstHalInfo->stDieInfo.stDieStCfg;	
	VPSS_REG_SetStRdAddr(u32AppVir, pstDeiSt->u32PPreAddr);
	VPSS_REG_SetStWrAddr(u32AppVir, pstDeiSt->u32PreAddr);
	VPSS_REG_SetStStride(u32AppVir, pstDeiSt->u32Stride);

	/* ???????? TNR*/
    pstNrMad = &pstHalInfo->stNrInfo.stNrMadCfg;
	VPSS_REG_SetMadRaddr(u32AppVir, pstNrMad->u32Tnrmad_raddr);
	VPSS_REG_SetMadWaddr(u32AppVir, pstNrMad->u32Tnrmad_waddr);
	VPSS_REG_SetMadStride(u32AppVir, pstNrMad->u32madstride);
   
    /*DBM*/
	VPSS_DBM_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_DB_CTRL) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_DBM_ADDR, VPSS_DBM_ADDR);
	VPSS_REG_SetDbmEn(u32AppVir,HI_TRUE);


	VPSS_REG_SetIglbEn(u32AppVir,HI_TRUE);
	VPSS_REG_SetIfmdEn(u32AppVir,HI_TRUE);

    /*RWZB*/
	#if 1
    VPSS_HAL_SetRwzbCfg(u32AppVir, &(pstHalInfo->stRwzbInfo));
	#endif
                                 
    /* ????Port???? */
    VPSS_HAL_SetPortCfg(enIP, u32AppVir, u32AppPhy, pstHalInfo);

	VPSS_Tnr_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_TNR_MODE) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_TNR_ADDR, VPSS_Tnr_ADDR);

	VPSS_Tnr_CLUT_ADDR = u32AppPhy + VPSS_REG_SIZE_CALC(VPSS_CTRL,VPSS_TNR_CLUT10) - sizeof(HI_U32);
	VPSS_REG_SetAddr(u32AppVir, REG_VPSS_TNR_CLUT_ADDR, VPSS_Tnr_CLUT_ADDR);

	VPSS_REG_SetSttWrAddr(u32AppVir, pstHalInfo->u32stt_w_phy_addr);
	
    return HI_SUCCESS;
}


HI_S32 VPSS_HAL_Set3DFrameNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir, HI_U32 u32AppPhy)
{
    HI_U32 u32W, u32H;


    (HI_VOID)VPSS_HAL_SetFrameNode(enIP, pstHalInfo, u32AppVir, u32AppPhy);

    /* ???????????????????? */
    switch(pstHalInfo->stInInfo.eFrmType)
    {
        case HI_DRV_FT_SBS:
            u32W = pstHalInfo->stInInfo.u32Width;
            VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,u32W,0);

            break;
            
        case HI_DRV_FT_TAB:
            u32H = pstHalInfo->stInInfo.u32Height;
            VPSS_REG_SetImgOffset(u32AppVir,CUR_FIELD,0,u32H);
            break;
            
        case HI_DRV_FT_FPK:
            break;
        default:
            VPSS_FATAL("eFrmType %d invaild\n", pstHalInfo->stInInfo.eFrmType);
            return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetRotateNode(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
    HI_U32 u32AppVir, HI_BOOL bRotateY, HI_U32 u32PortId)
{
    #if 1
    HI_DRV_VPSS_ROTATION_E enRotation;
    HI_DRV_VID_FRAME_ADDR_S *pstCur = HI_NULL;
    VPSS_REG_PORT_E enPort = VPSS_REG_HD;
    VPSS_HAL_FRAME_S *pstOutFrm = HI_NULL;
    HI_DRV_VID_FRAME_ADDR_S *pstOutAddr = HI_NULL;
    HI_U32 u32Angle;
    
    VPSS_REG_ResetAppReg(u32AppVir, NULL);

     /* ?????????? */
    VPSS_REG_SetInCropEn(u32AppVir, HI_FALSE);
    //VPSS_REG_SetImgBitWidth(u32AppVir, pstHalInfo->stInInfo.enBitWidth);
    VPSS_REG_SetImgFormat(u32AppVir, pstHalInfo->stInInfo.enFormat);
    VPSS_REG_SetImgSize(u32AppVir, 
        pstHalInfo->stInInfo.u32Width, pstHalInfo->stInInfo.u32Height,
        pstHalInfo->stInInfo.bProgressive);

    /* ?????????? */
    pstCur = &pstHalInfo->stInInfo.stAddr;

    /* ?????????? */
    if (pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP
        || pstHalInfo->stInInfo.enFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_TRUE);
    }
    else
    {
        VPSS_REG_SetImgTile(u32AppVir,CUR_FIELD,HI_FALSE);
    }
    
    VPSS_REG_SetImgAddr(u32AppVir,CUR_FIELD,
                        pstCur->u32PhyAddr_Y,
                        pstCur->u32PhyAddr_C,
                        0);
    VPSS_REG_SetImgStride(u32AppVir,CUR_FIELD, pstCur->u32Stride_Y, pstCur->u32Stride_C);

    /* ???????? */ 
    pstOutFrm = &pstHalInfo->astPortInfo[u32PortId].stOutInfo;
    pstOutAddr = &pstOutFrm->stAddr; 
    VPSS_REG_SetFrmSize(u32AppVir,enPort,pstOutFrm->u32Height, pstOutFrm->u32Width);
    VPSS_REG_SetFrmAddr(u32AppVir,enPort,pstOutAddr->u32PhyAddr_Y, pstOutAddr->u32PhyAddr_C);
    VPSS_REG_SetFrmStride(u32AppVir,enPort,pstOutAddr->u32Stride_Y,pstOutAddr->u32Stride_C);
    VPSS_REG_SetFrmFormat(u32AppVir,enPort,pstOutFrm->enFormat);        
    
    VPSS_REG_EnPort(u32AppVir, enPort, HI_TRUE);

    /* ???????? */ 
    enRotation = pstHalInfo->astPortInfo[u32PortId].enRotation;    
    switch(enRotation)
    {
        case HI_DRV_VPSS_ROTATION_90:
            u32Angle = 0x0;
            break;
        case HI_DRV_VPSS_ROTATION_270:
            u32Angle = 0x1;
            break;
        default:
            u32Angle = 0x1;
            VPSS_FATAL("Ro Error  %d\n",u32Angle);
            break;
    }
    
    if (bRotateY)
    {
        VPSS_REG_SetRotation(u32AppVir,u32Angle,1);
    }
    else
    {
        VPSS_REG_SetRotation(u32AppVir,u32Angle,2);
    }
    #endif
    return HI_SUCCESS;
}

HI_VOID VPSS_HAL_DumpReg(VPSS_IP_E enIP, VPSS_HAL_TASK_NODE_E enTaskNodeId)
{
    HI_U32 i;
    HI_U32 *pu32Reg;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    pstHalCtx = &stHalCtx[enIP];

    pu32Reg = (HI_U32 *)(pstHalCtx->au32AppVir[enTaskNodeId]);
    
    printk("\n\nPhyAddr %8x   enTaskNodeId = %d\n\n", 
        pstHalCtx->au32AppPhy[enTaskNodeId], enTaskNodeId);
    
    for(i=0; i<(64*4); i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }
    
    printk("\n\n");

    for(i=1024; i<1024+64; i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }

    printk("\n\n");

    for(i=2048; i<2048+64; i++)
    {
        if(i%(64) == 0)
        {
            printk("\nBASE %x", i*4);
        }

        if(i%4 == 0)
        {
            printk("\n%x0:", (i%64)/4);
        }
        
        printk("%.8x  ", *(pu32Reg+i));
    }

    printk("\n\n");

}

#if 0
/* ?????????????????? */
/* ?????????????????? */
#endif

HI_S32 VPSS_HAL_Init(VPSS_IP_E enIP)
{
	HI_U32 i;
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;

    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP];

    if (pstHalCtx->bInit)
    {
        VPSS_INFO("VPSS IP%d, Already Init\n", enIP);
        return HI_SUCCESS;
    }

    /* ??????????NODE???? */
    s32Ret = HI_DRV_MMZ_AllocAndMap("VPSS_RegBuf", HI_NULL,
        VPSS_REG_SIZE*VPSS_HAL_TASK_NODE_BUTT, 0, &pstHalCtx->stRegBuf);
    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Alloc VPSS_RegBuf Failed\n");
        return HI_FAILURE;
    }

    for (i=0; i<VPSS_HAL_TASK_NODE_BUTT; i++)
    {
        pstHalCtx->au32AppPhy[i] = pstHalCtx->stRegBuf.u32StartPhyAddr
                                 + VPSS_REG_SIZE*i;
        
        pstHalCtx->au32AppVir[i] = pstHalCtx->stRegBuf.u32StartVirAddr
                                 + VPSS_REG_SIZE*i;
    }


    /* ?????????????? */
    pstHalCtx->u32BaseRegVir
        = (HI_U32)IO_ADDRESS(pstHalCtx->u32BaseRegPhy);
    if (0 == pstHalCtx->u32BaseRegVir)
    {
        VPSS_FATAL("io_address VPSS_REG(%#x) Failed\n", pstHalCtx->u32BaseRegPhy);
        HI_DRV_MMZ_UnmapAndRelease(&pstHalCtx->stRegBuf);
        return HI_FAILURE;
    }

    pstHalCtx->bInit = HI_TRUE;

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);
    
    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_DelInit(VPSS_IP_E enIP)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);

    pstHalCtx = &stHalCtx[enIP];

    if (!pstHalCtx->bInit)
    {
        VPSS_INFO("VPSS IP%d, Already DeInit\n", enIP);
        return HI_SUCCESS;
    }

    VPSS_HAL_SetClockEn(enIP, HI_FALSE);

    HI_ASSERT(pstHalCtx->u32BaseRegVir != 0);
    if (pstHalCtx->u32BaseRegVir != 0)
    {
        pstHalCtx->u32BaseRegVir = 0;
    }

    HI_DRV_MMZ_UnmapAndRelease(&pstHalCtx->stRegBuf);
    memset(&pstHalCtx->stRegBuf, 0, sizeof(MMZ_BUFFER_S));

    pstHalCtx->bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_SetClockEn(VPSS_IP_E enIP, HI_BOOL bClockEn)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    if(pstHalCtx->bClockEn == bClockEn)
    {
        return HI_SUCCESS;
    }

    if (bClockEn)
    {
        VPSS_REG_SetClockEn(enIP, HI_TRUE);

        VPSS_REG_ResetAppReg(pstHalCtx->u32BaseRegVir, HI_NULL);
        VPSS_REG_SetTimeOut(pstHalCtx->u32BaseRegVir, DEF_LOGIC_TIMEOUT);
        VPSS_REG_SetIntMask(pstHalCtx->u32BaseRegVir, 0xfe);
    }
    else
    {
        VPSS_REG_SetClockEn(enIP, HI_FALSE);
    }

    pstHalCtx->bClockEn = bClockEn;

    return HI_SUCCESS;
}

HI_S32 VPSS_HAL_GetClockEn(VPSS_IP_E enIP, HI_BOOL *pbClockEn)
{
    //:TODO:????????CRG??????????
    return HI_SUCCESS;   
}

HI_S32 VPSS_HAL_GetIntState(VPSS_IP_E enIP, HI_U32* pu32IntState)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pu32IntState);

    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    return VPSS_REG_GetIntState(pstHalCtx->u32BaseRegVir, pu32IntState);
}

HI_S32 VPSS_HAL_ClearIntState(VPSS_IP_E enIP, HI_U32 u32IntState)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    return VPSS_REG_ClearIntState(pstHalCtx->u32BaseRegVir, u32IntState);
}

HI_S32 VPSS_HAL_SetNodeInfo(VPSS_IP_E enIP,
     VPSS_HAL_INFO_S *pstHalInfo,  VPSS_HAL_TASK_NODE_E enTaskNodeId)
{
    HI_U32 u32PortId = 0;    
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_U32 u32AppVir, u32AppPhy;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(pstHalInfo);
    VPSS_HAL_CHECK_NODE_ID_VAILD(enTaskNodeId);

    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    u32AppVir = pstHalCtx->au32AppVir[enTaskNodeId];
    u32AppPhy = pstHalCtx->au32AppPhy[enTaskNodeId];

    switch(pstHalInfo->enNodeType)
    {

        case VPSS_HAL_NODE_2D_FRAME:
            s32Ret = VPSS_HAL_SetFrameNode(enIP, pstHalInfo, u32AppVir, u32AppPhy);
            break;
        case VPSS_HAL_NODE_2D_5Field:
            s32Ret = VPSS_HAL_Set5FieldNode(enIP, pstHalInfo, u32AppVir, u32AppPhy);
            break;
        case VPSS_HAL_NODE_3D_FRAME_R:
            s32Ret = VPSS_HAL_Set3DFrameNode(enIP, pstHalInfo, u32AppVir, u32AppPhy);
            break;

        case VPSS_HAL_NODE_PZME:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;
        
        case VPSS_HAL_NODE_3DDET:
            //VPSS_HAL_SetFrameNode(pstHalInfo, u32AppVir);
            break;

        case VPSS_HAL_NODE_ROTATION_Y:
            u32PortId = (enTaskNodeId - VPSS_HAL_TASK_NODE_P0_RO_Y) / 2;//:TODO:????
            s32Ret = VPSS_HAL_SetRotateNode(enIP, pstHalInfo, u32AppVir, HI_TRUE,u32PortId);
            break;
        case VPSS_HAL_NODE_ROTATION_C:
            u32PortId = (enTaskNodeId - VPSS_HAL_TASK_NODE_P0_RO_Y) / 2;            
            s32Ret = VPSS_HAL_SetRotateNode(enIP, pstHalInfo, u32AppVir, HI_FALSE,u32PortId);
            break;
        default:
            VPSS_FATAL("No this Node Type:%d!\n", pstHalInfo->enNodeType);
            return HI_FAILURE;
            
    }

    (HI_VOID)VPSS_HAL_SetAllAlgCfgAddr(u32AppVir, u32AppPhy);

    //VPSS_FATAL("enTaskNodeId = %d, this Node Type:%d!\n", enTaskNodeId, pstHalInfo->enNodeType);
    //VPSS_HAL_DumpReg(enIP,enTaskNodeId);
    
    return s32Ret;
}

HI_S32 VPSS_HAL_StartLogic(VPSS_IP_E enIP, 
    HI_BOOL abNodeVaild[VPSS_HAL_TASK_NODE_BUTT])
{
    HI_U32 i = 0;
    VPSS_HAL_TASK_NODE_E enId, enLastVaild = VPSS_HAL_TASK_NODE_BUTT;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    VPSS_HAL_CHECK_IP_VAILD(enIP);
    VPSS_HAL_CHECK_NULL_PTR(abNodeVaild);
    
    pstHalCtx = &stHalCtx[enIP];
    VPSS_HAL_CHECK_INIT(pstHalCtx->bInit);

    /* ???????????????????? */
    enLastVaild = VPSS_HAL_TASK_NODE_BUTT;
    for(i=0;i<VPSS_HAL_TASK_NODE_BUTT;i++)
    {
        enId = VPSS_HAL_TASK_NODE_BUTT - 1 - i;
        
        if(HI_TRUE == abNodeVaild[enId])
        {
            if(VPSS_HAL_TASK_NODE_BUTT == enLastVaild)
            {
                VPSS_REG_StartLogic(0, pstHalCtx->au32AppVir[enId]);
            }
            else
            {
                VPSS_REG_StartLogic(pstHalCtx->au32AppPhy[enLastVaild], 
                    pstHalCtx->au32AppVir[enId]);
            }

            enLastVaild = enId;
        }
    }

    HI_ASSERT(enLastVaild != VPSS_HAL_TASK_NODE_BUTT);
    if (enLastVaild == VPSS_HAL_TASK_NODE_BUTT)
    {
        VPSS_FATAL("No Node Needs Start\n");
        return HI_FAILURE;
    }
    else
    {
        /* ???????? */
        return VPSS_REG_StartLogic(pstHalCtx->au32AppPhy[enLastVaild], 
                            pstHalCtx->u32BaseRegVir);
    }
}


HI_S32 VPSS_HAL_GetSCDInfo(HI_U32 u32AppAddr,HI_S32 s32SCDInfo[32])
{
	//return VPSS_REG_GetSCDInfo(u32AppAddr,s32SCDInfo);
	return HI_SUCCESS;
}

HI_VOID VPSS_HAL_GetDetPixel(HI_U32 u32AppAddr,HI_U32 BlkNum, HI_U8* pstData)
{
    VPSS_REG_GetDetPixel(u32AppAddr,BlkNum,pstData);
}

HI_S32 VPSS_HAL_GetBaseRegAddr(VPSS_IP_E enIP,
                                 HI_U32 *pu32PhyAddr,
                                 HI_U32 *pu32VirAddr)
{
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    
    pstHalCtx = &stHalCtx[enIP];

    *pu32PhyAddr = pstHalCtx->u32BaseRegPhy;
    *pu32VirAddr = pstHalCtx->u32BaseRegVir;
    
    return HI_SUCCESS;
}                                 

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif  /* __cplusplus */
