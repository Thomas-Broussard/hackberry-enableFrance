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
unsigned int intervalBetweenMoves = 200;
unsigned int speedMoves = 30;

// put variable to "true" to enable the members you want to test 
bool TestIndex = true;
bool TestThumb = true;
bool TestFingers = true;


void setup() {
  Serial.begin(9600);
  hackberry.begin(RIGHT_HAND);

  hackberry.servos.setSpeed(speedMoves);

  // Test 
  hackberry.servos.closeAll();
  delay(1000);
  hackberry.servos.openAll();
}

void loop() 
{  
  // Moving Thumb
  if (TestThumb)
  {
    Serial.println("Open THUMB");
    hackberry.servos.close(THUMB);
    delay(intervalBetweenMoves);

    Serial.println("Close THUMB");
    hackberry.servos.open(THUMB);
    delay(intervalBetweenMoves);
  }

  // Moving Index
  if (TestIndex)
  {
    Serial.println("Open INDEX");
    hackberry.servos.close(INDEX);
    delay(intervalBetweenMoves);

    Serial.println("Close INDEX");
    hackberry.servos.open(INDEX);
    delay(intervalBetweenMoves);
  }
  

  // Moving Fingers
  if (TestFingers)
  {
    Serial.println("Open FINGERS");
    hackberry.servos.close(FINGERS);
    delay(intervalBetweenMoves);

    Serial.println("Close FINGERS");
    hackberry.servos.open(FINGERS);
    delay(intervalBetweenMoves);
  }
  
}
