/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Minimalist example of Hackberry_sensor library usage
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include <Arduino.h>
#include "hackberry.h"
#include "TaskScheduler.h"

Hackberry hackberry;


// Scheduler
Scheduler runner;


int intervalBetweenEachRead = 1000; // ms
int sensorVal;

// Tasks Callbacks
void Task_Buttonhandler();
void Task_Sensorhandler();

Task T1(200  * TASK_MILLISECOND, TASK_FOREVER, &Task_Buttonhandler  , &runner, true); 
Task T2(intervalBetweenEachRead * TASK_MILLISECOND, TASK_FOREVER, &Task_Sensorhandler  , &runner, true );

void setup() {
  Serial.begin(9600);
  hackberry.init(RIGHT_HAND,TYPE_IR_SENSOR);
}

void loop() 
{  
  runner.execute(); 
}


void Task_Buttonhandler()
{
  hackberry.routine.buttons.execute();
  hackberry.routine.calibration.execute();
}

void Task_Sensorhandler()
{
  sensorVal = hackberry.hand.sensor.readAverage();
  Serial.print("Sensor Value = ");
  Serial.println(sensorVal);
}