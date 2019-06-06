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

bool checkMemoryMap = true;
bool readMode = false;


void setup() {
  Serial.begin(9600);
  hackberry.init();

  if(checkMemoryMap)
  {
      hackberry.hand.eeprom.printMemoryMap();
  }


  if(readMode)
  {
      Serial.println("=========================");
      Serial.println("     READ ONLY MODE");
      Serial.println("=========================");

      hackberry.hand.eeprom.printMemoryContent();
  }
  // write mode
  else
  {
    Serial.println("=========================");
    Serial.println("       WRITE MODE");
    Serial.println("=========================");
    hackberry.hand.eeprom.SetHand(RIGHT_HAND);

    hackberry.hand.eeprom.SetMinServo(THUMB,5);
    hackberry.hand.eeprom.SetMinServo(INDEX,18);
    hackberry.hand.eeprom.SetMinServo(FINGERS,23);

    hackberry.hand.eeprom.SetMaxServo(THUMB,166);
    hackberry.hand.eeprom.SetMaxServo(INDEX,46);
    hackberry.hand.eeprom.SetMaxServo(FINGERS,38);

    hackberry.hand.eeprom.SetSensorType(8);
    hackberry.hand.eeprom.SetSensorMin(100);
    hackberry.hand.eeprom.SetSensorMax(900);

    Serial.println("\nWrite finished\n");

    hackberry.hand.eeprom.printMemoryContent();
  }
}

void loop() 
{  
}
