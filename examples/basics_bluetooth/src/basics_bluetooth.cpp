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
String message;
void setup() {
  Serial.begin(9600);
 
  hackberry.begin(RIGHT_HAND);
  hackberry.bluetooth.start();
  Serial.println("START");
}

void loop() 
{  
   hackberry.bluetooth.execute();
}
