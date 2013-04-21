USPACE_PREFIX = ../..
LIBS = $(LIBGUI_PREFIX)/libgui.a $(LIBDRAW_PREFIX)/libdraw.a \
	$(LIBSOFTREND_PREFIX)/libsoftrend.a $(LIBSOFTFLOAT_PREFIX)/libsoftfloat.a
EXTRA_CFLAGS += -I$(LIBGUI_PREFIX) -I$(LIBDRAW_PREFIX) \
	-I$(LIBSOFTREND_PREFIX)
BINARY = vlaunch

SOURCES = \
	vlaunch.c \
	images.c

IMAGES = \
	gfx/w2.tga

PRE_DEPEND = images.c images.h
EXTRA_CLEAN = images.c images.h

include $(USPACE_PREFIX)/Makefile.common
images.c images.h: $(IMAGES)
	$(ROOT_PATH)/tools/mkarray.py images COMPOSITOR_IMAGES $^
