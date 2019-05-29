/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Unit test template
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * 
 *  Unit test made with Arduinounit
 *  https://github.com/mmurdoch/arduinounit
 * =============================================================================================================================================
 */

#line 2 "TEST SERVOS"

#include <Arduino.h>
#include "ArduinoUnit.h"
#include "hackberry.h"

Hackberry hackberry;
void setup() 
{
  hackberry.begin(RIGHT_HAND,TYPE_IR_SENSOR,false);
  Serial.begin(9600);
}


/* 
* =============================================================================================================================================
*                                  TESTING FUNCTIONS
* =============================================================================================================================================
*/
void TestLimitPositions(int member, int lim1, int lim2)
{
  int min = (lim1 < lim2)? lim1:lim2;
  int max = (lim1 > lim2)? lim1:lim2;

  hackberry.servos.setLimitPositions(member,lim1,lim2);

  // RIGHT HAND
  hackberry.servos.setHand(RIGHT_HAND);
  assertEqual(max, hackberry.servos.getOpenPosition(member));
  assertEqual(min, hackberry.servos.getClosePosition(member));

  // LEFT HAND
  hackberry.servos.setHand(LEFT_HAND);
  assertEqual(min, hackberry.servos.getOpenPosition(member));
  assertEqual(max, hackberry.servos.getClosePosition(member));
}

void TestOpenClose(int member, bool selectedHand)
{
  
  hackberry.servos.setHand(selectedHand);

  // OPEN
  hackberry.servos.open(member);
  assertEqual(hackberry.servos.getOpenPosition(member), hackberry.servos.getPosition(member));

  // CLOSE
  hackberry.servos.close(member);
  assertEqual(hackberry.servos.getClosePosition(member), hackberry.servos.getPosition(member));
}

void TestOpenCloseAll(bool selectedHand)
{
  hackberry.servos.setHand(selectedHand);

  // OPEN
  hackberry.servos.openAll();
  assertEqual(hackberry.servos.getOpenPosition(THUMB), hackberry.servos.getPosition(THUMB));
  assertEqual(hackberry.servos.getOpenPosition(INDEX), hackberry.servos.getPosition(INDEX));
  assertEqual(hackberry.servos.getOpenPosition(FINGERS), hackberry.servos.getPosition(FINGERS));

  // CLOSE
  hackberry.servos.closeAll();
  assertEqual(hackberry.servos.getClosePosition(THUMB), hackberry.servos.getPosition(THUMB));
  assertEqual(hackberry.servos.getClosePosition(INDEX), hackberry.servos.getPosition(INDEX));
  assertEqual(hackberry.servos.getClosePosition(FINGERS), hackberry.servos.getPosition(FINGERS));
}

/* 
* =============================================================================================================================================
*                                  TEST CASES
* =============================================================================================================================================
*/

test(thumb_limit_positions)
{
  int lim1 = random(0,180);
  int lim2 = random(0,180);

  TestLimitPositions(THUMB,lim1,lim2);
  TestLimitPositions(THUMB,-10,190);
}

test(index_limit_positions)
{
  int lim1 = random(0,180);
  int lim2 = random(0,180);

  TestLimitPositions(INDEX,lim1,lim2);
  TestLimitPositions(INDEX,-10,190);
}

test(fingers_limit_positions)
{
  int lim1 = random(0,180);
  int lim2 = random(0,180);

  TestLimitPositions(FINGERS,lim1,lim2);
  TestLimitPositions(FINGERS,-10,190);
}

test(thumb_open_close)
{
  TestOpenClose(THUMB,LEFT_HAND);
  TestOpenClose(THUMB,RIGHT_HAND);
}

test(index_open_close)
{
  TestOpenClose(INDEX,LEFT_HAND);
  TestOpenClose(INDEX,RIGHT_HAND);
}

test(fingers_open_close)
{
  TestOpenClose(FINGERS,LEFT_HAND);
  TestOpenClose(FINGERS,RIGHT_HAND);
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
