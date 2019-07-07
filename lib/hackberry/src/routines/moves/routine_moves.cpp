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
    this->lastMoveTime = millis();
}


// TODO : replace relative moves by absolute moves
void Routine_moves::execute()
{
    if(this->hand->getMode() != Standard) return;
    if (!this->isMoveExecutable()) return;
    
    int sensorValue = this->hand->sensor.readAverage();
    // int degree = STEP_MOVE_DEGREE;
    int degree = this->speedOfMove(sensorValue);

    // Open hand
    if (sensorValue < OPEN_THRESHOLD)
    {
        this->hand->servos.relativeOpen(FINGERS,degree);
        this->hand->servos.relativeOpen(INDEX,degree);
        
    }
    // Close Hand
    else if (sensorValue > CLOSE_THRESHOLD)
    {
        this->hand->servos.relativeClose(FINGERS,degree);
        this->hand->servos.relativeClose(INDEX,degree);
    }
}

int Routine_moves::speedOfMove(int sensorValue)
{
    int result = 0;
    if (sensorValue > CLOSE_THRESHOLD){
        result =  map(sensorValue,CLOSE_THRESHOLD,MAX_ADC, MIN_STEP_DEGREE, MAX_STEP_DEGREE);
    }
    else if (sensorValue < OPEN_THRESHOLD){
        result = map(sensorValue,MIN_ADC,OPEN_THRESHOLD, MAX_STEP_DEGREE, MIN_STEP_DEGREE);
    }
    return constrain(result,MIN_STEP_DEGREE ,MAX_STEP_DEGREE);
}

bool Routine_moves::isMoveExecutable()
{
     // test : one move per X ms
    if (millis() - this->lastMoveTime > 15)
    {
        this->lastMoveTime = millis();
        return true;
    }
    return false;
}

