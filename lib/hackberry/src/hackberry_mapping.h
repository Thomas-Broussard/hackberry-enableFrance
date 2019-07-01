/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Mapping of IOs for Hackberry Hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#ifndef __HACKBERRY_MAPPING_H__
#define __HACKBERRY_MAPPING_H__

/* 
* ====================================================================================
*                                  HACKBERRY_BOARD
* ====================================================================================
*/

// -----------------------------------------------
// Select your Hackberry board here (required)
// -----------------------------------------------
#define HACKBERRY_BOARD MK2

// Available boards :
#define MK1     1 // not used now
#define MK2     2
#define MK3     3

/* 
* ====================================================================================
*                                  EXTENSION_BOARD
* ====================================================================================
*/

// -----------------------------------------------
// Select your extension board here (optional)
// -----------------------------------------------
#define EXTENSION_BOARD BLUETOOTH_BOARD

// Available extensions :
#define NO_EXTENSION        0
#define GPIO_BOARD          1
#define LEDS_BOARD          2
#define BLUETOOTH_BOARD     3


/* 
* ====================================================================================
*                                  DEBUG MODE
* ====================================================================================
*/
// DEBUG MODE
#define DEBUG_ENABLED

// debug mode can't be enabled for Mk2 board if bluetooth extension is already active
#if defined(DEBUG_ENABLED) && ( (EXTENSION_BOARD != BLUETOOTH_BOARD) || (HACKBERRY_BOARD != MK2) )
    #define DebugPrint(x) Serial.print(x)
    #define DebugPrintln(x) Serial.println(x)
    #define DebugBegin(x) Serial.begin(x)
#else
    #define DebugPrint(x) 
    #define DebugPrintln(x) 
    #define DebugBegin(x) 
#endif


/* 
* ====================================================================================
*                                  MAPPINGS
* ====================================================================================
*/
#if   HACKBERRY_BOARD == MK1

    // not implemented yet 
    // resources for later : 
    // https://github.com/mission-arm/HACKberry/blob/v0.0/HACKberry-software/HACKberry_v1/HACKBerry_v1/HACKBerry_v1.ino

#elif HACKBERRY_BOARD == MK2

    // Servomotors
    #define PIN_THUMB           9
    #define PIN_INDEX           5
    #define PIN_FINGERS         6

    // Sensor
    #define PIN_SENSOR_1        A1

    // Buttons
    #define PIN_BUTTON_CALIB    A6
    #define PIN_BUTTON_EXTRA    A7
    #define PIN_BUTTON_THUMB    A0
    #define PIN_BUTTON_LOCK     10


#elif HACKBERRY_BOARD == MK3

    // Servomotors
    #define PIN_THUMB           9
    #define PIN_INDEX           5
    #define PIN_FINGERS         6

    #define PIN_MEASURE_INDEX   A0
    #define PIN_MEASURE_FINGERS A1

    // Sensor
    #define PIN_SENSOR_1        A7
    #define PIN_SENSOR_2        A2

    // Buttons
    #define PIN_BUTTON_CALIB    8
    #define PIN_BUTTON_EXTRA    7
    #define PIN_BUTTON_THUMB    2
    #define PIN_BUTTON_LOCK     10


    // Battery
    #define BATTERY_MONITORING_ENABLED
    #define PIN_BATTERY         A6
    
#endif


/* 
* ====================================================================================
*                                  ERROR HANDLER
* ====================================================================================
*/
#ifndef HACKBERRY_BOARD
    #error No Board defined - Please select the Hackberry Board version (example : "#define HACKBERRY_BOARD MK2")
#endif

#if HACKBERRY_BOARD == MK1
    #error MK1 unavailable - Please select a The Mk1 version is not yet implemented. Please choose another version
#endif

#ifndef __AVR_ATmega328P__  // Arduino nano
    #error Wrong chip defined - Please check that your platformio.ini file contains "board = nanoatmega328new" or "board = nanoatmega328"
#endif

#endif