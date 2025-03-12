/*********************
 *      INCLUDES
 *********************/
#ifndef __GENERAL_MAIN_H__  // Prevent multiple inclusions of this header file
#define __GENERAL_MAIN_H__

#include "lvgl/lvgl.h"  // Include the LittlevGL graphics library header for GUI elements

// Define a structure for managing UI elements within the general main module
typedef struct
{
    lv_obj_t* bg_cont;          // Pointer to the background container object
    lv_obj_t* label_describe1;  // Pointer to the first descriptive label object
    lv_obj_t* label_describe2;  // Pointer to the second descriptive label object
    uint8_t page_id;            // Identifier for the page, to differentiate between UI screens
} general_main_t;

// Declare functions for starting and stopping the general main module
extern void general_main_start(void);  // Function to initialize the module
extern void general_main_stop(void);   // Function to clean up the module when no longer needed

#endif /* __GENERAL_MAIN_H__ */  // End of the preprocessor conditional
