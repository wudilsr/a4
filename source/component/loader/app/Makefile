ifeq ($(CFG_HI_EXPORT_FLAG),)

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
SDK_DIR := $(shell pwd)/../../../../..
else
SDK_DIR := $(shell pwd)/../../../..
endif

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================

ifndef CFLAGS

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
export MKFLAGS

CC := $(CROSS_COMPILE)gcc

gccincdir := $(shell $(CC) -print-file-name=include)

CFLAGS := -g -Os -D__ARM__ -fno-strict-aliasing -fno-common -ffixed-r8 \
          -nostdinc -isystem $(gccincdir) $(MKFLAGS) -I$(PRODUCT_DIR) \
          -fno-builtin -ffreestanding  -pipe -marm  -mabi=aapcs-linux  \
          -mno-thumb-interwork -march=armv7-a \
          -Wall -Wstrict-prototypes -fno-stack-protector
endif
endif

CFLAGS += -I$(CURDIR)/include
CFLAGS += -I$(CURDIR)/common
CFLAGS += -I$(COMMON_UNF_INCLUDE)
CFLAGS += -I$(COMPONENT_DIR)/loader/api/include
CFLAGS += -I$(COMPONENT_DIR)/loader/app/ca/

CFLAGS += ${CFG_HI_BOARD_CONFIGS}

LOADER_SRC += main.c download.c protocol.c upgrd_common.c upgrd_config.c upgrd_osd.c burn.c burn_raw.c burn_ext4sp.c

ifeq ($(CFG_HI_ADVCA_SUPPORT)_$(CFG_HI_LOADER_BOOTLOADER),y_)
LOADER_SRC += burn_ca.c
CFLAGS += -I$(MSP_DIR)/drv/include
CFLAGS += -DHI_ADVCA_SUPPORT
CFLAGS += -DHI_ADVCA_TYPE_$(CFG_HI_ADVCA_TYPE)
ifdef CFG_HI_ADVCA_FUNCTION
    ifeq ($(CFG_HI_ADVCA_FUNCTION),FINAL)
        CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
    else
        CFLAGS += -DHI_ADVCA_FUNCTION_$(CFG_HI_ADVCA_FUNCTION)
    endif
endif
endif

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
CFLAGS += -DHI_LOADER_BOOTLOADER
endif

ifeq ($(CFG_HI_LOADER_APPLOADER),y)
CFLAGS += -DHI_LOADER_APPLOADER -DHI_BUILD_WITH_IR
endif

ifeq (y,$(CFG_HI_LOG_SUPPORT))
CFLAGS += -DHI_LOG_SUPPORT=1
ifdef CFG_HI_LOG_LEVEL
CFLAGS += -DHI_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
else
CFLAGS += -DHI_LOG_LEVEL=1
endif
else
CFLAGS += -DHI_LOG_SUPPORT=0
endif

ifeq ($(CFG_HI_APPLOADER_OSD_LANG_CN),y)
CFLAGS += -DHI_APPLOADER_OSD_LANG_CN
endif

ifneq ($(CFG_HI_APPLOADER_TUNER_INDEX), )
CFLAGS += -DHI_LOADER_TUNER_INDEX=$(CFG_HI_APPLOADER_TUNER_INDEX)
endif

ifneq ($(CFG_HI_BOOTLOADER_TUNER_INDEX), )
CFLAGS += -DHI_LOADER_TUNER_INDEX=$(CFG_HI_BOOTLOADER_TUNER_INDEX)
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLAGS += -DHI_BUILD_WITH_KEYLED
    ifeq ($(CFG_HI_KEYLED_PT6964_SELECT),y)
    CFLAGS += -DHI_KEYLED_PT6964
    endif
    ifeq ($(CFG_HI_KEYLED_PT6961_SELECT),y)
    CFLAGS += -DHI_KEYLED_PT6961
    endif
    ifeq ($(CFG_HI_KEYLED_CT1642_SELECT),y)
    CFLAGS += -DHI_KEYLED_CT1642
    endif
    ifeq ($(CFG_HI_KEYLED_74HC164_SELECT),y)
    CFLAGS += -DHI_KEYLED_74HC164
    endif
    ifeq ($(CFG_HI_KEYLED_FD650_SELECT),y)
    CFLAGS += -DHI_KEYLED_FD650
    endif
endif

