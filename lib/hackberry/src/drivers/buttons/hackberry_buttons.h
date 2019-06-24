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
#include "hackberry_global.h"

#define NB_BUTTONS 4 // Number of buttons on Hackberry hand

// Buttons
#define BUTTON_CALIB 0
#define BUTTON_EXTRA 1
#define BUTTON_THUMB 2
#define BUTTON_LOCK  3 

/**
 * TODO : A6 and A7 are analog inputs. Can't use DigitalRead function on them --> replace them by GPIO ?
 */
class Hackberry_buttons{


    public: 
    Hackberry_buttons();

    void init(unsigned char pinCalib = UNDEFINED, unsigned char pinExtra = UNDEFINED, unsigned char pinThumb = UNDEFINED, unsigned char pinLock = UNDEFINED);

    bool isPressed(int index);
    bool isPressedFor(int index, unsigned long delay_ms);

    private:

    // Wiring pins
    unsigned char _pins[NB_BUTTONS];        // button pins
    bool _isPressed[NB_BUTTONS];            // states of the button
    unsigned long _PressedTime[NB_BUTTONS]; // durations of the buttons press


    bool isButtonPressed(unsigned char pin); 
};




#endif