/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Minimalist example of Hackberry_bluetooth library usage
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include <Arduino.h>
#include "hackberry.h"

Hackberry hackberry;

void setup() {
  Serial.begin(9600);
 
  hackberry.init(RIGHT_HAND,TYPE_IR_SENSOR);
  
  Serial.println("START");

  // Enable the bluetooth routine
  hackberry.routine.bluetooth.start();
}

void loop() 
{  
  hackberry.routine.bluetooth.execute();
}
