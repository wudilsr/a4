/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : sample_dec_phymem_phymem.c
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : 码流来源于连续物理内存，输出为用户的物理内存
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/

/****************************  add include here     ***************************/

#include "sample_api.h"

/***************************** Macro Definition     ***************************/


/***************************** Structure Definition ***************************/


/********************** Global Variable declaration **************************/
DECLARE_SAMPLE_DEC_SETJMP();


/********************** API forward declarations    **************************/

/****************************************************************************
* description	: CNcomment: 声明解码错误跳转函数 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
DECLARE_SAMPLE_DEC_ERR_FUNC();



/*****************************************************************************
* func		: sample_dec_phymemin_phymemout
* description: CNcomment: 连续物理内存输入连续物理内存输出  CNend\n
* param[in]	: *pFileName		CNcomment:要解码的文件	  CNend\n
* retval 	: NA
* others:	: NA
*****************************************************************************/
HI_VOID sample_dec_phymemin_phymemout(HI_CHAR *pFileName)
{

		struct jpeg_decompress_struct cinfo;
		JPEG_MYERR_S jerr;

		HI_U32 u32Width    = 0;
		HI_U32 u32Height   = 0;
        HI_U32 u32Stride   = 0;
		HI_U32 u32MemSize  = 0;

		HI_BOOL bHardDec;
		HI_S32 s32Ret       = HI_SUCCESS;
		
		FILE* pInFile = NULL;
		HI_U64 u64FileSize     = 0;
		HI_U64 u64ReadFileSize = 0;
        HI_CHAR *pSrcPhyBuf     = NULL;
        HI_CHAR *pSrcVirBuf     = NULL;

		
        HI_JPEG_INFO_S stJpegInfo;
	
		HI_JPEG_SURFACE_DESCRIPTION_S stSurfaceDesc;

        SAMPLE_TRACE("\n\n==================================================================================================\n");
		SAMPLE_TRACE("decode jpeg file is %s\n",pFileName);
		SAMPLE_TRACE("==================================================================================================\n");
		
		pInFile = fopen(pFileName,"rb");
		if(NULL == pInFile)
		{
		   SAMPLE_TRACE("open jpeg file failure");
           return;
		}
		
	    sample_get_file_size(pInFile,&u64FileSize);
	    if(0 == u64FileSize)
	    {
	       SAMPLE_TRACE("get jpeg file size failure\n");
		   fclose(pInFile);
	       return;
	    }

		pSrcPhyBuf = (HI_CHAR*)HI_GFX_AllocMem(u64FileSize, 256, (HI_CHAR*)"jpeg", (HI_CHAR*)"JPEG");
		if(NULL == pSrcPhyBuf)
		{
		    SAMPLE_TRACE("HI_GFX_AllocMem failure\n");
		    fclose(pInFile);
	        return;
		}
		pSrcVirBuf = (HI_CHAR*)HI_GFX_MapCached((HI_U32)pSrcPhyBuf); 
		if(NULL == pSrcVirBuf)
		{
		    SAMPLE_TRACE("HI_GFX_MapCached failure\n");
		    fclose(pInFile);
	        return;
		}
		memset(pSrcVirBuf,0,u64FileSize);
		HI_GFX_Flush((HI_U32)pSrcPhyBuf);
		
		u64ReadFileSize = fread(pSrcVirBuf,1,u64FileSize,pInFile);
		if (u64ReadFileSize != u64FileSize)
		{
		    SAMPLE_TRACE("=== %s : %s :%d fread failure \n",__FILE__,__FUNCTION__,__LINE__);
			fclose(pInFile);
			HI_GFX_Unmap((HI_U32)pSrcPhyBuf);
		    HI_GFX_FreeMem((HI_U32)pSrcPhyBuf);
			pSrcPhyBuf = NULL;
	        return;
		}
		HI_GFX_Flush((HI_U32)pSrcPhyBuf);


        memset(&stSurfaceDesc,0,sizeof(HI_JPEG_SURFACE_DESCRIPTION_S));


		/**
		 ** use ourself error manage function
		 **/
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = SAMPLE_DEC_ERR_FUCNTION;
		
		if (setjmp(SAMPLE_DEC_SETJMP_BUFFER))
		{
			goto DEC_FINISH;
		}

		/**
		 ** create decompress
		 **/
		jpeg_create_decompress(&cinfo);

		/**
		 ** set stream
		 **/		 
		HI_JPEG_SetStreamPhyMem(&cinfo,pSrcPhyBuf);
	    jpeg_mem_src(&cinfo,(HI_UCHAR*)pSrcVirBuf,u64FileSize);

		/**
		 ** parse file
		 **/
	    jpeg_read_header(&cinfo, TRUE);
		
		/**
		 ** set scale and output color space
		 **/
		 cinfo.scale_num   = 1 ;
	     cinfo.scale_denom = 2;
         cinfo.out_color_space = JCS_BGR;

		
        stJpegInfo.bOutInfo = HI_TRUE;
		s32Ret = HI_JPEG_GetJpegInfo(&cinfo,&stJpegInfo);

        u32Width   = stJpegInfo.u32Width[0];
		u32Height  = stJpegInfo.u32Height[0];
		u32Stride  = stJpegInfo.u32OutStride[0];
        u32MemSize = stJpegInfo.u32OutSize[0];
			

		if(0 != u32MemSize)
		{
			 stSurfaceDesc.stOutSurface.pOutPhy[0] = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, 256, (HI_CHAR*)"jpeg", (HI_CHAR*)"JPEG");
			 if(NULL == stSurfaceDesc.stOutSurface.pOutPhy[0])
			 {
				goto DEC_FINISH;
			 }
			 stSurfaceDesc.stOutSurface.pOutVir[0] = (HI_CHAR*)HI_GFX_MapCached((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]); 
			 if(NULL == stSurfaceDesc.stOutSurface.pOutVir[0])
			 {
				goto DEC_FINISH;
			 }
			 memset(stSurfaceDesc.stOutSurface.pOutVir[0],0,u32MemSize);
			 HI_GFX_Flush((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
				 
		}
		stSurfaceDesc.stOutSurface.bUserPhyMem = HI_TRUE;
		stSurfaceDesc.stOutSurface.u32OutStride[0] = u32Stride; 
		s32Ret = HI_JPEG_SetOutDesc(&cinfo, &stSurfaceDesc);
		if(HI_SUCCESS != s32Ret)
		{
		   SAMPLE_TRACE("HI_JPEG_SetOutDesc failure\n");
		   goto DEC_FINISH;
		}


		/**
		 ** start decode
		 **/
	    jpeg_start_decompress(&cinfo);

		HI_JPEG_IfHardDec(&cinfo,&bHardDec);
		if(HI_TRUE == bHardDec)
		{
		    SAMPLE_TRACE("=========================\n");
            SAMPLE_TRACE("hard dec success\n");
			SAMPLE_TRACE("=========================\n");
		}
		else
	    {

	        SAMPLE_TRACE("=========================\n");
            SAMPLE_TRACE("soft dec success\n");
			SAMPLE_TRACE("=========================\n");
		}
		/**
		 ** output the decode data
		 **/
		while (cinfo.output_scanline < cinfo.output_height) 
	    {
		    jpeg_read_scanlines(&cinfo, NULL, 1);
		}

		/**
		 **这个地方是输出到连续物理内存，由用户决定是否刷cach,内部
		 **TDE转换直接转到物理内存，没有对虚拟内存做操作
		 **/
        HI_GFX_Flush((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);

		test_dec_show(u32Width,u32Height,u32Stride,stSurfaceDesc.stOutSurface.pOutVir[0],cinfo.out_color_space);
		
		/**
		 ** finish decode
		 **/
		jpeg_finish_decompress(&cinfo);
		
DEC_FINISH:

		/**
		 ** destory decode
		 **/
      	jpeg_destroy_decompress(&cinfo);
		
		fclose(pInFile);
		pInFile = NULL;
		
		if(NULL != stSurfaceDesc.stOutSurface.pOutPhy[0])
		{
			HI_GFX_Unmap((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
	        HI_GFX_FreeMem((HI_U32)stSurfaceDesc.stOutSurface.pOutPhy[0]);
		}

		if(NULL != pSrcPhyBuf)
		{
			HI_GFX_Unmap((HI_U32)pSrcPhyBuf);
	        HI_GFX_FreeMem((HI_U32)pSrcPhyBuf);
			pSrcPhyBuf = NULL;
		}

		return;
		
}
int main(int argc,char** argv)
{

		HI_S32 s32Ret = HI_SUCCESS;
		HI_CHAR pFileName[256] = {0};
		DIR *dir = NULL;
		struct dirent *ptr = NULL;
		
		dir = opendir(SAMPLE_DEC_JPEG_FILE_DIR);
		if(NULL==dir)
		{
		 	SAMPLE_TRACE("open jpeg file directory failure \n");
			return HI_FAILURE;
		}

		Display_Init();
		while((ptr = readdir(dir))!=NULL)
        {
             s32Ret = sample_getjpegfilename(ptr->d_name,pFileName);
             if(HI_FAILURE == s32Ret)
			 {
                continue;
             }
			 sample_dec_phymemin_phymemout(pFileName);
		}

		closedir(dir);

		Display_DeInit();
		
		return 0;
}
