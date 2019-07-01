/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for reading the Hackberry Hand Sensor
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_SENSOR_H__
#define __HACKBERRY_SENSOR_H__

// dependencies
#include <Arduino.h>
#include "hackberry_mapping.h"
#include "sensor_interface.h"


// ---------------------------------------------------
// Constants for sensor
// ---------------------------------------------------
#define DEFAULT_SENSOR TYPE_IR_SENSOR


// class
class Hackberry_sensor{

    public: 
        Hackberry_sensor();
        void init(unsigned char pin1 = UNDEFINED, unsigned char pin2 = UNDEFINED, unsigned char pin3 = UNDEFINED);

        // reading sensor output
        int read();
        int readAverage();

        int readRaw();
        int readRawAverage();

        void calibrate(int sensorMin, int sensorMax);

        void setSensorType(unsigned char sensorType);

    private:
        ISensor *_sensor;
        unsigned char _sensorType;

        int _sensorMin = MIN_ADC;
        int _sensorMax = MAX_ADC;

        unsigned char pin1;
        unsigned char pin2;
        unsigned char pin3;
};


#endif