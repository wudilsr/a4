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
ifeq ($(CFG_HI_CHIP_TYPE),hi3716mv310)
CFLAGS += -D__HI3716MV310__
endif

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

image :=    sample_ca_lpk                   \
            sample_ca_tsplay                \
            sample_ca_setjtag               \
            sample_ca_opensecboot           \
            sample_ca_setmarketid           \
            sample_ca_getchipid             \
            sample_ca_crypto                \
            sample_ca_lockhardcw            \
            sample_ca_blpk                  \
            sample_ca_writeRSAkey           \
            sample_ca_setSTBSN              \
            sample_ca_swpk_keyladder        \
            sample_ca_aes_cbc_mac           \
            sample_ca_isMarketIdSet         \
            sample_ca_dcas_tsplay           \
            sample_ca_get_otp_fuse          \
            sample_ca_set_otp_fuse          \
            sample_ca_novel_crypto          \
            sample_ca_conax_tsplay          \
            sample_ca_suma_tsplay           \
            sample_ca_cti_tsplay            \
            sample_ca_csa3_sp_tsplay	    \
            sample_ca_dcas_tsplay           \
            sample_ca_novel_tsplay          \
	    sample_ca_gettrustzonestatus    \
	    sample_ca_enabletrustzone

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
image +=    sample_ca_dvbplay               \
            sample_ca_dcas_dvbplay          \
            sample_ca_dvbplay_misc          \
            sample_ca_dvbplay_sp            \
            sample_ca_novel_dvbplay
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
image +=    sample_ca_pvr_rec               \
            sample_ca_pvr_play              \
            sample_ca_pvr_timeshift
endif
endif

COMMON_FILES := ../common/hi_adp_demux.o    \
                ../common/hi_psi_si.o       \
                ../common/hi_adp_data.o     \
                ../common/hi_adp_hdmi.o     \
                ../common/hi_adp_mpi.o      \
                ../common/hi_adp_search.o   \
                ../common/hi_filter.o       \
                ../common/search.o

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
COMMON_FILES += ../common/hi_adp_tuner.o
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean
all: $(image)

sample_ca_lpk: sample_ca_lpk.c $(COMMON_FILES)
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_tsplay: sample_ca_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_suma_tsplay: sample_ca_suma_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_cti_tsplay: sample_ca_cti_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_csa3_sp_tsplay: sample_ca_csa3_sp_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_conax_tsplay: sample_ca_conax_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_novel_tsplay: sample_ca_novel_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_setjtag: sample_ca_setjtag.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_opensecboot: sample_ca_opensecboot.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_setmarketid: sample_ca_setMarketID.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_getchipid: sample_ca_getchipid.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_crypto: sample_ca_crypto.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_novel_crypto: sample_ca_novel_crypto.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_dvbplay: sample_ca_dvbplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_novel_dvbplay: sample_ca_novel_dvbplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_lockhardcw: sample_ca_lockhardcw.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_blpk:sample_ca_blpk.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_writeRSAkey: sample_ca_writeRSAkey.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_pvr_rec: sample_ca_pvr_rec.c ${COMMON_FILES} ./sample_ca_adp_pvr.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_pvr_play: sample_ca_pvr_play.c ${COMMON_FILES} ./sample_ca_adp_pvr.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_pvr_timeshift: sample_ca_pvr_timeshift.c ${COMMON_FILES} ./sample_ca_adp_pvr.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_setSTBSN: sample_ca_setSTBSN.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS)  $(LIBPATH) $(LIB)

sample_ca_swpk_keyladder: sample_ca_swpk_keyladder.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_aes_cbc_mac: sample_ca_aes_cbc_mac.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_isMarketIdSet: sample_ca_isMarketIdSet.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_product_crypto: sample_product_crypto.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_product_encrypt_boot: sample_product_encrypt_boot.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_product_burn_partition: sample_product_burn_partition.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_product_pv_stb: sample_product_pv_stb.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_dcas_dvbplay: sample_ca_dcas_dvbplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_dcas_tsplay: sample_ca_dcas_tsplay.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_get_otp_fuse: sample_ca_get_otp_fuse.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_set_otp_fuse: sample_ca_set_otp_fuse.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_dvbplay_misc: sample_ca_dvbplay_misc.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

sample_ca_dvbplay_sp: sample_ca_dvbplay_sp.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)
	
sample_ca_irdeto_msr2.2: sample_ca_irdeto_msr2.2.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)	
	
sample_ca_gettrustzonestatus: sample_ca_gettrustzonestatus.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)
	
sample_ca_enabletrustzone: sample_ca_enabletrustzone.c ${COMMON_FILES}
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

clean:
	-@rm -f $(image)

