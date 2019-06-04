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

#include "routine_moves.h"

Routine_moves::Routine_moves()
{

}

void Routine_moves::init(Hackberry_hand hand)
{
    this->hand = &hand;
}

void Routine_moves::execute()
{
    int step = 5;
    int sensorValue = this->hand->sensor.readAverage();

    if (sensorValue > 512)
    {
        this->hand->servos.relativeMove(FINGERS,step,true);
        this->hand->servos.relativeMove(INDEX,step,true);
    }
    else
    {
        this->hand->servos.relativeMove(FINGERS,-step,true);
        this->hand->servos.relativeMove(INDEX,-step,true);
    }
}


