/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_api_tde.h
* Description:TDE2 API define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _HI_JPGE_API_H_
#define _HI_JPGE_API_H_

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#include "hi_type.h"
#include "hi_jpge_type.h"


/****************************************************************************/
/*                             TDE2 API define                               		       */
/****************************************************************************/

/** 
\brief  open jpeg encoder device
\attention \n
make sure call this function before  using some other jpeg encoder function.
and the status of jpeg encoder device must be open \n
 
\param  none
\retval ::HI_SUCCESS
\retval ::HI_ERR_JPGE_DEV_OPEN_FAILED TDE device not open.need to call HI_JPGE_Open first
\see \n
none
*/
HI_S32      HI_JPGE_Open(HI_VOID);


/** 
\brief  close jpeg encoder device
\attention \n
the number of calling HI_JPGE_Open and HI_JPGE_Close must be the same\n
\param  none
\retval none
\see \n
none
*/
HI_VOID    HI_JPGE_Close(HI_VOID);


/** 
\brief create jpeg encoder, and finish some Initialization
\attention none
\param[1] pEncHandle  handle of encoder
\param[2] pEncCfg   the parameters for creating jpeg encoder

\retval ::HI_ERR_JPGE_DEV_NOT_OPEN  device not open.need to call HI_JPGE_Open first
\retval ::HI_ERR_JPGE_NULL_PTR  parameter is null
\retval ::HI_SUCCESS 
\see \n
none
*/
HI_S32  HI_JPGE_Create( HI_U32 *pEncHandle, const Jpge_EncCfg_S *pEncCfg );


/** 
\brief jpeg encoding
\attention \n
make sure jpeg encoder device is open,and EncHandle is an valid handle for encoder\n

\param[in] EncHandle  hanlde for jpeg encoder
\param[in] pEncIn   parameter that for input
\param[in] pEncOut  parameter that for output

\retval ::HI_ERR_JPGE_DEV_NOT_OPEN  device not open.need to call HI_JPGE_Open first
\retval ::HI_ERR_JPGE_NULL_PTR  parameter is null
\retval ::HI_SUCCESS 

\see \n
none
*/
HI_S32      HI_JPGE_Encode( HI_U32 EncHandle, const Jpge_EncIn_S *pEncIn, Jpge_EncOut_S *pEncOut );

/** 
\brief destroy jpeg encoder handle and the relevant resource
\attention \n
make sure jpeg encoder device is open,and EncHandle is an valid handle for encoder\n

\param[in] EncHandle  handle of encoder

\retval ::HI_FAILURE 
\retval ::HI_SUCCESS 


\see \n
none
*/

HI_S32      HI_JPGE_Destroy( HI_U32   EncHandle );




#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _HI_JPGE_API_H_ */
