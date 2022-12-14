LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_ci
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifeq ($(CFG_HI_CI_DEV_CIMAX),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAX
endif
ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAXPLUS
endif
ifeq ($(CFG_HI_CI_DEV_HICI),y)
LOCAL_CFLAGS += -DHI_CI_DEV_HICI
endif

LOCAL_SRC_FILES := sample_ci.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common
include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_ci_dvbplay
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifeq ($(CFG_HI_CI_DEV_CIMAX),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAX
endif
ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAXPLUS
endif
ifeq ($(CFG_HI_CI_DEV_HICI),y)
LOCAL_CFLAGS += -DHI_CI_DEV_HICI
endif

LOCAL_SRC_FILES := sample_ci_dvbplay.c stack/ci_stack.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common


include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_ci_tsplay
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifeq ($(CFG_HI_CI_DEV_CIMAX),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAX
endif
ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
LOCAL_CFLAGS += -DHI_CI_DEV_CIMAXPLUS
endif
ifeq ($(CFG_HI_CI_DEV_HICI),y)
LOCAL_CFLAGS += -DHI_CI_DEV_HICI
endif

LOCAL_SRC_FILES := sample_ci_tsplay.c stack/ci_stack.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common


include $(BUILD_EXECUTABLE)
