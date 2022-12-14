# ===========================================================================
ifndef Q
ifeq ("$(origin V)", "command line")
  Q =
else  
  Q = @
endif
endif
#++++++++++
cur_cc   = gcc
cur_cxx  = g++
cur_cflags  := -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -I$(shell pwd)
#cur_cflags := -Wp-MD -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
cur_cxxflags := -O2
cur_dir = $(CURDIR)
#++++++++++
cur_shell := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	else if [ -x /bin/bash ]; then echo /bin/bash; \
	else echo sh; fi ; fi)
	
PREFIX         ?= $(shell pwd)
ifneq ($(O),)
PREFIX          = $(O)/kconfig
endif 
	
# ===========================================================================
PHONY := all clean install uninstall
#all: himconf
all: hiconf himconf #dochecklxdialog
# ===========================================================================
# lxdialog stuff
check-lxdialog  := $(cur_dir)/lxdialog/check-lxdialog.sh

cur_extracflags = $(shell $(cur_shell) $(check-lxdialog) -ccflags)
cur_loadlibs    = $(shell $(cur_shell) $(check-lxdialog) -ldflags $(cur_cc))
cur_extracflags += -DLOCALE
cur_extracflags += $(shell $(cur_shell) $(cur_dir)/check.sh $(cur_cc) $(cur_cflags))

dochecklxdialog:
	$(Q)$(cur_shell) $(check-lxdialog) -check $(cur_cc) $(cur_extracflags) $(cur_loadlibs)

# ===========================================================================
# Shared Makefile for the various kconfig executables:
# conf:	  Used for defconfig, oldconfig and related targets
# mconf:  Used for the menuconfig target
#         Utilizes the lxdialog package
# object files used by all kconfig flavours

lxdialog := lxdialog/checklist.c lxdialog/util.c lxdialog/inputbox.c
lxdialog += lxdialog/textbox.c lxdialog/yesno.c lxdialog/menubox.c

conf-objs     := conf.c  $(PREFIX)/zconf.tab.c
mconf-objs    := mconf.c $(PREFIX)/zconf.tab.c  $(lxdialog)
#kxgettext-objs	:= kxgettext.c $(PREFIX)/zconf.tab.c

prepare:
	$(Q)@test -d $(PREFIX) || mkdir -p $(PREFIX)

himconf: $(mconf-objs)
#	@echo $(CURSES_LOC)
	$(Q)$(cur_cc) -o $(PREFIX)/$@ $^  $(cur_cflags) $(cur_extracflags) $(cur_loadlibs)

hiconf: $(conf-objs)
	$(Q)$(cur_cc) -o $(PREFIX)/$@ $^  $(cur_cflags) $(cur_extracflags) $(cur_loadlibs)

$(PREFIX)/zconf.tab.c: $(PREFIX)/lex.zconf.c $(PREFIX)/zconf.hash.c
	@cat zconf.tab.c_shipped > $(PREFIX)/zconf.tab.c
$(PREFIX)/lex.zconf.c : prepare
	@cat lex.zconf.c_shipped > $(PREFIX)/lex.zconf.c
$(PREFIX)/zconf.hash.c: prepare
	@cat zconf.hash.c_shipped > $(PREFIX)/zconf.hash.c

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ifndef RCS_FIND_IGNORE
RCS_FIND_IGNORE := \( -name SCCS -o -name BitKeeper -o -name .svn -o -name CVS -o -name .pc -o -name .hg -o -name .git \) -prune -o
endif

clean:	
	$(Q)rm -rf $(PREFIX)/hiconf
	$(Q)rm -rf $(PREFIX)/himconf
	$(Q)rm -rf $(PREFIX)/zconf.tab.c $(PREFIX)/lex.zconf.c $(PREFIX)/zconf.hash.c
	@echo $(cur_dir)
	$(Q)find $(PREFIX) $(RCS_FIND_IGNORE) \
		\( -name '*.o'  \
		-o -name '*.cmd' \
		-o -name '.*.cmd' \
		-o -name '.*.o.cmd'\
		 \) -type f -print | xargs rm -f
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
install: all
#	@echo "install over !"
uninstall: 
	rm -rf $(PREFIX)/hiconf
	rm -rf $(PREFIX)/himconf
#	@echo "uninstall over !"
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# ===========================================================================

