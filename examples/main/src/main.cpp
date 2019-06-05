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

#define _TASK_SLEEP_ON_IDLE_RUN // Enable sleep mode when tasks aren't running, to save power

Hackberry hackberry;

// Scheduler
Scheduler runner;

// Tasks callbacks
void Task1();
void Task2();
void Task3();
void Task4();
void Task5();

// Tasks
Task T1(50  * TASK_MILLISECOND, TASK_FOREVER, &Task1, &runner, true); // executed every 50ms
Task T2(100 * TASK_MILLISECOND, TASK_FOREVER, &Task2, &runner, true); // executed every 100ms
Task T3(200 * TASK_MILLISECOND, TASK_FOREVER, &Task3, &runner, true); // executed every 200ms
Task T4(500 * TASK_MILLISECOND, TASK_FOREVER, &Task4, &runner, true); // executed every 500ms
Task T5(10  * TASK_SECOND     , TASK_FOREVER, &Task5, &runner, true); // executed every 10s


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
void Task1()
{
  hackberry.routine.buttons.execute();
}

void Task2()
{
  hackberry.routine.bluetooth.execute();
}

void Task3()
{
  hackberry.routine.moves.execute();
}

void Task4()
{
  
}

void Task5()
{
  hackberry.routine.batteryMonitoring.execute();
}