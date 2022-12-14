##################### DO NOT EDIT THIS FILE ######################
#trustedcore mk file
#created by h00206996

#add version:100 means version 1.00
TRUSTEDCORE_VERSION = 200
WITH_DEBUG_VERSION = false


#Trustedcore Make Platform:LINUX or ANDROID
TRUSTEDCORE_MAKE_PLATFORM_CHOOSE?=LINUX
ifeq ($(strip $(TRUSTEDCORE_MAKE_PLATFORM_CHOOSE)), LINUX)
TRUSTEDCORE_DIR=$(shell pwd)
else
TRUSTEDCORE_DIR=${SDK_DIR}/source/plugin/tvp/trustedcore
endif
$(info TRUSTEDCORE_DIR: $(TRUSTEDCORE_DIR))

#you can add a new platform in platform_definition.mk
include $(TRUSTEDCORE_DIR)/platform_definition.mk
$(info PLATFORM_DIR_NAME: $(PLATFORM_DIR_NAME))

PLATFORM_DIR=$(TRUSTEDCORE_DIR)/platform/${PLATFORM_DIR_NAME}

#platform config
include $(PLATFORM_DIR)/platform.mk


WITH_MEDIAOS_BRANCH = true
MICRO_TRUSTEDCORE = false
WITH_CC_DRIVER = true
WITH_K3V2PRO_CCTEST = true


# add by l00202565 begin
ifneq ($(filter 4.6 4.6.%, $(TARGET_GCC_VERSION)),)
TRUSTEDCORE_ASFLAG_SET := false
else
TRUSTEDCORE_ASFLAG_SET := true
endif
# when support arch64 use: "TRUSTEDCORE_ARCH_CHOOSE := AARCH64"
TRUSTEDCORE_ARCH_CHOOSE := ARM

TRUSTEDCORE_MK := $(TRUSTEDCORE_DIR)/mk
TRUSTEDCORE_BUILD_RAW_STATIC_LIBRARY = $(TRUSTEDCORE_MK)/trustedcore_static_library_build.mk
TRUSTEDCORE_BUILD_RAW_EXECUTABLE = $(TRUSTEDCORE_MK)/trustedcore_raw_executable_build.mk
TRUSTEDCORE_BUILD_TA_EXECUTABLE = $(TRUSTEDCORE_MK)/task_executable.mk
TRUSTEDCORE_BUILD_EXECUTABLE_IMG = $(TRUSTEDCORE_MK)/trustedcore_img_build.mk
TA_LINK_SCRIPT = $(TRUSTEDCORE_MK)/ta_link.ld
# add by l00202565 end

# add by h00211444
# originally, two CC switch in four makefiles,
# now, both in this file

#selection of SECURE_TESTSUITE: none, RTOSck_UT, RTOSck_IT, RTOSck_PT
SECURE_TESTSUITE = none
#SECURE_TESTSUITE = RTOSck_UT
#SECURE_TESTSUITE = RTOSck_IT


#Makefile Compile Flags
include $(TRUSTEDCORE_DIR)/trustedcore_relase_flags.mk
include $(TRUSTEDCORE_DIR)/trustedcore_flags.mk
include $(PLATFORM_DIR)/platform_flags.mk


###########################################################
# definition for hi_linux
###########################################################
ifeq ($(strip $(TRUSTEDCORE_MAKE_PLATFORM_CHOOSE)), LINUX)
ifeq ($(O),)
OUT = ${TRUSTEDCORE_DIR}/release/out
else
OUT = $(O)
endif

TOOLCHAINS_DIR = $(OUT)/toolchains
TOOLCHAINS_PACKAGE = ${TRUSTEDCORE_DIR}/toolchains/gcc.tar.bz2
CROSS_COMPILE1?=$(TOOLCHAINS_DIR)/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
CROSS_COMPILE2?=$(TOOLCHAINS_DIR)/gcc/linux-x86/arm/arm-linux-androideabi-4.8/bin/arm-linux-androideabi-

MAKE       =make
AR1        =$(CROSS_COMPILE1)ar
CC1        =$(CROSS_COMPILE1)gcc
LD1        =$(CROSS_COMPILE1)ld
OBJCOPY1   =$(CROSS_COMPILE1)objcopy
AR2        =$(CROSS_COMPILE2)ar
CC2        =$(CROSS_COMPILE2)gcc
LD2        =$(CROSS_COMPILE2)ld
OBJCOPY2   =$(CROSS_COMPILE2)objcopy
CFLAGS     =
LDFLAGS    =
RM         =-rm -rf
MKDIR      =-mkdir -p
COPY       =cp
TRUSTEDCORE_RELEASE_DIR=${TRUSTEDCORE_DIR}/release
endif
