#include "sre_syscalls_id_ext.h"
/*efuse begin*/
    .global __bsp_efuse_read
    .global __bsp_efuse_write
    .global __tee_hal_get_dieid
    .global __driver_dep_test
    .global __driver_p61_factory_test
/*efuse end*/
    .global __scard_connect
    .global __scard_disconnect
    .global __scard_transmit
    .global __driver_fingerprint_command
    .global __driver_spi_full_duplex
//#ifdef TEE_SUPPORT_TUI
    .global __hisi_tui_get_tpdata
    .global __set_notify_addr
    .global __send_simu_tp

/*display begin*/
    .global __hisi_fb_cfg_sec
    .global __hisi_pan_display_sec
    .global __hisi_wait_vactive_flag
    .global __hisi_wait_release_flag
    .global __hisi_get_disp_info
    .global __hisi_fb_alpha_set
/*display end*/

#ifdef TEE_SUPPORT_TUI
    .global __can_enter_tui_loop
    .global __init_tui_sdriver
#endif
    .global __is_device_rooted
#ifdef WITH_HISI_VFMW
    .global __VDEC_Suspend
    .global __VDEC_Init
    .global __VDEC_Resume
    .global __VFMW_CTRL_thread_sec
    .global __VDEC_Control
    .global __VDEC_InitWithOperation
    .global __VCTRL_WriteProc
    .global __VCTRL_ReadProc
    .global __VCTRL_SetDbgOption
    .global __VCTRL_GetChanImage
    .global __VCTRL_ReleaseChanImage
    .global __VDEC_Exit
#endif
    
/*vdp begin*/
#ifdef WITH_HISI_VDP
    .global __vdp_drv_Ioctl
#endif
/*vdp end*/
#ifdef WITH_HISI_SEC_MMZ
    .global __MMZ_NEW
    .global __MMZ_DEL
    .global __MMZ_MALLOC
    .global __MMZ_FREE
    .global __MMZ_MAP
    .global __MMZ_UNMAP
    .global __MMZ_FLUSH
    .global __TEE_IsSecMMZ
    .global __TEE_IsSecMem
    .global __TEE_IsNonSecMem
    .global __call_debug
#endif
#if defined(WITH_HISI_CIPHER)
    .global __TEE_CIPHER_Ioctl
	.global __CRYS_PKCS5_PBKDF2_HMAC1
#endif
#ifdef WITH_HISI_OTP
/*otp begin*/
    .global __OTP_Init
    .global __OTP_DeInit
    .global __OTP_Reset
    .global __OTP_GetChipID
    .global __OTP_ReadWord
    .global __OTP_ReadByte
    .global __OTP_WriteWord
    .global __OTP_WriteByte
    .global __OTP_Test
/*otp end*/
#endif
#ifdef WITH_HISI_ADVCA
    .global __TEE_ADVCA_Ioctl

#endif
    .global __get_vsim_sharemem

#ifdef WITH_HISI_SMMU
    .global __hisi_sec_maptosmmu
    .global __hisi_sec_unmapfromsmmu
    .global __hisi_sec_maptosmmu_and_setflag
    .global __hisi_sec_unmapfromsmmu_and_clrflg
    .global __hisi_sec_alloc
    .global __hisi_sec_free
    .global __hisi_sec_map_to_cpu
    .global __hisi_sec_unmap_from_cpu
    .global __hisi_sec_map_to_sec_smmu
    .global __hisi_sec_unmap_from_sec_smmu
    .global __hisi_nonsec_mem_map_to_sec_cpu
    .global __hisi_nosec_mem_unmap_from_sec_cpu
    .global __hisi_nosec_mem_map_to_sec_smmu
    .global __hisi_nosec_mem_unmap_from_sec_smmu
    .global __agent_closed
    .global __sec_ioctl
    .global __hisi_mem_flush
#endif
    .global __get_target_product

    .global __bsp_sec_call

