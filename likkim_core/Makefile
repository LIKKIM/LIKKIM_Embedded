#
# Makefile
#
# compiler and tools
# ROOTDIR = ~/toolchain/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/
CC = $(ROOTDIR)arm-none-linux-gnueabihf-gcc
AR = $(ROOTDIR)arm-none-linux-gnueabihf-ar
RANLIB = $(ROOTDIR)arm-none-linux-gnueabihf-ranlib

LIKKIM_DIR = likkim_algo
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare
CFLAGS += -I$(LIKKIM_DIR)/Hardware -I$(LIKKIM_DIR)/algo 
CFLAGS += -I$(LIKKIM_DIR)/../library/include/freetype2
CFLAGS += -I$(LIKKIM_DIR)/../library/include/libdrm -I$(LVGL_DIR)/library/include 
LD_DIR = -L$(LIKKIM_DIR) -L$(LIKKIM_DIR)/algo/
LD_DIR += -L$(LIKKIM_DIR)/../library/lib -lfreetype -ldrm
LDFLAGS ?= $(LD_DIR) -lm -lpthread -lusart_program -lwallet_algo -lnetwork
BIN = lvgl_exec


#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/likkim/likkim.mk

CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

# modify target file path, add build prefix
BUILD_DIR = build
AOBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASRCS:.S=$(OBJEXT))))
COBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(CSRCS:.c=$(OBJEXT))))
MAINOBJ = $(addprefix $(BUILD_DIR)/,$(notdir $(MAINSRC:.c=$(OBJEXT))))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

# add vpath to help make find source files
vpath %.c $(sort $(dir $(SRCS)))
vpath %.S $(sort $(dir $(ASRCS)))

## MAINOBJ -> OBJFILES
all:
	@mkdir -p $(BUILD_DIR)
	make -C likkim_algo/ LIKKIM_ALL -j$(nproc)
	make LVGL_ALL -j$(nproc)

LVGL_ALL: $(AOBJS) $(COBJS) $(MAINOBJ)
	$(CC) -o $(BUILD_DIR)/$(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

# change compile rule
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

clean: 
	rm -f $(BUILD_DIR)/$(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)
	rm -rf $(BUILD_DIR)
	make -C likkim_algo/ clean

export CC AR RANLIB
