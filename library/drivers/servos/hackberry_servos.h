/* 
 *  =============================================================================================================================================
 *  Projet : Hackberry e-Nable France
 *  Auteur : Thomas Broussard
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

// dependencies
#include "hackberry.h"

// constants
#define THUMB   1
#define INDEX   2
#define FINGERS  3

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
    Servo servoIndex;  //index 
    Servo servoPouce;  //pouce
    Servo servoDoigts; //les trois autres doigts  

    // déplacement des servomoteurs
    moveServo(int member, int position);


    // limit of movements
    int openThumb , closedThumb;
    int openIndex , closedIndex;
    int openFingers , closedFingers;
};
#endif