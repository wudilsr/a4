################################################################################
#    ./dosfstools/Makefile
#    Create By CaiZhiYong 
#    2011.09.05
################################################################################

PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE  ?= arm-hisiv200-linux-

################################################################################

BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
STRIP          := $(CROSS_COMPILE)strip
ifeq (${CROSS_COMPILE},arm-histbv300-linux-)
PPPSRC         := ppp-2.4.7
endif
ifeq (${CROSS_COMPILE},arm-histbv310-linux-)
PPPSRC         := ppp-2.4.7
endif
ifeq (${CROSS_COMPILE},arm-hisiv200-linux-)
PPPSRC         := ppp-2.4.5
endif
TARGETS        := usr/local/sbin/chat usr/local/sbin/pppd \
		  usr/local/sbin/pppstats usr/local/sbin/pppdump \
		  usr/local/sbin/pppoe-discovery
################################################################################

#STATIC         ?= "-static"
################################################################################

install: all
	@cd $(BUILD_DIR)/$(PPPSRC) && \
		make CC=$(CROSS_COMPILE)gcc INSTROOT=$(PREFIX) install && \
	cd -

all: $(addprefix $(BUILD_DIR)/,$(TARGETS))

$(addprefix $(BUILD_DIR)/,$(TARGETS)): \
    $(BUILD_DIR)/$(PPPSRC)/tar
	@cd $(BUILD_DIR)/$(PPPSRC) && \
		./configure && \
		make CC=$(CROSS_COMPILE)gcc INSTROOT=$(PREFIX) \
		STATIC=$(STATIC) all && \
	cd -

$(BUILD_DIR)/%/tar:
	test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################
uninstall:
	@echo "not support"

clean:
	@test ! -d $(BUILD_DIR) || rm -rf $(BUILD_DIR)
	@(for ix in $(TARGETS); do \
		test ! -e $(PREFIX)/$$ix || rm -rf $(PREFIX)/$$ix; \
	done)
	@test ! -d $(PREFIX)/usr/local/lib/pppd || \
		rm -rf $(PREFIX)/usr/local/lib/pppd
	@test ! -d $(PREFIX)/usr/local/include/pppd || \
		rm -rf $(PREFIX)/usr/local/include/pppd
	@test ! -d $(PREFIX)/usr/local/share/man/man8 || \
		rm -rf $(PREFIX)/usr/local/share/man/man8
menuconfig:
	@echo "not support"

distclean: clean

################################################################################
.PHONY: clean menuconfig distclean install all
################################################################################
