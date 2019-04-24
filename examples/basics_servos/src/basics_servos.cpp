/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Minimalist example of Hackberry_servos library usage
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include <Arduino.h>
#include "hackberry.h"

Hackberry hackberry;

// time betwen each move made
unsigned int intervalBetweenMoves = 1000;

// put variable to "true" to enable the members you want to test 
bool TestIndex = true;
bool TestThumb = false;
bool TestFingers = false;


void setup() {
  Serial.begin(9600);
  hackberry.begin(RIGHT_HAND);
}

void loop() 
{  
  // Moving Thumb
  if (TestThumb)
  {
    hackberry.servos.open(THUMB);
    delay(intervalBetweenMoves);
    hackberry.servos.close(THUMB);
    delay(intervalBetweenMoves);
  }

  // Moving Index
  if (TestIndex)
  {
    hackberry.servos.open(INDEX);
    delay(intervalBetweenMoves);
    hackberry.servos.close(INDEX);
    delay(intervalBetweenMoves);
  }
  

  // Moving Fingers
  if (TestFingers)
  {
    hackberry.servos.open(FINGERS);
    delay(intervalBetweenMoves);
    hackberry.servos.close(FINGERS);
    delay(intervalBetweenMoves);
  }
  
}
