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

// Task Scheduler configuration (must be define before include)
#define _TASK_SLEEP_ON_IDLE_RUN // Enable sleep mode when tasks aren't running, to save power
#define _TASK_PRIORITY
#define _TASK_WDT_IDS
#define _TASK_TIMECRITICAL

// libraries dependencies
#include <Arduino.h>
#include "TaskScheduler.h"
#include "hackberry.h"

Hackberry hackberry;

// function call
void setPriorities();

// Scheduler
Scheduler runner;

// Priority order : critical > high > runner
Scheduler highPriority;
Scheduler criticalPriority;

// Tasks callbacks
void Task_Buttonhandler();
void Task_BluetoothHandler();
void Task_Moves();
void Task_BatteryMonitoring();
void Task_Template();

// Tasks
Task T1(50  * TASK_MILLISECOND, TASK_FOREVER, &Task_Buttonhandler     , &runner, true); // executed every 50ms
Task T2(100 * TASK_MILLISECOND, TASK_FOREVER, &Task_BluetoothHandler  , &criticalPriority, true); // executed every 100ms
Task T3(200 * TASK_MILLISECOND, TASK_FOREVER, &Task_Moves             , &runner, true); // executed every 200ms
Task T4(10  * TASK_SECOND     , TASK_FOREVER, &Task_BatteryMonitoring , &highPriority, true); // executed every 10s

// Task template
Task T5(500 * TASK_MILLISECOND, TASK_FOREVER, &Task_Template          , &runner, true); // executed every 500ms


void setup() 
{
  Serial.begin(9600);
  hackberry.init();
  setPriorities();
}

void loop() 
{  
  runner.execute();
}


/* 
 * =============================================================================================
 *                                        SCHEDULER CONFIGURATION
 * =============================================================================================
 */
void setPriorities()
{
  runner.setHighPriorityScheduler(&highPriority);
  highPriority.setHighPriorityScheduler(&criticalPriority);
  runner.enableAll(true);
}

/* 
 * =============================================================================================
 *                                        TASKS EXECUTION
 * =============================================================================================
 */
void Task_Buttonhandler()
{
  hackberry.routine.buttons.execute();
}

void Task_BluetoothHandler()
{
  hackberry.routine.bluetooth.execute();
}

void Task_Moves()
{
  hackberry.routine.moves.execute();
}

void Task_BatteryMonitoring()
{
  hackberry.routine.batteryMonitoring.execute();
}

void Task_Template()
{
  // create your own task here
}