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

#define DIGITALBUTTON_PRESSED LOW
#define ANALOGBUTTON_PRESSED  200

// dependencies
#include <Arduino.h>

/**
 * TODO : A6 and A7 are analog inputs. Can't use DigitalRead function on them --> replace them by GPIO ?
 */
class Hackberry_buttons{


    public: 
    Hackberry_buttons(unsigned char pinCalib, unsigned char pinExtra,unsigned char pinThumb,unsigned char pinLock);

    void init();

     // Get button state
    bool isCalibButtonPressed();
    bool isExtraButtonPressed();
    bool isThumbButtonPressed();
    bool isLockButtonPressed();

    bool isCalibButtonPressedFor(unsigned long delay_ms);
    bool isExtraButtonPressedFor(unsigned long delay_ms);
    bool isThumbButtonPressedFor(unsigned long delay_ms);
    bool isLockButtonPressedFor(unsigned long delay_ms);

    private:

    // Wiring pins
    unsigned char _pinCalib;       // Start hand calibration
    unsigned char _pinExtra;       // Reverse the direction of rotation of the fingers
    unsigned char _pinThumb;       // Thumb opening / closing
    unsigned char _pinLock;        // lock / unlock the fingers

    bool _isCalibPressed = false;
    bool _isExtraPressed = false;
    bool _isThumbPressed = false;
    bool _isLockPressed = false;

    unsigned long _CalibPressedTime = 0;
    unsigned long _ExtraPressedTime = 0;
    unsigned long _ThumbPressedTime = 0;
    unsigned long _LockPressedTime = 0;

    bool isButtonPressed(unsigned char pin); 
    bool isButtonPressedFor(unsigned char pin, unsigned long *pressTime, unsigned long delay_ms);
};




#endif