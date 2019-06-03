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
  hackberry.init(RIGHT_HAND,TYPE_IR_SENSOR,false);
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

  hackberry.hand.servos.setLimitPositions(member,lim1,lim2);

  // RIGHT HAND
  hackberry.hand.servos.setHand(RIGHT_HAND);
  assertEqual(max, hackberry.hand.servos.getOpenPosition(member));
  assertEqual(min, hackberry.hand.servos.getClosePosition(member));

  // LEFT HAND
  hackberry.hand.servos.setHand(LEFT_HAND);
  assertEqual(min, hackberry.hand.servos.getOpenPosition(member));
  assertEqual(max, hackberry.hand.servos.getClosePosition(member));
}

void TestOpenClose(int member, bool selectedHand)
{
  
  hackberry.hand.servos.setHand(selectedHand);

  // OPEN
  hackberry.hand.servos.open(member);
  assertEqual(hackberry.hand.servos.getOpenPosition(member), hackberry.hand.servos.getPosition(member));

  // CLOSE
  hackberry.hand.servos.close(member);
  assertEqual(hackberry.hand.servos.getClosePosition(member), hackberry.hand.servos.getPosition(member));
}

void TestOpenCloseAll(bool selectedHand)
{
  hackberry.hand.servos.setHand(selectedHand);

  // OPEN
  hackberry.hand.servos.openAll();
  assertEqual(hackberry.hand.servos.getOpenPosition(THUMB), hackberry.hand.servos.getPosition(THUMB));
  assertEqual(hackberry.hand.servos.getOpenPosition(INDEX), hackberry.hand.servos.getPosition(INDEX));
  assertEqual(hackberry.hand.servos.getOpenPosition(FINGERS), hackberry.hand.servos.getPosition(FINGERS));

  // CLOSE
  hackberry.hand.servos.closeAll();
  assertEqual(hackberry.hand.servos.getClosePosition(THUMB), hackberry.hand.servos.getPosition(THUMB));
  assertEqual(hackberry.hand.servos.getClosePosition(INDEX), hackberry.hand.servos.getPosition(INDEX));
  assertEqual(hackberry.hand.servos.getClosePosition(FINGERS), hackberry.hand.servos.getPosition(FINGERS));
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
