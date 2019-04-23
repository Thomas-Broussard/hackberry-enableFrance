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

// Hand Selection
#define RIGHT_HAND true
#define LEFT_HAND false

// class
class Hackberry
{
    public:
        Hackberry();

        // initialisation
        void begin(bool selectedHand);

        // Hackberry hand components
        Hackberry_buttons buttons;
        Hackberry_servos fingers;
        Hackberry_sensor sensor;
        Hackberry_eeprom eeprom;
        Hackberry_debug debug;
        // Hackberry_calibration calibration;
        
    private:      
};

#endif
