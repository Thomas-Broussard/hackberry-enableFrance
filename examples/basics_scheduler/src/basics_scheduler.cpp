/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Basic example on how to use the scheduler
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * 
 *  TaskScheduler Library, created by Anatoli Arkhipenko.
 *  https://github.com/arkhipenko/TaskScheduler
 * =============================================================================================================================================
 */


/**
 *  Task are used to call functions regularly, without having to use the delay ()
 * 
 *  How to create a new task :
 *  1 - create a function that will be called by your task ( = Task Callback)
 * 
 *  2 - create a Task object :
 *  Task(interval,execution,callback,*scheduler,true);
 * 
 *  with the following parameters : 
 *    @param time : define the interval between each trigger (in ms)
 *    @param execution : number of execution (or TASK_FOREVER to run infinite)
 *    @param callback : function called when task is triggered
 *    @param *scheduler : address to scheduler object (here : &runner)
 * 
 * 3 - run runner.execute() in the void loop()
 *
*/


#include <Arduino.h>
#include "TaskScheduler.h"
#include "hackberry.h"

Hackberry hackberry;

// Scheduler
Scheduler runner;


// Tasks callbacks
void Task_1s();
void Task_5s();
void Task_10s();

// Tasks
Task T_1s(1 * TASK_SECOND, TASK_FOREVER, &Task_1s, &runner, true);
Task T_5s(5 * TASK_SECOND, TASK_FOREVER, &Task_5s, &runner, true);
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
void Task_1s()
{
  Serial.println("task every 1s");
}

void Task_5s()
{
  Serial.println("task every 5s");
}

void Task_10s()
{
  Serial.println("task every 10s");
}