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
    if(this->hand->getMode() != Standard) return;
    
    int sensorValue = this->hand->sensor.readAverage();
    /*#ifdef DEBUG_ROUTINE_ENABLED
    Serial.print("Sensor Value = ");
    Serial.println(sensorValue);
    #endif*/

    // Open hand
    if (sensorValue < OPEN_THRESHOLD)
    {
        /*#ifdef DEBUG_ROUTINE_ENABLED
        Serial.println("Open hand...");
        #endif*/
        this->hand->servos.relativeOpen(FINGERS,STEP_MOVE_DEGREE,false);
        this->hand->servos.relativeOpen(INDEX,STEP_MOVE_DEGREE,false);
    }
    // Close Hand
    else if (sensorValue > CLOSE_THRESHOLD)
    {

        this->hand->servos.relativeClose(FINGERS,STEP_MOVE_DEGREE,false);
        this->hand->servos.relativeClose(INDEX,STEP_MOVE_DEGREE,false);
    }

    
}


