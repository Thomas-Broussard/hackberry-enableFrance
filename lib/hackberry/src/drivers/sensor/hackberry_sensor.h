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

// class
class Hackberry_sensor{

    public: 
        Hackberry_sensor();
        void init(bool selectedHand, int sensorType);

        // reading sensor output
        int read();
        int readAverage();

    private:

        // Wiring pins
        int _pinSensor;

        // Type of sensor used
        int _sensorType;
};


#endif