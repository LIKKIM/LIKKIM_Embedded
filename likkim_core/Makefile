#
# Makefile
#
# 编译器和工具
# ROOTDIR = ~/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/
CC = $(ROOTDIR)arm-none-linux-gnueabihf-gcc
AR = $(ROOTDIR)arm-none-linux-gnueabihf-ar
RANLIB = $(ROOTDIR)arm-none-linux-gnueabihf-ranlib

LIKKIM_DIR = likkim_algo
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare
CFLAGS += -I$(LIKKIM_DIR)/Hardware -I$(LIKKIM_DIR)/algo 
LD_DIR = -L$(LIKKIM_DIR) -L$(LIKKIM_DIR)/algo/
LDFLAGS ?= $(LD_DIR) -lm -lpthread -lusart_program -lwallet_algo -lnetwork
BIN = lvgl_exec


#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/likkim/likkim.mk

CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES
all:
	make -C likkim_algo/ LIKKIM_ALL
	make LVGL_ALL -j4
	@mkdir -p build
	@mv $(BIN) build
	find . -type f -name "*.o" -not -path "./build/*" -exec mv {} build/ \;

LVGL_ALL: $(AOBJS) $(COBJS) $(MAINOBJ)
	$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "CC $<"

clean: 
	rm -f build/$(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)
	rm -f build/*
	make -C likkim_algo/ clean

export CC AR RANLIB