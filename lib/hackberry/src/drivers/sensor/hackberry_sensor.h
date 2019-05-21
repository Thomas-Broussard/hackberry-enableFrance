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

// class
class Hackberry_sensor{

    public: 
        Hackberry_sensor();
        void init(bool selectedHand, int sensorType);

        // reading sensor output
        int read();
        int readAverage();
        void calibrate();

        void setSensorType(int sensorType);

    private:
        ISensor *_sensor;
        int _sensorType;
};


#endif