USPACE_PREFIX = ../..
LIBS = $(LIBGUI_PREFIX)/libgui.a $(LIBDRAW_PREFIX)/libdraw.a \
	$(LIBSOFTREND_PREFIX)/libsoftrend.a $(LIBSOFTFLOAT_PREFIX)/libsoftfloat.a
EXTRA_CFLAGS += -I$(LIBGUI_PREFIX) -I$(LIBDRAW_PREFIX) \
	-I$(LIBSOFTREND_PREFIX)
BINARY = clockt

SOURCES = \
	clockt.c \
	
include $(USPACE_PREFIX)/Makefile.common
	
