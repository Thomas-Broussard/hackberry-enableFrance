/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library to control the push buttons of the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_BUTTONS_H__
#define __HACKBERRY_BUTTONS_H__

// dependencies
#include "hackberry.h"


// class
class Hackberry_buttons{


    public: 
    Hackberry_buttons(Hackberry _hackberry);

    void init(bool selectedHand);

    // Functions called when a button is pressed
    void buttonAction_Calib();
    void buttonAction_Extra();
    void buttonAction_Thumb();
    void buttonAction_Lock();

    private:

    // Hackberry Hand
    Hackberry _hackberry;

    // Wiring pins
    int _pinCalib;       // Start hand calibration
    int _pinExtra;       // Reverse the direction of rotation of the fingers
    int _pinThumb;       // Thumb opening / closing
    int _pinLock;        // lock / unlock the fingers 
};




#endif