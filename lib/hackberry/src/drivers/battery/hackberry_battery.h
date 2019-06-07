/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for monitoring the Hackberry Hand Battery
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_BATTERY_H__
#define __HACKBERRY_BATTERY_H__

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"


// resistors of the voltage divider
#define R12 162 // kohms
#define R13 100 // kohms

// min and max voltage values of the battery
#define VBAT_MIN    6.2 // Volts
#define VBAT_MAX    7.2 // Volts

// Maximum voltage tolerated by the ADC (for arduino : 5V)
#define V_RANGE   5 // volts

// Maximum ADC range (for arduino : 1023)
#define ADC_RANGE (MAX_ADC - MIN_ADC + 1)
#define ADC_CONVERSION (ADC_RANGE / V_RANGE)

// calculated parameters
#define R_FACTOR (R13 / (R12+R13)) // gain of the voltage divider

#define ADC_MIN ((VBAT_MIN * R_FACTOR) * ADC_CONVERSION)
#define ADC_MAX ((VBAT_MAX * R_FACTOR) * ADC_CONVERSION)       

#define GAIN    (ADC_RANGE / (ADC_MAX - ADC_MIN))
#define OFFSET  (- ADC_MIN * GAIN)

#define LEVEL_FACTOR (100 / ADC_RANGE) // 0.0976 = (100/1023)   

// class
class Hackberry_battery{

    public: 
        Hackberry_battery(int pinBattery);
        void init();
        int read();
        int readAverage();

    private:
        int _pinBattery;

        int readRawValue();
        int readRawAverage();
};


#endif