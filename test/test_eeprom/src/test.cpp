/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Unit test template for EEPROM
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * 
 *  Unit test made with Arduinounit
 *  https://github.com/mmurdoch/arduinounit
 * =============================================================================================================================================
 */

#line 2 "TEST EEPROM"

#include <Arduino.h>
#include "ArduinoUnit.h"
#include "hackberry.h"

/* 
* =============================================================================================================================================
*                                  SETUP TEST
* =============================================================================================================================================
*/
Hackberry hackberry;
void setup() {

  hackberry.begin(RIGHT_HAND,TYPE_IR_SENSOR,false);
  Serial.begin(9600);
}

/* 
* =============================================================================================================================================
*                                  TESTING FUNCTIONS
* =============================================================================================================================================
*/
void testServo(int member)
{
  int previousmin = hackberry.eeprom.GetMinServo(member);
  int previousmax = hackberry.eeprom.GetMaxServo(member);
  int min = random(0,180);
  int max = random(0,180);

  hackberry.eeprom.SetMinServo(member, min);
  assertEqual(min, hackberry.eeprom.GetMinServo(member));

  hackberry.eeprom.SetMinServo(member, previousmin);
  assertEqual(previousmin, hackberry.eeprom.GetMinServo(member));

  hackberry.eeprom.SetMaxServo(member, max);
  assertEqual(max, hackberry.eeprom.GetMaxServo(member));
  
  hackberry.eeprom.SetMaxServo(member, previousmax);
  assertEqual(previousmax, hackberry.eeprom.GetMaxServo(member));
}

/* 
* =============================================================================================================================================
*                                  TEST CASES
* =============================================================================================================================================
*/

// -----------------------------------
// TEST EEPROM GENERAL
// -----------------------------------
test(eeprom_hand_type)
{
  bool previousval = hackberry.eeprom.GetHand();

  hackberry.eeprom.SetHand(RIGHT_HAND);
  assertEqual(RIGHT_HAND, hackberry.eeprom.GetHand());

  hackberry.eeprom.SetHand(LEFT_HAND);
  assertEqual(LEFT_HAND, hackberry.eeprom.GetHand());

  hackberry.eeprom.SetHand(previousval);
  assertEqual(previousval, hackberry.eeprom.GetHand());
}

// -----------------------------------
// TEST EEPROM SERVOMOTORS
// -----------------------------------
test(eeprom_servo_thumb)
{
  testServo(THUMB);
}

test(eeprom_servo_index)
{
  testServo(INDEX);
}

test(eeprom_servo_fingers)
{
  testServo(FINGERS);
}

// -----------------------------------
// TEST EEPROM SENSOR
// -----------------------------------
test(eeprom_sensor_type)
{
  int previousval = hackberry.eeprom.GetSensorType();
  int testvalue = random(0,10);

  hackberry.eeprom.SetSensorType(testvalue);
  assertEqual(testvalue, hackberry.eeprom.GetSensorType());

  hackberry.eeprom.SetSensorType(previousval);
  assertEqual(previousval, hackberry.eeprom.GetSensorType());
}

test(eeprom_sensor_offset)
{
  int previousval = hackberry.eeprom.GetSensorOffset();
  int testvalue = random(-2000,2000);
  hackberry.eeprom.SetSensorOffset(testvalue);
  assertEqual(testvalue, hackberry.eeprom.GetSensorOffset());

  hackberry.eeprom.SetSensorOffset(previousval);
  assertEqual(previousval, hackberry.eeprom.GetSensorOffset());
}

test(eeprom_sensor_gain)
{
  float previousval = hackberry.eeprom.GetSensorGain();
  float testvalue = random(0,2000)/100.0;

  hackberry.eeprom.SetSensorGain(testvalue);
  assertEqual(testvalue, hackberry.eeprom.GetSensorGain());

  hackberry.eeprom.SetSensorGain(previousval);
  assertEqual(previousval, hackberry.eeprom.GetSensorGain());
}

/* 
* =============================================================================================================================================
*                                  RUNNING TEST
* =============================================================================================================================================
*/
void loop() 
{  
  Test::run();
}
