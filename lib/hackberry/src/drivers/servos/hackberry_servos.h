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

// class
class Hackberry_servos{

    public: 
    Hackberry_servos(int indexPin, int thumbPin, int fingersPin);
    void init(bool selectedHand);

    // speed
    void setSpeed(int speed);
    int getSpeed();

    // moving fingers
    void move(int member, int position, bool waitEnabled);
    void relativeMove(int member, int degree, bool waitEnabled);
    
    void open(int member);
    void close(int member);
    void openAll();
    void closeAll();
    int getPosition(int member);
    
    private:
    // wiring pins
    int _pinServoIndex;
    int _pinServoThumb;
    int _pinServoFingers;
    
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