#ifdef WITH_HISI_DMX 
    .global __TEE_DRV_DMX_CreateDescrambler
    .global __TEE_DRV_DMX_DestroyDescrambler
    .global __TEE_DRV_DMX_AttachDescrambler
    .global __TEE_DRV_DMX_DetachDescrambler
    .global __TEE_DRV_DMX_GetDescramblerAttr
    .global __TEE_DRV_DMX_SetDescramblerAttr
    .global __TEE_DRV_DMX_SetDescramblerEvenKey
    .global __TEE_DRV_DMX_SetDescramblerOddKey
    .global __TEE_DRV_DMX_SetDescramblerEvenIVKey
    .global __TEE_DRV_DMX_SetDescramblerOddIVKey
    .global __TEE_DRV_DMX_GetDescramblerKeyHandle
    .global __TEE_DRV_DMX_CreateScrambler
    .global __TEE_DRV_DMX_DestroyScrambler
    .global __TEE_DRV_DMX_AttachScrambler
    .global __TEE_DRV_DMX_DetachScrambler
    .global __TEE_DRV_DMX_GetScramblerAttr
    .global __TEE_DRV_DMX_SetScramblerAttr
    .global __TEE_DRV_DMX_SetScramblerEvenKey
    .global __TEE_DRV_DMX_SetScramblerOddKey
    .global __TEE_DRV_DMX_GetScramblerKeyHandle
    .global __TEE_DRV_DMX_GetChannelHandle
    .global __TEE_DRV_DMX_RegisterChannel
    .global __TEE_DRV_DMX_UnregisterChannel
    .global __TEE_DRV_DMX_RegisterOq
    .global __TEE_DRV_DMX_UnregisterOq
    .global __TEE_DRV_DMX_RegisterRamPort
    .global __TEE_DRV_DMX_UnregisterRamPort
    .global __TEE_DRV_DMX_LockChannel
    .global __TEE_DRV_DMX_UnlockChannel
    .global __TEE_DRV_DMX_RegisterVidSecBuf
    .global __TEE_DRV_DMX_UnregisterVidSecBuf
    .global __TEE_DRV_DMX_RegisterAudSecBuf
    .global __TEE_DRV_DMX_UnregisterAudSecBuf
    .global __TEE_DRV_DMX_FixupAudSecBuf
    .global __TEE_DRV_DMX_ParserPesHeader
    .global __TEE_DRV_DMX_ParserPesDispCtrlInfo
    .global __TEE_DRV_DMX_GetPesHeaderLen
    .global __TEE_DRV_DMX_RegisterRecSecBuf
    .global __TEE_DRV_DMX_UnregisterRecSecBuf
    .global __TEE_DRV_DMX_ParserSCData
    .global __TEE_DRV_DMX_ParserFilterSCData
#endif
#ifdef WITH_HISI_PVR 
    .global __TEE_PVR_DeInit
    .global __TEE_PVR_OpenChannel
    .global __TEE_PVR_CloseChannel
    .global __TEE_PVR_RecProcTsData
    .global __TEE_PVR_RecCopyToRee
    .global __TEE_PVR_PlayCopyFromRee
    .global __TEE_PVR_RecGetStatus
    .global __TEE_PVR_RecGetOutputBufInfo
#endif
    .align 5

__bsp_efuse_read:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_EFUSE_READ
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__bsp_efuse_write:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_EFUSE_WRITE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__tee_hal_get_dieid:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_TEE_HAL_GET_DIEID
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__scard_connect:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_SCARD_CONNECT
    sub sp, fp, #4
    pop {fp, lr}
    bx lr
__scard_disconnect:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_SCARD_DISCONNECT
    sub sp, fp, #4
    pop {fp, lr}
    bx lr
__scard_transmit:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_SCARD_TRANSMIT
    sub sp, fp, #4
    pop {fp, lr}
    bx lr
#ifdef TEE_SUPPORT_TUI
__hisi_tui_get_tpdata:
    push {fp, lr}
    add fp, sp, #4
    swi SW_TP_GET_DATA
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__set_notify_addr:
    push {fp, lr}
    add fp, sp, #4
    swi SW_TP_SET_NOTIFY_ADDR
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

//#ifdef TEE_SUPPORT_TUI
__init_tui_sdriver:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_TUI_INIT_SDRIVER
    sub sp, fp, #4
    pop {fp, lr}
    bx lr
#endif

__driver_dep_test:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DRIVER_TEST
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__driver_p61_factory_test:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_P61_FAC_TEST
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_fb_cfg_sec:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_SEC_CFG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_fb_alpha_set:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_SEC_SET
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
/* del by f00216599
#ifdef CC_DERIVER
__send_simu_tp:
    push {fp, lr}
    add fp, sp, #4
    swi SW_TP_SET_SIMU_DATA
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
#endif
*/
__hisi_pan_display_sec:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_SEC_DISPLAY
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__hisi_wait_vactive_flag:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_ACTIVE_FLAG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__hisi_wait_release_flag:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_RELEASE_FLAG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__hisi_get_disp_info:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FB_GETINFO
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__is_device_rooted:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_IS_DEVICE_ROOTED
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

 #ifdef WITH_HISI_VFMW
 __VDEC_Suspend:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_SUSPEND
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VDEC_Init:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_INIT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VDEC_Resume:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_RESUME
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VFMW_CTRL_thread_sec:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VFMW_THREADPROC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VDEC_Control:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_CONTROL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VDEC_InitWithOperation:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_INITWITHOPERATION
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VCTRL_WriteProc:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VFMW_WRITEPROC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VCTRL_ReadProc:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VFMW_READPROC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VCTRL_SetDbgOption:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VCTRL_SETDBGOPTION
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VCTRL_GetChanImage:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VFMW_GETCHANIMAGE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VCTRL_ReleaseChanImage:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VFMW_RELEASECHANIMAGE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__VDEC_Exit:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_VDEC_EXIT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
#endif
  
