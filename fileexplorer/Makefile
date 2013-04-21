USPACE_PREFIX = ../..
LIBS = $(LIBGUI_PREFIX)/libgui.a $(LIBDRAW_PREFIX)/libdraw.a \
	$(LIBSOFTREND_PREFIX)/libsoftrend.a $(LIBSOFTFLOAT_PREFIX)/libsoftfloat.a
EXTRA_CFLAGS += -I$(LIBGUI_PREFIX) -I$(LIBDRAW_PREFIX) \
	-I$(LIBSOFTREND_PREFIX)
BINARY = fileexplorer

SOURCES = \
	file.c

include $(USPACE_PREFIX)/Makefile.common
