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
#include <Arduino.h>
#include "hackberry_global.h"
#include "dependencies/VarSpeedServo.h"

// Constants
#define PIN_INDEX 6 
#define PIN_THUMB 9
#define PIN_FINGERS 5

// class
class Hackberry_servos{

    public: 
    Hackberry_servos();
    void init(bool selectedHand);

    // moving fingers
    void move(int member, int position);
    void open(int member);
    void close(int member);
    void openAll();
    void closeAll();
    int getPosition(int member);
    
    private:
    // wiring pins
    int _pinServoIndex  = PIN_INDEX;
    int _pinServoThumb  = PIN_THUMB;
    int _pinServoFingers = PIN_FINGERS;
    
    // Servomotors
    VarSpeedServo  servoIndex;  
    VarSpeedServo  servoThumb;  
    VarSpeedServo  servoFingers; 

    // servomotor move
    void moveServo(int member, int wantedPosition);
    

    // limit of movements
    int openThumb , closedThumb;
    int openIndex , closedIndex;
    int openFingers , closedFingers;
};


// Functions outside of the class (utilities)
int frameInteger(int value, int min, int max);

#endif