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


// Servomotors
#define PIN_THUMB           9
#define PIN_INDEX           5
#define PIN_FINGERS         6

// Sensor
#define PIN_SENSOR_1        A7
#define PIN_SENSOR_2        A2

// Buttons
#define PIN_BUTTON_CALIB    A0
#define PIN_BUTTON_EXTRA    A1
#define PIN_BUTTON_THUMB    2
#define PIN_BUTTON_LOCK     10

// Battery
#define PIN_BATTERY         A6


// Bluetooth / Communication
#define PIN_RX              0
#define PIN_TX              1
#define PIN_POWER           A3



#endif