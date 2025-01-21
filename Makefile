# Makefile
#
# Compiler and Tools
# ROOTDIR = ~/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/
CC = $(ROOTDIR)arm-none-linux-gnueabihf-gcc
AR = $(ROOTDIR)arm-none-linux-gnueabihf-ar
RANLIB = $(ROOTDIR)arm-none-linux-gnueabihf-ranlib

LIKKIM_DIR = LIKKIM
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
OBJDIR = build/obj

CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare
CFLAGS += -I$(LIKKIM_DIR)/Hardware -I$(LIKKIM_DIR)/algo 
LD_DIR = -L$(LIKKIM_DIR) -L$(LIKKIM_DIR)/algo/
LDFLAGS ?= $(LD_DIR) -lm -lpthread -lusart_program -lwallet_algo -lnetwork
BIN = build/lvgl_exec


# Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/likkim/likkim.mk

CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

AOBJS = $(patsubst %.S,$(OBJDIR)/%.o,$(ASRCS))
COBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(CSRCS))
MAINOBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(MAINSRC))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES
all:
	make -C LIKKIM/ LIKKIM_ALL
	make LVGL_ALL -j4

LVGL_ALL: $(OBJS) $(MAINOBJ)
	@mkdir -p build
	$(CC) -o $(BIN) $(MAINOBJ) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

clean: 
	rm -rf build $(OBJDIR)
	make -C LIKKIM/ clean

export CC AR RANLIB
