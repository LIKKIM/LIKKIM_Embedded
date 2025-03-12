# Set LIKKIM_DIR_NAME to 'likkim' if not set
LIKKIM_DIR_NAME ?= likkim

# Include the src.mk file for compiling code
include $(LVGL_DIR)/$(LIKKIM_DIR_NAME)/src/src.mk

# Include the img.mk file for handling images
include $(LVGL_DIR)/$(LIKKIM_DIR_NAME)/img/img.mk

# Include the font.mk file for handling fonts
include $(LVGL_DIR)/$(LIKKIM_DIR_NAME)/font/font.mk
