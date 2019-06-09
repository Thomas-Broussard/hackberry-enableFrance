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
#define _TASK_PRIORITY          // Enable the task priority system

// libraries dependencies
#include <Arduino.h>
#include "TaskScheduler.h"
#include "hackberry.h"
#include "hackberry_mapping.h"

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
void Task_Calibration();
void Task_Template();

// Tasks
Task T1(100  * TASK_MILLISECOND, TASK_FOREVER, &Task_Buttonhandler     , &runner, true); 
Task T2(10 * TASK_MILLISECOND, TASK_FOREVER, &Task_Moves             , &runner, true); 
Task T3(50  * TASK_MILLISECOND, TASK_FOREVER, &Task_Calibration     , &criticalPriority, true); 

// Task enabled on Mk3 board only
#ifdef MAPPING_MK3
  Task T4(100 * TASK_MILLISECOND, TASK_FOREVER, &Task_BluetoothHandler  , &criticalPriority, true); 
  Task T5(10  * TASK_SECOND     , TASK_FOREVER, &Task_BatteryMonitoring , &highPriority, true); 
#endif

// Task template
//Task T_template(500 * TASK_MILLISECOND, TASK_FOREVER, &Task_Template          , &runner, true); // executed every 500ms


void setup() 
{
  Serial.begin(9600);
  Serial.println("Start");
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

void Task_Calibration()
{
  switch(hackberry.hand.getMode())
  {
    case SensorCalibration :
      hackberry.routine.calibration_sensor.execute();  
    break;

    case ServosCalibration :
      hackberry.routine.calibration_servos.execute(); 
    break;

    default:break;
  }
}

void Task_Template()
{
  // create your own task here
}  