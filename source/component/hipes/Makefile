#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)

CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(COMPONENT_DIR)/hipes/include

LIBS := libhi_pes

OBJS := src/hi_unf_pes.o

HEADER_FILES := $(COMPONENT_DIR)/hipes/include/hi_unf_pes.h

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS).a
	$(AT)rm -rf $(LIBS).so

install: all
	$(AT)cp -f  $(LIBS).a           $(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  $(LIBS).so          $(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS) : $(OBJS)
	$(AT)$(AR) -rsv $@.a $^
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $@.so $^
endif

