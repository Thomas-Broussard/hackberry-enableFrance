/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Manages the movements of the servomotors according to the muscular activity detected by the sensor
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __ROUTINE_BATTERY_H__
#define __ROUTINE_BATTERY_H__

// dependencies
#include <Arduino.h>
#include "hackberry_mapping.h"
#include "drivers/hackberry_hand.h"


#define LOW_BATTERY_LEVEL 15 // (%) 

// class
class Routine_battery
{
    public: 
        Routine_battery();
        void init(Hackberry_hand *hand);
        void execute();

    private:
        Hackberry_hand *hand;
};

#endif