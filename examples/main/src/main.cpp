/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Main program of Hackberry Hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * 
 *  TaskScheduler Library, created by Anatoli Arkhipenko.
 *  https://github.com/arkhipenko/TaskScheduler
 * =============================================================================================================================================
 */

#include <Arduino.h>
#include "TaskScheduler.h"
#include "hackberry.h"

Hackberry hackberry;

// Scheduler
Scheduler runner;

// Tasks callbacks
void Task_50ms();
void Task_100ms();
void Task_200ms();
void Task_500ms();
void Task_10s();

// Tasks
Task T_50ms(50 * TASK_MILLISECOND, TASK_FOREVER, &Task_50ms, &runner, true);
Task T_100ms(100 * TASK_MILLISECOND, TASK_FOREVER, &Task_100ms, &runner, true);
Task T_200ms(200 * TASK_MILLISECOND, TASK_FOREVER, &Task_200ms, &runner, true);
Task T_500ms(500 * TASK_MILLISECOND, TASK_FOREVER, &Task_500ms, &runner, true);
Task T_10s(10 * TASK_SECOND, TASK_FOREVER, &Task_10s, &runner, true);



void setup() 
{
  Serial.begin(9600);
  hackberry.init(RIGHT_HAND,TYPE_IR_SENSOR);
}

void loop() 
{  
  runner.execute();
}



/* 
 * =============================================================================================
 *                                        TASKS EXECUTION
 * =============================================================================================
 */
void Task_50ms()
{
  hackberry.routine.buttons.execute();
}

void Task_100ms()
{
  hackberry.routine.bluetooth.execute();
}

void Task_200ms()
{
  hackberry.routine.moves.execute();
}

void Task_500ms()
{
  
}

void Task_10s()
{
  hackberry.routine.batteryMonitoring.execute();
}