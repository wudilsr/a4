LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := tntfs_hisilicon.ko
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/modules
LOCAL_SRC_FILES := $(HISI_LINUX_KERNEL)/$(if $(findstring _dbg_, $(CFG_HI_KERNEL_CFG)),tntfs.ko,tntfs_$(CFG_HI_KERNEL_CFG).ko)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := ntfsck
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)/
LOCAL_SRC_FILES := tools/ntfsck
include $(BUILD_PREBUILT)
