CSRCS += font_24.c
CSRCS += font_40.c
CSRCS += font_32.c

DEPPATH += --dep-path $(LVGL_DIR)/$(LIKKIM_DIR_NAME)/font
VPATH += :$(LVGL_DIR)/$(LIKKIM_DIR_NAME)/font

CFLAGS += "-I$(LVGL_DIR)/$(LIKKIM_DIR_NAME)/font"
