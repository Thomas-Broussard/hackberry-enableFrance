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

    // set parameters
    void setSpeed(int speed);

    // moving fingers
    void move(int member, int position, bool waitEnabled);
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
    void moveServo(int member, int wantedPosition, bool waitEnabled);
    

    // limit of movements
    int openThumb , closedThumb;
    int openIndex , closedIndex;
    int openFingers , closedFingers;

    // speed
    int _speed;
};


// Functions outside of the class (utilities)
int frameInteger(int value, int min, int max);

#endif