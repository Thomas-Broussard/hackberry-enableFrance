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

  hackberry.hand.init(RIGHT_HAND,TYPE_IR_SENSOR);
  Serial.begin(9600);
}

/* 
* =============================================================================================================================================
*                                  TESTING FUNCTIONS
* =============================================================================================================================================
*/
void testServo(int member)
{
  int previousmin = hackberry.hand.eeprom.GetMinServo(member);
  int previousmax = hackberry.hand.eeprom.GetMaxServo(member);
  int min = random(0,180);
  int max = random(0,180);

  hackberry.hand.eeprom.SetMinServo(member, min);
  assertEqual(min, hackberry.hand.eeprom.GetMinServo(member));

  hackberry.hand.eeprom.SetMinServo(member, previousmin);
  assertEqual(previousmin, hackberry.hand.eeprom.GetMinServo(member));

  hackberry.hand.eeprom.SetMaxServo(member, max);
  assertEqual(max, hackberry.hand.eeprom.GetMaxServo(member));
  
  hackberry.hand.eeprom.SetMaxServo(member, previousmax);
  assertEqual(previousmax, hackberry.hand.eeprom.GetMaxServo(member));
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
  bool previousval = hackberry.hand.eeprom.GetHand();

  hackberry.hand.eeprom.SetHand(RIGHT_HAND);
  assertEqual(RIGHT_HAND, hackberry.hand.eeprom.GetHand());

  hackberry.hand.eeprom.SetHand(LEFT_HAND);
  assertEqual(LEFT_HAND, hackberry.hand.eeprom.GetHand());

  hackberry.hand.eeprom.SetHand(previousval);
  assertEqual(previousval, hackberry.hand.eeprom.GetHand());
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
  int previousval = hackberry.hand.eeprom.GetSensorType();
  int testvalue = random(0,10);

  hackberry.hand.eeprom.SetSensorType(testvalue);
  assertEqual(testvalue, hackberry.hand.eeprom.GetSensorType());

  hackberry.hand.eeprom.SetSensorType(previousval);
  assertEqual(previousval, hackberry.hand.eeprom.GetSensorType());
}

test(eeprom_sensor_offset)
{
  int previousval = hackberry.hand.eeprom.GetSensorOffset();
  int testvalue = random(-2000,2000);
  hackberry.hand.eeprom.SetSensorOffset(testvalue);
  assertEqual(testvalue, hackberry.hand.eeprom.GetSensorOffset());

  hackberry.hand.eeprom.SetSensorOffset(previousval);
  assertEqual(previousval, hackberry.hand.eeprom.GetSensorOffset());
}

test(eeprom_sensor_gain)
{
  float previousval = hackberry.hand.eeprom.GetSensorGain();
  float testvalue = random(0,2000)/100.0;

  hackberry.hand.eeprom.SetSensorGain(testvalue);
  assertEqual(testvalue, hackberry.hand.eeprom.GetSensorGain());

  hackberry.hand.eeprom.SetSensorGain(previousval);
  assertEqual(previousval, hackberry.hand.eeprom.GetSensorGain());
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
