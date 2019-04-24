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

#define BUTTONPRESSED LOW

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"

// class
class Hackberry_buttons{


    public: 
    Hackberry_buttons();

    void init(bool selectedHand);

    // Functions called when a button is pressed
    void buttonAction_Calib();
    void buttonAction_Extra();
    void buttonAction_Thumb();
    void buttonAction_Lock();

     // Get button state
    bool isCalibButtonPressed();
    bool isExtraButtonPressed();
    bool isThumbButtonPressed();
    bool isLockButtonPressed();

    private:

    // Wiring pins
    int _pinCalib;       // Start hand calibration
    int _pinExtra;       // Reverse the direction of rotation of the fingers
    int _pinThumb;       // Thumb opening / closing
    int _pinLock;        // lock / unlock the fingers 
};




#endif