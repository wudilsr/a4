## Makefile.am for DirectFB/inputdrivers/keyboard

INCLUDES = \
	-I$(top_builddir)/include	\
	-I$(top_builddir)/lib	\
	-I$(top_srcdir)/include	\
	-I$(top_srcdir)/lib	\
	-I$(top_srcdir)/src	\
	-I$(top_srcdir)/systems

keyboard_LTLIBRARIES = libdirectfb_keyboard.la

if BUILD_STATIC
keyboard_DATA = $(keyboard_LTLIBRARIES:.la=.o)
endif

keyboarddir = $(MODULEDIR)/inputdrivers

libdirectfb_keyboard_la_SOURCES =	\
	keyboard.c

libdirectfb_keyboard_la_LDFLAGS = \
	-module			\
	-avoid-version		\
	$(DFB_LDFLAGS) -lm -ljpeg -lhi_msp -lhi_common -ldl

libdirectfb_keyboard_la_LIBADD = \
	$(top_builddir)/lib/direct/libdirect.la \
	$(top_builddir)/src/libdirectfb.la


include $(top_srcdir)/rules/libobject.make
	
