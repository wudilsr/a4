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
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

ifeq ($(CFG_HI_VI_BT656_HIGH8),y)
EXTRA_CFLAGS += -DCFG_HI_VI_BT656_HIGH8
endif

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/vi                     \
                -I$(MSP_DIR)/drv/vi                     \
                -I$(MSP_DIR)/drv/vi/vicap

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_vi

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  hal_vi.o          \
                    drv_vi_intf.o     \
                    drv_vi_proc.o     \
                    drv_vi.o          \
                    drv_vi_buf.o      \
                    drv_vi_utils.o

ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
$(MOD_NAME)-y +=    ./hi_phy_vicap.o            \
                    ./vicap/drv_vicap.o         \
                    ./vicap/drv_vicap_buf.o     \
                    ./vicap/hal_vicap.o         \
                    ./vicap/drv_uf.o            \
                    ./vicap/drv_vicap_proc.o

EXTRA_CFLAGS += -DHI_HDMI_RX_SUPPORT
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
