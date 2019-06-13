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

// Members
#ifndef THUMB
#define THUMB 1
#endif

#ifndef INDEX
#define INDEX 2
#endif

#ifndef FINGERS
#define FINGERS 3
#endif

// Hand
#ifndef LEFT_HAND
#define LEFT_HAND false
#endif

#ifndef RIGHT_HAND
#define RIGHT_HAND true
#endif


// class
class Hackberry_servos{

    public: 
    Hackberry_servos(unsigned char indexPin, unsigned char thumbPin, unsigned char fingersPin);
    void init();

    // Hand type
    void setHand(bool selectedHand);
    bool getHand();
    void changeHand();

    // speed
    void setSpeed(unsigned char  speed);
    unsigned char getSpeed();

    // moving fingers
    void move(unsigned char member, unsigned char position, bool waitEnabled);
    
    void relativeMove(unsigned char member, unsigned char degree, bool waitEnabled);
    void relativeOpen(unsigned char member, unsigned char degree, bool waitEnabled);
    void relativeClose(unsigned char member, unsigned char degree, bool waitEnabled);
    
    void open(unsigned char member);
    void close(unsigned char member);
    void openAll();
    void closeAll();

    // moving fingers (forced)
    void forceMove(unsigned char member,  unsigned char position);
    void forceRelativeMove(unsigned char member, unsigned char position);
    void forceRelativeOpen(unsigned char member, unsigned char degree);
    void forceRelativeClose(unsigned char member, unsigned char degree);

    // Positions of fingers
    void setLimitPositions(unsigned char  member, unsigned char limit1, unsigned char limit2);

    unsigned char  getPosition(unsigned char member);
    unsigned char  getOpenPosition(unsigned char  member);
    unsigned char  getClosePosition(unsigned char  member);

    void lockMember(unsigned char  member);
    void unlockMember(unsigned char member);
    
    private:
    // wiring pins
    unsigned char _pinServoIndex;
    unsigned char _pinServoThumb;
    unsigned char _pinServoFingers;

    // Servomotors
    VarSpeedServo  servoIndex;  
    VarSpeedServo  servoThumb;  
    VarSpeedServo  servoFingers; 

    // Selected hand (right or left)
    bool _selectedHand = RIGHT_HAND;
    
    bool _lockThumb = false;
    bool _lockIndex = false;
    bool _lockFingers = false;

    unsigned char _speed = DEFAULT_SPEED;

    // limit of movements
    unsigned char _openThumb , _closedThumb;
    unsigned char _openIndex , _closedIndex;
    unsigned char _openFingers , _closedFingers;

    // servomotor move
    void moveServo(unsigned char member, unsigned char wantedPosition);
    void moveServo(unsigned char member, unsigned char wantedPosition, bool waitEnabled);
    
    // utils
    unsigned char framePosition(unsigned char value, unsigned char lim1, unsigned char lim2);
    
};


#endif