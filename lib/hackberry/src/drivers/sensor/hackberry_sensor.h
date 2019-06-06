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
#include "hackberry_global.h"
#include "sensor_interface.h"


// ---------------------------------------------------
// Constants for sensor
// ---------------------------------------------------



// class
class Hackberry_sensor{

    public: 
        Hackberry_sensor(int pin);
        Hackberry_sensor(int pin1, int pin2);
        Hackberry_sensor(int pin1, int pin2, int pin3);

        void init(int sensorType);

        // reading sensor output
        int read();
        int readAverage();
        void calibrate(int sensorMin, int sensorMax);

        void setSensorType(int sensorType);

    private:
        ISensor *_sensor;
        int _sensorType;

        int _sensorMin = 0;
        int _sensorMax = 1024;

        int pin1;
        int pin2;
        int pin3;
};


#endif