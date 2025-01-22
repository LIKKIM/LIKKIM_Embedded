/*********************
 *      INCLUDES
 *********************/
#ifndef __GUI_LANGUAGE_COMM_H__
#define __GUI_LANGUAGE_COMM_H__

#include <string.h>
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>

LV_FONT_DECLARE(font_24)
LV_FONT_DECLARE(font_32)
LV_FONT_DECLARE(font_40)




extern const char* language_table_screen_never_turn_off[];
extern const char* language_table_fee_payer[];
extern const char* language_table_format[];
extern const char* language_table_message_hash[];
extern const char* language_table_wallet_ready[];
extern const char* language_table_warning_reset_device[];
extern const char* language_table_restore_funds[];
extern const char* language_table_cancel[];
extern const char* language_table_erase_this_device[];
extern const char* language_table_enter_pin[];
extern const char* language_table_wrong_pin[];
extern const char* language_table_entered_incorrect[];
extern const char* language_table_close[];
extern const char* language_table_enter_new_pin[];
extern const char* language_table_confirm_pin[];
extern const char* language_table_swipe_to_show_app[];
extern const char* language_table_quick_start[];
extern const char* language_table_create_wallet_or_restore[];
extern const char* language_table_create_wallet[];
extern const char* language_table_import_wallet[];
extern const char* language_table_ready_to_check[];
extern const char* language_table_select_number_of_words[];
extern const char* language_table_words[];
extern const char* language_table_recovery_phrase[];
extern const char* language_table_write_down_following[];
extern const char* language_table_continue[];
extern const char* language_table_almost_done[];
extern const char* language_table_follow_the_guide[];
extern const char* language_table_back[];
extern const char* language_table_verification_phrase[];
extern const char* language_table_verification_word[];
extern const char* language_table_incorrect_word[];
extern const char* language_table_wrong_word_check_again[];
extern const char* language_table_try_again[];
extern const char* language_table_user_guide[];
extern const char* language_table_kikkim_app_tutorial[];
extern const char* language_table_what_is_recovery_phrase[];
extern const char* language_table_recovery_phrase_description[];
extern const char* language_table_welcome_to_likkim[];
extern const char* language_table_recovery_phrase_instruction[];
extern const char* language_table_general[];
extern const char* language_table_guide[];
extern const char* language_table_settings[];
extern const char* language_table_conection_app_wallet[];
extern const char* language_table_minute[];
extern const char* language_table_device_shutdown[];
extern const char* language_table_during_device_locked_screen_off[];
extern const char* language_table_auto_lock[];
extern const char* language_table_never[];
extern const char* language_table_after_10_minutes_screen_off[];
extern const char* language_table_language[];
extern const char* language_table_shutdown[];
extern const char* language_table_homescreen[];
extern const char* language_table_lock_screen[];
extern const char* language_table_home_screen[];
extern const char* language_table_abort_import[];
extern const char* language_table_sure_to_abort_process[];
extern const char* language_table_confirm[];
extern const char* language_table_import_recovery_phrase[];
extern const char* language_table_enter_word[];
extern const char* language_table_successfully_recovered_wallet[];
extern const char* language_table_security[];
extern const char* language_table_about_device[];
extern const char* language_table_power_off[];
extern const char* language_table_change_pin[];
extern const char* language_table_set_pin_protect_wallet[];
extern const char* language_table_enter_old_pin[];
extern const char* language_table_set_new_pin[];
extern const char* language_table_pin_changed[];
extern const char* language_table_successfully_changed_pin[];
extern const char* language_table_done[];
extern const char* language_table_connect_app_wallet[];
extern const char* language_table_bluetooth_pairing[];
extern const char* language_table_change_password[];
extern const char* language_table_reset_device[];
extern const char* language_table_model[];
extern const char* language_table_bluetooth_name[];
extern const char* language_table_system[];
extern const char* language_table_bluetooth[];
extern const char* language_table_bootloader[];
extern const char* language_table_reset_to_factory_default[];
extern const char* language_table_this_will_erase_all_data[];
extern const char* language_table_after_reset_phrase_will_be_deleted[];
extern const char* language_table_slide_to_reset[];
extern const char* language_table_reset_complete[];
extern const char* language_table_device_reset[];
extern const char* language_table_restart[];
extern const char* language_table_address[];
extern const char* language_table_path[];
extern const char* language_table_qr_code[];
extern const char* language_table_view_transaction[];
extern const char* language_table_directions[];
extern const char* language_table_more[];
extern const char* language_table_reject[];
extern const char* language_table_confirm_transaction[];
extern const char* language_table_sign_transaction[];
extern const char* language_table_slide_to_sign[];
extern const char* language_table_processing[];
extern const char* language_table_transaction_successful[];
extern const char* language_table_mul_language[];

extern const char* language_table_add_finger[];
extern const char* language_table_finger[];
extern const char* language_table_add_finger_prompt[];
extern const char* language_table_unlock_device[];
extern const char* language_table_fingerprint[];
extern const char* language_table_get_started[];
extern const char* language_table_place_finger[];
extern const char* language_table_put_finger_power_button[];
extern const char* language_table_lift_and_touch_power_button[];
extern const char* language_table_fingerprint_added[];
extern const char* language_table_remove_fingerprints[];
extern const char* language_table_confirm_remove_fingerprint[];
extern const char* language_table_remove[];
extern const char* language_table_alternative_pin_unlock[];
extern const char* language_table_not_now[];
extern const char* language_table_add_fingerprint[];
extern const char* language_table_invalid_recovery_phrase[];
extern const char* language_table_recovery_phrase_invalid[];
extern const char* language_table_submitted[];

extern const char* language_table_incorrect_password[];
extern const char* language_table_incorrect_password_locked_1_min[];
extern const char* language_table_incorrect_password_locked_5_min[];
extern const char* language_table_incorrect_password_locked_1_hours[];
extern const char* language_table_incorrect_password_locked_2_hours[];
extern const char* language_table_incorrect_password_locked_4_hours[];
extern const char* language_table_incorrect_password_locked_8_hours[];
extern const char* language_table_incorrect_password_2_attempts[];
extern const char* language_table_incorrect_password_1_attempt[];




extern void set_language_string(lv_obj_t* label, uint8_t font_size, const char** str_table);
#endif /* __GUI_LANGUAGE_COMM_H__ */


