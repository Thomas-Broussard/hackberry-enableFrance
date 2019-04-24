/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library to simplify the use of the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_H__
#define __HACKBERRY_H__

// dependencies
#include <Arduino.h>

// drivers
#include "drivers/buttons/hackberry_buttons.h"
#include "drivers/servos/hackberry_servos.h"
#include "drivers/sensor/hackberry_sensor.h"
//#include "drivers/debug/hackberry_debug.h"

// class
class Hackberry
{
    public:
        Hackberry();

        // initialization
        void begin(bool selectedHand);
        void begin(bool selectedHand, int sensorType);

        // Hackberry hand components
        Hackberry_buttons buttons;
        Hackberry_servos  servos;
        Hackberry_sensor  sensor;

        //Hackberry_eeprom  eeprom;
        //Hackberry_debug   debug;
        //Hackberry_calibration calibration;
        
    private:      
};

#endif
