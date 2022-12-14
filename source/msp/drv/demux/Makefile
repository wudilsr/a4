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
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a hi3798cv200 hi3716mv410 hi3716mv420),)
DEMUX_DRV_VER = demux_v1
else
DEMUX_DRV_VER = demux_v2
endif

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/demux/$(DEMUX_DRV_VER)         \
                -I$(MSP_DIR)/drv/demux/$(DEMUX_DRV_VER)         \
                -I$(MSP_DIR)/drv/demux/$(DEMUX_DRV_VER)/descrambler      \
                -I$(COMPONENT_DIR)/ha_codec/include

EXTRA_CFLAGS += -DCFG_HI_DEMUX_POOLBUF_SIZE=$(CFG_HI_DEMUX_POOLBUF_SIZE)

EXTRA_CFLAGS += -DHI_DEMUX_PROC_SUPPORT

EXTRA_CFLAGS += -DDMX_DESCRAMBLER_SUPPORT

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_demux

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  $(DEMUX_DRV_VER)/drv_demux_intf.o        \
                    $(DEMUX_DRV_VER)/drv_demux.o             \
                    $(DEMUX_DRV_VER)/drv_demux_func.o        \
                    $(DEMUX_DRV_VER)/hal_demux.o             \
                    $(DEMUX_DRV_VER)/drv_demux_osal.o        \
                    $(DEMUX_DRV_VER)/drv_demux_scd.o         \
                    $(DEMUX_DRV_VER)/drv_demux_bitstream.o   \
                    $(DEMUX_DRV_VER)/drv_demux_index.o       \
                    $(DEMUX_DRV_VER)/drv_demux_sw.o

$(MOD_NAME)-y   +=  $(DEMUX_DRV_VER)/descrambler/drv_descrambler.o       \
                    $(DEMUX_DRV_VER)/descrambler/drv_descrambler_func.o  \
                    $(DEMUX_DRV_VER)/descrambler/hal_descrambler.o

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

