#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
HDMI_VER := hdmi_1_4
else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
HDMI_VER := hdmi_2_0
endif

HDMI_DRV_DIR := $(MSP_DIR)/drv/hdmi/$(HDMI_VER)

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/hdmi                   \
                -I$(MSP_DIR)/drv/hdmi/$(HDMI_VER)       \
                -I$(MSP_DIR)/api/sio                    \
                -I$(MSP_DIR)/api/higo/include

ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
EXTRA_CFLAGS += -I$(MSP_DIR)/drv/hdmi/$(HDMI_VER)/hdmi_drv

EXTRA_CFLAGS += -DDVI_SUPPORT

ifeq ($(CFG_PRODUCT_TYPE), android)
EXTRA_CFLAGS += -DANDROID_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_DVI), y)
EXTRA_CFLAGS += -DDVI_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP), y)
EXTRA_CFLAGS += -DHDCP_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_3D), y)
EXTRA_CFLAGS += -DSUPPORT_3D
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_CEC), y)
EXTRA_CFLAGS += -DCEC_SUPPORT
endif

EXTRA_CFLAGS += -DDEBUG_SUPPORT

else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
EXTRA_CFLAGS += -DCONFIG_HDMI_STB_SDK

EXTRA_CFLAGS += -DHDMI_DVI_SUPPORT
EXTRA_CFLAGS += -DHDMI_SCDC_SUPPORT

ifeq ($(CFG_PRODUCT_TYPE), android)
EXTRA_CFLAGS += -DHDMI_ANDROID_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_DVI), y)
EXTRA_CFLAGS += -DHDMI_DVI_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP), y)
EXTRA_CFLAGS += -DHDMI_HDCP_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_3D), y)
EXTRA_CFLAGS += -DHDMI_3D_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_CEC), y)
EXTRA_CFLAGS += -DHDMI_CEC_SUPPORT
endif

EXTRA_CFLAGS += -DHDMI_DEBUG_SUPPORT
endif

#ifeq ($(CFG_HI_HDMI_SUPPORT_FPGA), y)
#EXTRA_CFLAGS += -DSUPPORT_FPGA
#endif

ifdef CFG_HI_HDMI_DEBUG_MEM_SIZE
EXTRA_CFLAGS += -DABS_BUF_DEBUG_LEN=$(CFG_HI_HDMI_DEBUG_MEM_SIZE)
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_DEBUG), y)
EXTRA_CFLAGS += -DHDMI_DEBUG
endif

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_hdmi

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
$(MOD_NAME)-y   +=  $(HDMI_VER)/hdmi_intf_k.o                   \
                    $(HDMI_VER)/hdmi_intf.o                     \
                    $(HDMI_VER)/drv_hdmi.o                      \
                    $(HDMI_VER)/drv_global.o                    \
                    $(HDMI_VER)/drv_reg_proc.o                  \
                    $(HDMI_VER)/drv_compatibility.o             \
                    $(HDMI_VER)/hdmi_drv/drv_hlviic.o           \
                    $(HDMI_VER)/hdmi_drv/si_audio.o             \
                    $(HDMI_VER)/hdmi_drv/si_cec.o               \
                    $(HDMI_VER)/hdmi_drv/si_crc16.o             \
                    $(HDMI_VER)/hdmi_drv/si_de.o                \
                    $(HDMI_VER)/hdmi_drv/si_delay.o             \
                    $(HDMI_VER)/hdmi_drv/si_edid.o              \
                    $(HDMI_VER)/hdmi_drv/si_eeprom.o            \
                    $(HDMI_VER)/hdmi_drv/si_fifo.o              \
                    $(HDMI_VER)/hdmi_drv/si_hdcp.o              \
                    $(HDMI_VER)/hdmi_drv/si_hdmitx.o            \
                    $(HDMI_VER)/hdmi_drv/si_infofrm.o           \
                    $(HDMI_VER)/hdmi_drv/si_infpkttb.o          \
                    $(HDMI_VER)/hdmi_drv/si_isr.o               \
                    $(HDMI_VER)/hdmi_drv/si_mddc.o              \
                    $(HDMI_VER)/hdmi_drv/si_regio.o             \
                    $(HDMI_VER)/hdmi_drv/si_sha.o               \
                    $(HDMI_VER)/hdmi_drv/si_sha_hw.o            \
                    $(HDMI_VER)/hdmi_drv/si_timer.o             \
                    $(HDMI_VER)/hdmi_drv/si_txvidp.o            \
                    $(HDMI_VER)/hdmi_drv/si_txvptbl.o           \
                    $(HDMI_VER)/hdmi_drv/si_ucec.o              \
                    $(HDMI_VER)/hdmi_drv/si_video.o             \
                    $(HDMI_VER)/hdmi_drv/si_vmode.o             \
                    $(HDMI_VER)/hdmi_drv/si_vmtables.o          \
                    $(HDMI_VER)/hdmi_drv/si_phy.o

