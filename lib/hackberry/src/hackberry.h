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
#include "drivers/debug/hackberry_debug.h"
#include "drivers/bluetooth/hackberry_bluetooth.h"
#include "drivers/eeprom/hackberry_eeprom.h"
#include "drivers/battery/hackberry_battery.h"


// Mapping of IOs
#include "hackberry_mapping.h"

// class
class Hackberry
{
    public:
        Hackberry();

        // initialization
        void begin(bool selectedHand, int sensorType, bool enableDebug);

        // Hackberry hand components
        Hackberry_buttons   buttons;
        Hackberry_servos    servos;
        Hackberry_sensor    sensor;
        Hackberry_battery   battery;
        Hackberry_bluetooth bluetooth;
        //Hackberry_debug     debug;
        Hackberry_eeprom    eeprom;
        
    private:      
};

#endif
