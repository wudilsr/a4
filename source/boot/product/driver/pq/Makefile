#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../..
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

PQ_DIR := $(PRODUCT_DIR)/driver/pq

ifndef CFLAGS
include $(BOOT_DIR)/define.mak
export MKFLAGS

CC := $(CROSS_COMPILE)gcc

gccincdir := $(shell $(CC) -print-file-name=include)

CFLAGS := -g -Os -D__KERNEL__ -D__ARM__ -fno-strict-aliasing -fno-common -ffixed-r8 \
      -nostdinc -isystem $(gccincdir) $(MKFLAGS) -I$(PRODUCT_DIR) \
      -fno-builtin -ffreestanding  -pipe -marm  -mabi=aapcs-linux  \
      -mno-thumb-interwork -march=armv7-a \
      -Wall -Wstrict-prototypes -fno-stack-protector
endif

CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -D__PQ_PLATFORM_BOOT__

ifeq ($(CFG_HI_PQ_V1_0), y)
CFLAGS  += -DHI_PQ_VERSION_V1

else ifeq ($(CFG_HI_PQ_V2_0), y)
CFLAGS  += -DHI_PQ_VERSION_V2
else ifeq ($(CFG_HI_PQ_V3_0), y)
CFLAGS  += -DHI_PQ_VERSION_V3
endif

OBJS    := $(PQ_DIR)/drv_pq.o


LIBS    := $(PQ_DIR)/libpq.a

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)

install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
