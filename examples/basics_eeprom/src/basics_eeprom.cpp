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
bool readMode = true;


void setup() {
  Serial.begin(9600);
  hackberry.begin(RIGHT_HAND,STANDARD_IR_SENSOR);

  
  if(checkMemoryMap)
  {
      hackberry.eeprom.printMemoryMap();
  }


  if(readMode)
  {
      Serial.println("=========================");
      Serial.println("       READ MODE");
      Serial.println("=========================");

      bool Hand = hackberry.eeprom.GetHand();
      Serial.print("Hand = "); Serial.println( Hand == RIGHT_HAND ? "Right":"Left");

      Serial.print("MinThumb = ");      Serial.println( hackberry.eeprom.GetMinServo(THUMB) );
      Serial.print("MinIndex = ");      Serial.println( hackberry.eeprom.GetMinServo(INDEX) );
      Serial.print("MinFingers = ");    Serial.println( hackberry.eeprom.GetMinServo(FINGERS) );

      Serial.print("MaxThumb = ");      Serial.println( hackberry.eeprom.GetMaxServo(THUMB) );
      Serial.print("MaxIndex = ");      Serial.println( hackberry.eeprom.GetMaxServo(INDEX) );
      Serial.print("MaxFingers = ");    Serial.println( hackberry.eeprom.GetMaxServo(FINGERS) );


      Serial.print("SensorType = ");    Serial.println( hackberry.eeprom.GetSensorType() );
      Serial.print("SensorGain = ");    Serial.println( hackberry.eeprom.GetSensorGain() );
      Serial.print("SensorOffset = ");  Serial.println( hackberry.eeprom.GetSensorOffset() );
  }
  // write mode
  else
  {
    Serial.println("=========================");
    Serial.println("       WRITE MODE");
    Serial.println("=========================");
    hackberry.eeprom.SetHand(RIGHT_HAND);

    hackberry.eeprom.SetMinServo(THUMB,5);
    hackberry.eeprom.SetMinServo(INDEX,18);
    hackberry.eeprom.SetMinServo(FINGERS,23);

    hackberry.eeprom.SetMaxServo(THUMB,166);
    hackberry.eeprom.SetMaxServo(INDEX,46);
    hackberry.eeprom.SetMaxServo(FINGERS,38);

    hackberry.eeprom.SetSensorType(8);
    hackberry.eeprom.SetSensorGain(1.66);
    hackberry.eeprom.SetSensorOffset(99);

    Serial.println("\n Write finished. Put variable readMode to \"true\" to see the eeprom content");
  }

  
}

void loop() 
{  
}