#ifdef WITH_HISI_SEC_MMZ
__MMZ_NEW:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_NEW
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_DEL:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_DEL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_MALLOC:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_MALLOC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_FREE:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_FREE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_MAP:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_MAP
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_UNMAP:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_UNMAP
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__MMZ_FLUSH:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MMZ_FLUSH
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_IsSecMMZ:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_TEE_ISSECMMZ
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__mem_copy:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_MEM_COPY
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_IsSecMem:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_TEE_ISSECMEM
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_IsNonSecMem:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_TEE_ISNONSECMEM
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__call_debug:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEBUG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
#endif

#if defined(WITH_HISI_CIPHER)
__TEE_CIPHER_Ioctl:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_CIPHER_IOCTL
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__CRYS_PKCS5_PBKDF2_HMAC1:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_CIPHER_PBKDF2
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

#endif

#ifdef WITH_HISI_OTP
__OTP_Init:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_INIT
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_DeInit:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_DeInit
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_Reset:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_Reset
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_GetChipID:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_GetChipID
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_ReadWord:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_ReadWord
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_ReadByte:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_ReadByte
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_WriteWord:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_WriteWord
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_WriteByte:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_WriteByte
    sub sp, fp, #4
    pop {fp, lr}
    bx lr

__OTP_Test:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_OTP_Test
    sub sp, fp, #4
    pop {fp, lr}
    bx lr
#endif

#ifdef WITH_HISI_ADVCA

__TEE_ADVCA_Ioctl:
	push {fp, lr}
	add fp, sp, #4
	swi SW_SYSCALL_ADVCA_IOCTL
	sub sp, fp, #4
	pop {fp, lr}
	bx lr
#endif

#ifdef WITH_HISI_SMMU
__hisi_sec_maptosmmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_MAPTOSMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_unmapfromsmmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_UNMAPFROMSMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_maptosmmu_and_setflag:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_MAPTOSMMU_AND_SETFLAG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_unmapfromsmmu_and_clrflg:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_UNMAPFROMSMMU_AND_CLRFLG
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_alloc:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_ALLOC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_free:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_FREE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_map_to_cpu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_MAP_TO_CPU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_unmap_from_cpu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_UNMAP_FROM_CPU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_map_to_sec_smmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_MAP_TO_SEC_SMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_sec_unmap_from_sec_smmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_SEC_UNMAP_FROM_SEC_SMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__hisi_nonsec_mem_map_to_sec_cpu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_NONSEC_MEM_MAP_TO_SEC_CPU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_nosec_mem_unmap_from_sec_cpu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_NOSEC_MEM_UNMAP_FROM_SEC_CPU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_nosec_mem_map_to_sec_smmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_NOSEC_MEM_MAP_TO_SEC_SMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_nosec_mem_unmap_from_sec_smmu:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_NOSEC_MEM_UNMAP_FROM_SEC_SMMU
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__agent_closed:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_AGENT_CLOSED
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__sec_ioctl:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_SEC_IOCTL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__hisi_mem_flush:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HISI_MEM_FLUSH
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

#endif
__get_vsim_sharemem:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_GET_VSIM_SHAREMEM
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__driver_fingerprint_command:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FP_COMMAND_INFO
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
__driver_spi_full_duplex:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_FP_SPI_TRANSACTION
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
#if 0 // del by f00216599
__get_target_product:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_GET_TARGET_PRODUCT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
#endif
__bsp_sec_call:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_BSP_SEC_CALL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

#ifdef WITH_HISI_VDP
 __vdp_drv_Ioctl:
     push {fp, lr}
     add fp, sp, #4
     swi SW_SYSCALL_VDP_DRV_IOCTL
     sub fp, sp, #4
     pop {fp, lr}
     bx lr
