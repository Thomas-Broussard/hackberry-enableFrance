/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Minimalist example of Hackberry_buttons library usage
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
}

void loop() 
{  
  if (hackberry.hand.buttons.isCalibButtonPressed())
  {
    Serial.println("Calibration Button pressed !");
    delay(1000);
  }

  if (hackberry.hand.buttons.isThumbButtonPressed())
  {
    Serial.println("Thumb Button pressed !");
    delay(1000);
  }
  
  if (hackberry.hand.buttons.isExtraButtonPressed())
  {
    Serial.println("Extra Button pressed !");
    delay(1000);
  }

  if (hackberry.hand.buttons.isLockButtonPressed())
  {
    Serial.println("Lock Button pressed !");
    delay(1000);
  }
}
