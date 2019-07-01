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

#include "routine_battery.h"

Routine_battery::Routine_battery()
{

}

void Routine_battery::init(Hackberry_hand *hand)
{
    this->hand = hand;
}

void Routine_battery::execute()
{
    int batteryLevel = this->hand->battery.readAverage();

    if (batteryLevel < LOW_BATTERY_LEVEL)
    {
        // TODO : complete here
        this->hand->setMode(Sleep); // If battery is low , put it in sleep mode
    }
}