ifeq ($(CFG_HI_HDMI_SUPPORT_DEBUG), y)
$(MOD_NAME)-y += $(HDMI_VER)/drv_abs_debug.o
$(MOD_NAME)-y += $(HDMI_VER)/drv_hdmi_debug.o
endif

else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
HAL_DIR := hal/Hifone

EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/hal
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/common
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/cpi
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tpg
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/vtg
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/pll
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/cra
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx/hdcp
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx/scdc
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx/tx_hdmi
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx/videopath
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/driver/tx/tx_mhl

#EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/edid
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/log
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/malloc
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/obj
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/seq
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/time
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/mtx
EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/library/video

EXTRA_CFLAGS += -I$(HDMI_DRV_DIR)/$(HAL_DIR)/platform

####################################################################################################

DRV_OBJS := $(HDMI_VER)/$(HAL_DIR)/driver/common/si_drv_common.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/cpi/si_drv_cpi.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/si_drv_tx.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/tx_hdmi/si_mod_tx_hdmi.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/scdc/si_mod_tx_scdc.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/videopath/si_mod_videopath.o   \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/videopath/si_mod_videopath_cra.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/hdcp/si_mod_tx_hdcp.o   \
            $(HDMI_VER)/$(HAL_DIR)/driver/cra/si_drv_cra.o  \
            $(HDMI_VER)/$(HAL_DIR)/library/log/si_lib_log.o \
            $(HDMI_VER)/$(HAL_DIR)/library/malloc/si_lib_malloc.o \
            $(HDMI_VER)/$(HAL_DIR)/library/obj/si_lib_obj.o \
            $(HDMI_VER)/$(HAL_DIR)/library/seq/si_lib_seq.o \
            $(HDMI_VER)/$(HAL_DIR)/library/time/si_lib_time.o \
            $(HDMI_VER)/$(HAL_DIR)/platform/platform.o \
            $(HDMI_VER)/$(HAL_DIR)/platform/sii_time.o

#DRV_OBJS += $(HDMI_VER)/$(HAL_DIR)/driver/tpg/si_drv_tpg.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/vtg/si_drv_vtg.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/pll/si_drv_pll_vo.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/pll/si_drv_pll_vo_cfg.o \
            $(HDMI_VER)/$(HAL_DIR)/library/video/si_lib_video.o \
            $(HDMI_VER)/$(HAL_DIR)/library/mtx/si_lib_mtx.o

#DRV_OBJS += $(HDMI_VER)/$(HAL_DIR)/driver/pebbles/si_drv_pebbles.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/tx_mhl/si_mod_tx_mhl.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/tx_mhl/emsc/si_mod_tx_cbus_emsc.o \
            $(HDMI_VER)/$(HAL_DIR)/driver/tx/tx_mhl/mdt/si_mod_tx_cbus_mdt.o

DRV_OBJS += $(HDMI_VER)/$(HAL_DIR)/hdmi_hal.o
DRV_OBJS += $(HDMI_VER)/$(HAL_DIR)/hal_cec.o

DRV_OBJS += $(HDMI_VER)/drv_hdmi_infoframe.o \
            $(HDMI_VER)/drv_hdmi_event.o \
            $(HDMI_VER)/drv_hdmi_edid.o \
            $(HDMI_VER)/drv_hdmi_edid_test.o \
            $(HDMI_VER)/drv_hdmi_intf.o \
            $(HDMI_VER)/drv_hdmi_intf_k.o \
			$(HDMI_VER)/drv_hdmi_proc.o \
			$(HDMI_VER)/drv_hdmi_compatibility.o

$(MOD_NAME)-y := $(DRV_OBJS)
endif

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
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

