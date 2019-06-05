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
  hackberry.init(RIGHT_HAND,TYPE_IR_SENSOR);

  
  if(checkMemoryMap)
  {
      hackberry.hand.eeprom.printMemoryMap();
  }


  if(readMode)
  {
      Serial.println("=========================");
      Serial.println("       READ MODE");
      Serial.println("=========================");

      bool Hand = hackberry.hand.eeprom.GetHand();
      Serial.print("Hand = "); Serial.println( Hand == RIGHT_HAND ? "Right":"Left");

      Serial.print("MinThumb = ");      Serial.println( hackberry.hand.eeprom.GetMinServo(THUMB) );
      Serial.print("MinIndex = ");      Serial.println( hackberry.hand.eeprom.GetMinServo(INDEX) );
      Serial.print("MinFingers = ");    Serial.println( hackberry.hand.eeprom.GetMinServo(FINGERS) );

      Serial.print("MaxThumb = ");      Serial.println( hackberry.hand.eeprom.GetMaxServo(THUMB) );
      Serial.print("MaxIndex = ");      Serial.println( hackberry.hand.eeprom.GetMaxServo(INDEX) );
      Serial.print("MaxFingers = ");    Serial.println( hackberry.hand.eeprom.GetMaxServo(FINGERS) );


      Serial.print("SensorType = ");    Serial.println( hackberry.hand.eeprom.GetSensorType() );
      Serial.print("SensorGain = ");    Serial.println( hackberry.hand.eeprom.GetSensorGain() );
      Serial.print("SensorOffset = ");  Serial.println( hackberry.hand.eeprom.GetSensorOffset() );
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
    hackberry.hand.eeprom.SetSensorGain(1.66);
    hackberry.hand.eeprom.SetSensorOffset(99);

    Serial.println("\n Write finished. Put variable readMode to \"true\" to see the eeprom content");
  }
}

void loop() 
{  
}
