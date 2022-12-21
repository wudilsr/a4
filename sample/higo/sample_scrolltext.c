#include <stdio.h>
#include <stdlib.h>
#include "hi_go.h"
#include "sample_displayInit.h"

#define FONT_NAME "./res/DroidSansFallbackLegacy.ttf"

#define WIDTH 2560	//length of text buf,littler than 4096;adapt it with the length of text
HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32 s32Ret = 0;
    HI_HANDLE hFont = HIGO_INVALID_HANDLE;
    HIGO_LAYER_INFO_S stLayerInfo = {0};
    HI_HANDLE hLayer = HIGO_INVALID_HANDLE;
    HI_HANDLE hScrollTextLayer = HIGO_INVALID_HANDLE;
    HI_HANDLE hLayerSurface;
	HI_HANDLE hDecoder;
    HI_RECT stRect = {0, 0, WIDTH, 36};
    HI_CHAR szText[] = "滚动字幕sample!";
    HI_HANDLE hTextSurface;
    HI_PIXELDATA pData;  
    HI_HANDLE hScrollText;
    HIGO_SCROLLTEXT_ATTR_S stScrollAttr = {0};
    HIGO_SCROLLTEXT_DATA_S stScrollData = {0};
    HI_BOOL bScrollTextPause = HI_FALSE;  
    HI_U32  u32Cnt = 0;
    HI_U32 u32Offset = 0;
	HIGO_DEC_ATTR_S stDecAttr;
	
    s32Ret = Display_Init();
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = HI_GO_Init();
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR1;
    }

    //create main layer
    s32Ret = HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo); 
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR2;
    }

    stLayerInfo.PixelFormat = HIGO_PF_8888;
    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_FLIP;      
    s32Ret = HI_GO_CreateLayer(&stLayerInfo, &hLayer);
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR2;
    }

    s32Ret = HI_GO_GetLayerSurface(hLayer, &hLayerSurface);
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR3;        
    }

	stDecAttr.SrcType = HIGO_DEC_SRCTYPE_FILE;
	stDecAttr.SrcInfo.pFileName = "./res/jpg/Img201007080005_N.JPG";
	s32Ret = HI_GO_CreateDecoder(&stDecAttr, &hDecoder);
	if (HI_SUCCESS != s32Ret)
	{
		goto ERR3;
	}

	s32Ret = HI_GO_DecImgToSurface(hDecoder, 0, hLayerSurface);
	if (HI_SUCCESS != s32Ret)
	{
		goto ERR4;
	}

	HI_GO_RefreshLayer(hLayer, NULL);
	
    //create scrolltext layer
    s32Ret = HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_1, &stLayerInfo); 
    if(HI_SUCCESS != s32Ret)
    {
        goto ERR4;
    }

	stLayerInfo.CanvasHeight = stLayerInfo.DisplayHeight = stLayerInfo.ScreenHeight = 36;
    stLayerInfo.PixelFormat = HIGO_PF_8888;
    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_NORMAL;      
    s32Ret = HI_GO_CreateLayer(&stLayerInfo, &hScrollTextLayer);
    if(HI_SUCCESS != s32Ret)
    {
        goto ERR4;
    }

    s32Ret = HI_GO_CreateText(FONT_NAME, NULL,  &hFont);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR5;       
    }

    s32Ret = HI_GO_SetTextColor(hFont, 0xff000000);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR6;       
    }

    /*create text surface*/
    s32Ret = HI_GO_CreateSurface(WIDTH, 36, stLayerInfo.PixelFormat, &hTextSurface);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR6;       
    }

    s32Ret = HI_GO_LockSurface(hTextSurface, pData, HI_FALSE);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR7;       
    }
    
    s32Ret = HI_GO_UnlockSurface(hTextSurface);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR7;       
    }

    /*attibute of scrolltext*/
    stScrollAttr.ePixelFormat = stLayerInfo.PixelFormat; /*same with layer's*/
    stScrollAttr.Layer = hScrollTextLayer;	/*layer handle attach to*/
    stScrollAttr.u16CacheNum = 2;			/*cache num*/
    stScrollAttr.stScrollRect.x = 0;		/*startx of scrolltext*/
    stScrollAttr.stScrollRect.y = 0;		/*starty of scrolltext*/
    stScrollAttr.stScrollRect.w = 1280;		/*width of scrolltext*/
    stScrollAttr.stScrollRect.h = 36;		/*height of scrolltext*/
    stScrollAttr.bDeflicker = HI_TRUE;		/*enable deflicker*/
    s32Ret = HI_GO_CreateScrollText(&stScrollAttr, &hScrollText);
    if (HI_SUCCESS != s32Ret) 
    {
        goto ERR7;       
    }

    stRect.y = 4;
    stRect.h = 32;  
    stRect.x = 1280;
    stRect.w = WIDTH - stRect.x;

    /*background color of scrolltext*/
    s32Ret = HI_GO_FillRect(hTextSurface, NULL, 0xFFFFFFFF, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != s32Ret)
    {
    	printf("[%s:%d]\n", __FUNCTION__, __LINE__);
        goto ERR8; 
    }

	HI_GO_SyncSurface(hTextSurface, HIGO_SYNC_MODE_CPU);
	
    s32Ret = HI_GO_TextOutEx(hFont, hTextSurface, szText, &stRect, HIGO_LAYOUT_LEFT);
    if (HI_SUCCESS != s32Ret)
    {
    	printf("[%s:%d]\n", __FUNCTION__, __LINE__);
        goto ERR8; 
    }

	HIGO_ENC_ATTR_S stAttr = {HIGO_IMGTYPE_BMP, 0};
	HI_GO_EncodeToFile(hTextSurface, "text.bmp", &stAttr);

    while(1)
    {
        if (!bScrollTextPause)
        {
            u32Offset += 3;
            if (u32Offset >= WIDTH)
            {
                u32Offset = 0;
                continue;
            }
        }

        /*physical addr is perfered to virtual addr;virtual addr will be used only if physical 
		addr is equal to zero*/
        stScrollData.pu8VirAddr = (HI_U8 *)pData[0].pData + u32Offset*4;	/*virtual addr*/
        stScrollData.u32PhyAddr = (HI_U32)pData[0].pPhyData + u32Offset*4;	/*physical addr*/
        stScrollData.u32Stride = pData[0].Pitch;
        s32Ret = HI_GO_FillScrollText(hScrollText, &stScrollData);
        if (HI_SUCCESS != s32Ret)
        {
            continue;
        }

        /*pause scrolltext*/
        if(1000 == u32Cnt)
        {
            HI_GO_PauseScrollText(hScrollText);
            bScrollTextPause = HI_TRUE;
        }

        /*resume scrolltext*/
        if(2000 == u32Cnt)
        {
            HI_GO_ResumeScrollText(hScrollText);
            bScrollTextPause = HI_FALSE;
        }


        if(3000 == u32Cnt)
        {
            HI_GO_DestoryScrollText(hScrollText);
			break;
        }

        u32Cnt++;
    }
    
ERR8:
	HI_GO_DestoryScrollText(hScrollText);
ERR7:
	HI_GO_FreeSurface(hTextSurface);
ERR6:
	HI_GO_DestroyText(hFont);
ERR5:
	HI_GO_DestroyLayer(hScrollTextLayer);
ERR4:
	HI_GO_DestroyDecoder(hDecoder);
ERR3:
	HI_GO_DestroyLayer(hLayer);
ERR2:
	HI_GO_Deinit();
ERR1:
	Display_DeInit();
	
    return s32Ret;
}
