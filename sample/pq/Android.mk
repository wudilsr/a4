LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pq
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
LOCAL_SRC_FILES := sample_pq_v1.c
endif
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a hi3716mv410 hi3716mv420),)
LOCAL_SRC_FILES := sample_pq_v2.c
endif

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp

include $(BUILD_EXECUTABLE)
