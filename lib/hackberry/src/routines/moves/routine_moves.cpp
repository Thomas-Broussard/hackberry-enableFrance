/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Authors  : Thomas Broussard, Joël Liénard
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



void Routine_moves::execute()
{
    // conditions to make a move
    if(this->hand->getMode() != Standard && this->hand->getMode() != Bluetooth) return; // Moves can be done in Standard or Bluetooth mode only
    if(this->hand->getMode() == Bluetooth && !this->hand->isMovesEnabled()) return; // in Bluetooth mode, Moves need to be enabled
     const int pinTEST = LED_BUILTIN;
    digitalWrite(pinTEST, HIGH);
    // arrived here, a move will be made
    int sensorValue = this->hand->sensor.readAverage();
    int valCurrentI=0;
    int valCurrentF=0;
    valCurrentI= this->hand->servos.readMeasure(INDEX);
    valCurrentF= this->hand->servos.readMeasure(FINGERS);
    
    // Open hand
    if (sensorValue < OPEN_THRESHOLD){
        //this->hand->servos.relativeOpen(FINGERS, 20);
        //this->hand->servos.relativeOpen(INDEX,20);
        
        int speed =  map(sensorValue,OPEN_THRESHOLD,MAX_ADC, 0, MAX_STEP_MOVE_MICROS);
        this->hand->servos.perdixmileRelativeMove(INDEX,  -speed);
        this->hand->servos.perdixmileRelativeMove(FINGERS,  -speed);
        
    }
    // Close Hand
    else if (sensorValue > CLOSE_THRESHOLD){
        //this->hand->servos.relativeClose(FINGERS,2);
        //this->hand->servos.relativeClose(INDEX,2);
        
        int speed =  map(sensorValue,CLOSE_THRESHOLD,MAX_ADC, 0, MAX_STEP_MOVE_MICROS);
        int force = map(valCurrentI, 0, 1023, 0, GAIN_FORCE_INDEX);
        this->hand->servos.perdixmileRelativeMove(INDEX,  -speed + force);
        force = map(valCurrentF, 0, 1023, 0, GAIN_FORCE_FINGERS);
        this->hand->servos.perdixmileRelativeMove(FINGERS,  -speed + force);
        
    }
    // Feedback
    {
      int tmpVal = map(valCurrentI+valCurrentF, 0, 1023, 0, 255);
      if(tmpVal>255)tmpVal=255;
      analogWrite(PIN_FEEDBACK,tmpVal);//retour d'effort
    }
    #if (0)
    {//pour mise au point
    //Serial.print(valCurrentI);Serial.print(" ,");Serial.println(valCurrentF);
    int tmpVal = map(valCurrentF+valCurrentI, 0, 2000, 45, 150);
    this->hand->servos.forceMove(THUMB,tmpVal);//servo Thumb utilisé pour visualiser l'effort
    }
    #endif
    digitalWrite(pinTEST, LOW);
}
#if(0)
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

#endif