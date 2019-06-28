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

// Select the mapping that you want to use (default : Mk2)
#define MAPPING_MK2
//#define MAPPING_MK3


// Select the extension card that you want to use (default : none)
//#define EXTENSION_BLUETOOTH
//#define EXTENSION_LEDS
//#define EXTENSION_FORCE_CONTROL

/* 
* ====================================================================================
*                                  MAPPINGS
* ====================================================================================
*/
#ifdef MAPPING_MK2
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
#endif


#ifdef MAPPING_MK3
    
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
*                                  EXTENSION BOARDS
* ====================================================================================
*/
#ifdef EXTENSION_BLUETOOTH
    #define PIN_RX_BT           3
    #define PIN_TX_BT           4
    #define PIN_POWER_BT        A3
#endif



/* 
* ====================================================================================
*                                  ERROR HANDLER
* ====================================================================================
*/
#if !defined (MAPPING_MK2) && !defined (MAPPING_MK3)
    #error "Please, select a mapping in hackberry_mapping.h"
#endif

#if defined (MAPPING_MK2) && defined (MAPPING_MK3)
    #error "Please, select only one mapping in hackberry_mapping.h"
#endif

#endif