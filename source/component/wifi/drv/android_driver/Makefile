KERNEL_OUT := $(ANDROID_PRODUCT_OUT)/obj/KERNEL_OBJ
MODULE_OUT := $(shell pwd)
CROSS_COMPILE ?= arm-hisiv200-linux-
EXTRA_CFLAGS := ROOTFS_DIR=$(ANDROID_BUILD_TOP)/$(PRODUCT_OUT) \
		LINUX_DIR=$(KERNEL_OUT) \
		CFG_HI_KERNEL_VERSION=linux-3.10.y ANDROID_BUILD=y \
		CFG_HI_WIFI_MODE_STA=y CFG_HI_WIFI_MODE_AP=y

TARGET+=CFG80211

all:$(TARGET)

CFG80211:
	make ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) $(EXTRA_CFLAGS) \
		-C $(shell pwd)/../cfg80211 install
	@make -C $(shell pwd)/../cfg80211 clean

clean:

