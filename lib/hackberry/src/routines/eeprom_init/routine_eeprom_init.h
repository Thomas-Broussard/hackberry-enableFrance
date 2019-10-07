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

#ifndef __ROUTINE_EEPROM_INIT_H__
#define __ROUTINE_EEPROM_INIT_H__

// dependencies
#include <Arduino.h>
#include "hackberry_mapping.h"
#include "drivers/hackberry_hand.h"


#define LOW_BATTERY_LEVEL 15 // (%) 

// class
class Routine_eeprom_init
{
    public: 
        Routine_eeprom_init();
        void init(Hackberry_hand *hand);

    private:
        Hackberry_hand *hand;

        void initSensor();
        void initHand();
        void initServos(unsigned char member);
   
};

#endif