ifneq ($(CFG_HI_APPLOADER_MODE_IP)_$(CFG_HI_BOOTLOADER_MODE_IP),_)
CFLAGS += -DHI_LOADER_MODE_IP
LOADER_SRC += download_ip.c
endif

ifneq ($(CFG_HI_APPLOADER_MODE_OTA)_$(CFG_HI_BOOTLOADER_MODE_OTA),_)
CFLAGS += -DHI_LOADER_MODE_OTA
LOADER_SRC += download_ota.c ota_datamanager.c ota_force.c

ifneq ($(CFG_HI_APPLOADER_TUNER_CAB)_$(CFG_HI_BOOTLOADER_TUNER_CAB),_)
CFLAGS += -DHI_LOADER_TUNER_CAB
endif

ifneq ($(CFG_HI_APPLOADER_TUNER_SAT)_$(CFG_HI_BOOTLOADER_TUNER_SAT),_)
CFLAGS += -DHI_LOADER_TUNER_SAT
ifeq ($(CFG_HI_DISEQC_SUPPORT),y)
CFLAGS += -DDISEQC_SUPPORT
endif
endif

ifneq ($(CFG_HI_APPLOADER_TUNER_TER)_$(CFG_HI_BOOTLOADER_TUNER_TER),_)
CFLAGS += -DHI_LOADER_TUNER_TER
endif

endif

ifneq ($(CFG_HI_APPLOADER_MODE_USB)_$(CFG_HI_BOOTLOADER_MODE_USB),_)
CFLAGS += -DHI_LOADER_MODE_USB
LOADER_SRC += download_usb.c
endif

ifneq ($(CFG_HI_APPLOADER_MODE_FS)_$(CFG_HI_BOOTLOADER_MODE_FS),_)
CFLAGS += -DHI_LOADER_MODE_FS
LOADER_SRC += download_fs.c
endif

ifneq ($(CFG_HI_APPLOADER_PROTOCOL_SSU_OTA)_$(CFG_HI_BOOTLOADER_PROTOCOL_SSU_OTA),_)
CFLAGS += -DHI_LOADER_PROTOCOL_SSU_OTA
LOADER_SRC += protocol_ssu_ota.c
endif

ifneq ($(CFG_HI_APPLOADER_PROTOCOL_HISI_OTA)_$(CFG_HI_BOOTLOADER_PROTOCOL_HISI_OTA),_)
CFLAGS += -DHI_LOADER_PROTOCOL_HISI_OTA
LOADER_SRC += protocol_hisi_ota.c
ifeq ($(CFG_HI_ADVCA_SUPPORT)_$(CFG_HI_LOADER_BOOTLOADER),y_)
LOADER_SRC += protocol_hisi_ota_ca.c
endif
endif

ifneq ($(CFG_HI_APPLOADER_FS_PROTOCOL_HISI_FILE)_$(CFG_HI_APPLOADER_IP_PROTOCOL_HISI_FILE)_$(CFG_HI_APPLOADER_USB_PROTOCOL_HISI_FILE)_$(CFG_HI_BOOTLOADER_USB_PROTOCOL_HISI_FILE),___)
CFLAGS += -DHI_LOADER_PROTOCOL_HISI_FILE
LOADER_SRC += protocol_hisi_file.c
ifeq ($(CFG_HI_ADVCA_SUPPORT)_$(CFG_HI_LOADER_BOOTLOADER),y_)
LOADER_SRC += protocol_hisi_file_ca.c
endif
endif

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
LOADER_SRC += upgrd_text.c
endif
               
#####LOADER_OBJS for bootloader*********LOADER_SRC for bootloader and apploader#####
LOADER_OBJS := $(patsubst %.c,%.o,$(LOADER_SRC))

LOADER_SRC += ../api/src/hi_loader_info.c ../api/src/loaderdb_info.c
####################################################################################
ifeq ($(CFG_ADVCA_TYPE)_$(CFG_HI_LOADER_BOOTLOADER), NAGRA_)
CFLAGS += -I$(SDK_DIR)/source/component/advca/nagra/include
endif

CFLAGS += -g -rdynamic -O2

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
LOADER_OBJS += hi_loader_info.o loaderdb_info.o
include BootLoader.mak
endif

ifeq ($(CFG_HI_LOADER_APPLOADER),y)
include AppLoader.mak
endif
