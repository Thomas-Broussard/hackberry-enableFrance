/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Global variables shared and used in the hackberry project
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_GLOBAL_H__
#define __HACKBERRY_GLOBAL_H__

// Version Number
#define MAJOR_VERSION 1
#define MINOR_VERSION 1
#define PATCH_VERSION 1


// DEBUG MODE
#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
    #define DebugPrint(x) Serial.print(x)
    #define DebugPrintln(x) Serial.println(x)
#else
    #define DebugPrint(x) 
    #define DebugPrintln(x) 
#endif



// Hand Selection
#define RIGHT_HAND true
#define LEFT_HAND false


// LIST OF EXISTING SENSORS
#define TYPE_IR_SENSOR 0
#define TYPE_EMG_SENSOR 1


// Range of the microcontroller's ADC 
#define MIN_ADC 0
#define MAX_ADC 1023

// General 
#define UNDEFINED -1

// ---------------------------------------------------
// Constants for servomotor
// ---------------------------------------------------
#define THUMB   1
#define INDEX   2
#define FINGERS  3

/**
 * List of operating modes for the hackberry hand
 */
enum Hackberry_Mode
{
    Standard,
    SensorCalibration, 
    ServosCalibration
};




#endif