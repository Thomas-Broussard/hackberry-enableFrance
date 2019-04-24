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

Hackberry hackberry;

int intervalBetweenEachRead = 500; // ms
int sensorVal;


void setup() {
  Serial.begin(9600);
  hackberry.begin(RIGHT_HAND,STANDARD_IR_SENSOR);
}

void loop() 
{  
  sensorVal = hackberry.sensor.readAverage();
  Serial.print("Sensor Value = ");
  Serial.println(sensorVal);
  delay(intervalBetweenEachRead);  
}