#endif
#ifdef WITH_HISI_DMX
__TEE_DRV_DMX_CreateDescrambler:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_NEW_DESC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_DestroyDescrambler:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_DEL_DESC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_AttachDescrambler:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_ATTACH_DESC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_DetachDescrambler:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_DETACH_DESC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_GetDescramblerAttr:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_DESC_ATTR
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetDescramblerAttr:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_DESC_ATTR
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetDescramblerEvenKey:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_DESC_EVEN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetDescramblerOddKey:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_DESC_ODD
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetDescramblerEvenIVKey:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_DESC_EVEN_IV
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetDescramblerOddIVKey:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_DESC_ODD_IV
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_GetDescramblerKeyHandle:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_KEYID
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_CreateScrambler:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_NEW_SC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_DestroyScrambler:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_DEL_SC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_GetScramblerAttr:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_SC_ATTR
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetScramblerAttr:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_SC_ATTR
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetScramblerEvenKey:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_SC_EVEN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_SetScramblerOddKey:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_SET_SC_ODD
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_AttachScrambler:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_ATTACH_SC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_DetachScrambler:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_DETACH_SC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_GetScramblerKeyHandle:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_SC_KEYID
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
    
__TEE_DRV_DMX_GetChannelHandle:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_CHNID
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_RegisterChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_CHAN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnregisterChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_CHAN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_RegisterOq:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_OQ
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnregisterOq:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_OQ
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_RegisterRamPort:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_RAM_PORT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnregisterRamPort:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_RAM_PORT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_LockChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_LOCK_CHAN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnlockChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNLOCK_CHAN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_RegisterVidSecBuf:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_VID_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnregisterVidSecBuf:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_VID_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_RegisterAudSecBuf:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_AUD_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_UnregisterAudSecBuf:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_AUD_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_FixupAudSecBuf:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_FIXUP_AUD_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_ParserPesHeader:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_PARSER_PES_HEADER
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_ParserPesDispCtrlInfo:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_PARSER_DISP_CONTROL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__TEE_DRV_DMX_GetPesHeaderLen:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_GET_PES_HEADER_LEN
    sub fp, sp, #4
    pop {fp, lr}
    bx lr    

__TEE_DRV_DMX_RegisterRecSecBuf:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_REG_REC_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr   
    
__TEE_DRV_DMX_UnregisterRecSecBuf:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_UNREG_REC_SECBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr  

__TEE_DRV_DMX_ParserSCData:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_PARSER_SC_DATA
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 

__TEE_DRV_DMX_ParserFilterSCData:
	push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_DEMUX_PARSER_FILTER_SC_DATA
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
#endif

#ifdef WITH_HISI_PVR
__TEE_PVR_DeInit:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_DeInit
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
__TEE_PVR_OpenChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_OPEN_CHANNEL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
__TEE_PVR_CloseChannel:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_CLOSE_CHANNEL
    sub fp, sp, #4
    pop {fp, lr}
    bx lr  
__TEE_PVR_RecProcTsData:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_PROC_TSDATA
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
__TEE_PVR_RecCopyToRee:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_COPY_TO_REE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
__TEE_PVR_PlayCopyFromRee:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_COPY_TO_TEE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr 
__TEE_PVR_RecGetOutputBufInfo:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_GET_OUTPUTBUF
    sub fp, sp, #4
    pop {fp, lr}
    bx lr  
__TEE_PVR_RecGetStatus:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_PVR_GET_TEE_STATE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr      
#endif

#ifdef WITH_HISI_SEC_HDMI

    .global __HI_DRV_HDMI_SetSRM
    .global __HI_DRV_HDMI_SetHDCPStrategy
    .global __HI_DRV_HDMI_GetHDCPStrategy
    .global __HI_DRV_HDMI_GetHDCPStatus
    .global __HI_DRV_HDMI_SetHDCPMute
    .global __HI_DRV_HDMI_HDCP22_Init
    .global __HI_DRV_HDMI_TeeProc
    .global __HI_DRV_HDMI_SetHDCPCaps
    .global __HI_DRV_HDMI_GetHDCPCaps
    .global __HI_DRV_HDMI_Init
    .global __HI_DRV_HDMI_DeInit
    .global __HI_DRV_HDMI_Start
    .global __HI_DRV_HDMI_Stop

__HI_DRV_HDMI_SetSRM:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_SETSRM
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_SetHDCPStrategy:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_SETHDCPSTRATEGY
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_GetHDCPStrategy:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_GETHDCPSTRATEGY
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_GetHDCPStatus:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_GETHDCPSTATUS
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_SetHDCPMute:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_SETHDCPMUTE
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_HDCP22_Init:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_HDCP22_INIT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_TeeProc:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_TEEPROC
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_SetHDCPCaps:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_SETHDCPCAPS
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_GetHDCPCaps:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_GETHDCPCAPS
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_Init:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_INIT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_DeInit:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_DEINIT
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_Start:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_START
    sub fp, sp, #4
    pop {fp, lr}
    bx lr

__HI_DRV_HDMI_Stop:
    push {fp, lr}
    add fp, sp, #4
    swi SW_SYSCALL_HI_DRV_HDMI_STOP
    sub fp, sp, #4
    pop {fp, lr}
    bx lr
    

#endif


