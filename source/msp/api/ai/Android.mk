ifeq ($(CFG_HI_AI_SUPPORT),y)
AI_DIR := ai
LOCAL_CFLAGS += -DHI_AUDIO_AI_SUPPORT
LOCAL_SRC_FILES += $(AI_DIR)/mpi_ai.c
LOCAL_SRC_FILES += $(AI_DIR)/unf_ai.c
endif
