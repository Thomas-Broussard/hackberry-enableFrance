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

void Routine_moves::init(Hackberry_hand *hand)
{
    this->hand = hand;
}

void Routine_moves::execute()
{
    int sensorValue = this->hand->sensor.readAverage();


    // Open hand
    if (sensorValue < OPEN_THRESHOLD)
    {
        this->hand->servos.relativeOpen(FINGERS,STEP_MOVE_DEGREE,true);
        this->hand->servos.relativeOpen(INDEX,STEP_MOVE_DEGREE,true);
    }
    // Close Hand
    else if (sensorValue > CLOSE_THRESHOLD)
    {
        this->hand->servos.relativeClose(FINGERS,STEP_MOVE_DEGREE,true);
        this->hand->servos.relativeClose(INDEX,STEP_MOVE_DEGREE,true);
    }

    
}


