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

//#include "dependencies/VarSpeedServo.h"
#include "dependencies/ServoCC.h"

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

        Hackberry_servos();

        void init(unsigned char indexPin, unsigned char thumbPin, unsigned char fingersPin);
        void init(unsigned char indexPin, unsigned char thumbPin, unsigned char fingersPin, unsigned char indexMeasurePin, unsigned char fingersMeasurePin);
        
        // Hand type
        void setHand(bool selectedHand);
        bool getHand();
        void changeHand();

        // speed
        void setSpeed(unsigned char speed);
        unsigned char getSpeed();

        // moving fingers
        void move(unsigned char member, int position);
        
        void relativeMove(unsigned char member, int degree);
        void relativeOpen(unsigned char member, int degree);
        void relativeClose(unsigned char member, int degree);
        
        void open(unsigned char member);
        void close(unsigned char member);
        void openAll();
        void closeAll();

        // moving fingers (forced)
        void forceMove(unsigned char member,  int position);
        void forceRelativeMove(unsigned char member, int position);
        void forceRelativeOpen(unsigned char member, int degree);
        void forceRelativeClose(unsigned char member, int degree);

        // Positions of fingers
        void setLimitPositions(unsigned char  member, unsigned char limit1, unsigned char limit2);

        unsigned char  getPosition(unsigned char member);
        unsigned char  getOpenPosition(unsigned char  member);
        unsigned char  getClosePosition(unsigned char  member);

        void lockMember(unsigned char  member);
        void unlockMember(unsigned char member);

        // Current Sensor (Mk3 only)
        unsigned int readMeasure(unsigned char member);
    


    private:
        // wiring pins
        unsigned char _pinServoIndex;
        unsigned char _pinServoThumb;
        unsigned char _pinServoFingers;

        unsigned char _pinMeasureIndex;
        unsigned char _pinMeasureFingers;
        //unsigned char _pinMeasureThumb; // not used

        // Servomotors
        ServoCC servoIndex;  
        ServoCC servoThumb;  
        ServoCC servoFingers; 

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
        
        // utils
        unsigned char framePosition(unsigned char value, unsigned char lim1, unsigned char lim2);
};


#endif