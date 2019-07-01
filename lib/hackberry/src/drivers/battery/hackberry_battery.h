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
#include "hackberry_mapping.h"


// resistors of the voltage divider (see hardware schematics : https://easyeda.com/editor#id=e390bae9b279417c9c5e9cd86d05d3c4)
#define R12 162 // kohms
#define R13 100 // kohms

// min and max voltage values of the battery
#define VBAT_MIN    6.2 // Volts
#define VBAT_MAX    7.2 // Volts

// Maximum voltage tolerated by the ADC (for arduino : 5V)
#define V_RANGE   5 // volts

// Maximum ADC range
#define ADC_RANGE (MAX_ADC - MIN_ADC + 1)
#define ADC_CONVERSION (ADC_RANGE / V_RANGE)

// calculated parameters
#define R_FACTOR (R13 / (R12+R13)) // gain of the voltage divider

#define ADC_BAT_MIN ((VBAT_MIN * R_FACTOR) * ADC_CONVERSION)
#define ADC_BAT_MAX ((VBAT_MAX * R_FACTOR) * ADC_CONVERSION)       

// class
class Hackberry_battery{

    public: 
        Hackberry_battery();
        void init(unsigned char pinBattery = UNDEFINED);
        unsigned char read();
        unsigned char readAverage();

    private:
        unsigned char _pinBattery;

        int readRawValue();
        int readRawAverage();
};


#endif