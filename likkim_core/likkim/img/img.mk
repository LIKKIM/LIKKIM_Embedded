﻿CSRCS += img_add.c
CSRCS += img_alert.c 
CSRCS += img_back.c
CSRCS += img_bg1.c
CSRCS += img_bg2.c
CSRCS += img_bg3.c
CSRCS += img_bg4.c
CSRCS += img_bg5.c
CSRCS += img_bg6.c    
CSRCS += img_bg7.c
CSRCS += img_ble_connect.c 
CSRCS += img_ble_unconnect.c
CSRCS += img_chosen.c 
CSRCS += img_error.c
CSRCS += img_fingerprint.c
CSRCS += img_fingerprint_1.c
CSRCS += img_fingerprint_2.c
CSRCS += img_fingerprint_3.c
CSRCS += img_fingerprint_4.c
CSRCS += img_fingerprint_5.c
CSRCS += img_fingerprint_6.c
CSRCS += img_fingerprint_add_tip.c
CSRCS += img_keypad_ok.c
CSRCS += img_keypad_delete.c
CSRCS += img_keypad2_delete.c
CSRCS += img_likkim.c
CSRCS += img_loading.c
CSRCS += img_menu_general.c
CSRCS += img_menu_guide.c
CSRCS += img_menu_settings.c
CSRCS += img_power_10.c
CSRCS += img_power_25.c
CSRCS += img_power_50.c
CSRCS += img_power_75.c
CSRCS += img_power_100.c
CSRCS += img_power_charge.c
CSRCS += img_power_on.c
CSRCS += img_screen_shoosen.c
CSRCS += img_slider_knob_1.c
CSRCS += img_slider_knob_2.c
CSRCS += img_slider_knob_3.c
CSRCS += img_slider_knob_4.c
CSRCS += img_small_bg1.c
CSRCS += img_small_bg2.c
CSRCS += img_small_bg3.c
CSRCS += img_small_bg4.c
CSRCS += img_small_bg5.c
CSRCS += img_small_bg6.c
CSRCS += img_small_bg7.c
CSRCS += img_startup_arrow.c
CSRCS += img_success.c
CSRCS += img_unchosen.c


DEPPATH += --dep-path $(LVGL_DIR)/$(LIKKIM_DIR_NAME)/img
VPATH += :$(LVGL_DIR)/$(LIKKIM_DIR_NAME)/img

CFLAGS += "-I$(LVGL_DIR)/$(LIKKIM_DIR_NAME)/img"
