#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common

ifeq ($(CFG_HI_TEE_SUPPORT), y)
CFLAGS += -DHI_TEE_SUPPORT
CFLAGS += -I$(HI_TEE_OS_DIR)/libteec/inc/
CFLAGS += -I$(COMMON_DIR)/api/mmz
HI_LIBS += -lteec
endif

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR) 
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP = sample_rawplay
OBJS = rawplay.o $(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
