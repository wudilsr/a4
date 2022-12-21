LOCAL_PATH := $(call my-dir)

###############################sample_dvbplay#################################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_dvbplay
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := dvbplay.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

include $(BUILD_EXECUTABLE)

###############################sample_dvbplay_ir#################################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_dvbplay_ir
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := dvbplay_ir.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common \
                          libhi_msp libhi_sample_common

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

include $(BUILD_EXECUTABLE)


###############################sample_dvbplay_pid#################################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_dvbplay_pid
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := dvbplay_pid.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common \
                          libhi_msp libhi_sample_common

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

include $(BUILD_EXECUTABLE)