/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for controlling Hackberry hand servomotors
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_SERVOS_H__
#define __HACKBERRY_SERVOS_H__

// Dependencies
#include "hackberry.h"

// Constants
#define THUMB   1
#define INDEX   2
#define FINGERS  3

// Default parameters
#define THUMB_MAX           140  //right:open, left:close
#define INDEX_MAX           130  //right:open, left:close
#define FINGERS_MAX         145  //right:open, left:close

#define THUMB_MIN           47   //right:close, left:open
#define INDEX_MIN           27   //right:close, left:open
#define FINGERS_MIN         105  //right:close, left:open


// class
class Hackberry_servos{

    public: 
    Hackberry_servos(Hackberry _hackberry);
    init(bool selectedHand);

    // moving fingers
    move(int member, int position);
    open(int member);
    close(int member);
    openAll();
    closeAll();
    
    private:
    // Hackberry hand
    Hackberry _hackberry;

    // wiring pins
    _pinServoIndex  = 3; 
    _pinServoThumb  = 6;
    _pinServoFingers = 5;
    
    // Servomotors
    Servo servoIndex;  
    Servo servoThumb;  
    Servo servoFingers; 

    // servomotor move
    moveServo(int member, int position);


    // limit of movements
    int openThumb , closedThumb;
    int openIndex , closedIndex;
    int openFingers , closedFingers;
};


// Functions outside the class (utilities)
void frameInteger(int value, int min, int max);

#endif