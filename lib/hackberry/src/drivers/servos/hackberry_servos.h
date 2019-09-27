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
#include "hackberry_mapping.h"

//#include "dependencies/VarSpeedServo.h"
#include "dependencies/ServoCC.h"


// POSITIONS OF MEMBERS
/*
#define ANGLE               20
#define THUMB_INIT_POS      90 
#define INDEX_INIT_POS      90
#define FINGERS_INIT_POS    90 
*/
    /* initialisation of limits close to those of the old software */
//right:open, left:close (temp)
#define THUMB_MAX    105       //(THUMB_INIT_POS + ANGLE)
#define INDEX_MAX    120       //(INDEX_INIT_POS + ANGLE)    
#define FINGERS_MAX   75      //(FINGERS_INIT_POS + ANGLE)

//right:close, left:open (temp)
#define THUMB_MIN     20      //(THUMB_INIT_POS - ANGLE) 
#define INDEX_MIN      20     //(INDEX_INIT_POS - ANGLE)
#define FINGERS_MIN    20     //(FINGERS_INIT_POS - ANGLE)


// INITIAL SPEED OF SERVOMOTOR
#define DEFAULT_SPEED 50

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
        void microsMove(unsigned char member, int position);
        
        void perdixmileRelativeMove(unsigned char member, int perdixmile);
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
        void setLimitPositions(unsigned char  member, int limit1, int limit2);

        unsigned char  getPosition(unsigned char member);
        unsigned char  getOpenPosition(unsigned char  member);
        unsigned char  getClosePosition(unsigned char  member);

        void lockMember(unsigned char  member);
        void unlockMember(unsigned char member);
        void deactivIfPeriodExp(int member);
        void activTempo(int member,int periode);

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
        #ifdef __SERVO_CC_H__
            ServoCC servoIndex;  
            ServoCC servoThumb;  
            ServoCC servoFingers; 
        #else
            VarSpeedServo servoIndex;  
            VarSpeedServo servoThumb;  
            VarSpeedServo servoFingers; 
        #endif
        

        // Selected hand (right or left)
        bool _selectedHand = RIGHT_HAND;
        
        bool _lockThumb = false;
        bool _lockIndex = false;
        bool _lockFingers = false;

        unsigned char _speed = DEFAULT_SPEED;

        // limit of movements
        int _openThumb , _closedThumb;
        int _openIndex , _closedIndex;
        int _openFingers , _closedFingers;
        int _openThumbMu , _closedThumbMu;
        int _openIndexMu , _closedIndexMu;
        int _openFingersMu , _closedFingersMu;

        //gestion deactivation
        int toDesactivThumb=0;
        int toDesactivIndex=0;
        int toDesactivFingers=0;
        
    #define DELAY_TO_DESACTIV 10
  
        // servomotor move
        void moveServo(unsigned char member, int wantedPosition);
        int getMicrosPosition(unsigned char  member);
        
        // utils
        int framePosition(int value, int lim1, int lim2);
};


#endif