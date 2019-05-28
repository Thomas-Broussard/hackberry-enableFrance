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

#include "hackberry_buttons.h"


/**
 * Constructor
 * 
 */
Hackberry_buttons::Hackberry_buttons(int pinCalib, int pinExtra, int pinThumb, int pinLock)
{
    this->_pinCalib       = pinCalib;
    this->_pinExtra       = pinExtra; 
    this->_pinThumb       = pinThumb;
    this->_pinLock        = pinLock;
}

/**
 * Initialize pins of buttons
 */
void Hackberry_buttons::init()
{
    // pins initialization
    pinMode(_pinCalib, INPUT_PULLUP);
    pinMode(_pinExtra, INPUT_PULLUP);
    pinMode(_pinThumb, INPUT_PULLUP);
    pinMode(_pinLock , INPUT_PULLUP);
}

/**
 * get the current state of the Calib button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isCalibButtonPressed()
{
    return digitalRead(this->_pinCalib) == BUTTONPRESSED ? true:false ;
}

/**
 * get the current state of the Extra button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isExtraButtonPressed(){
    return digitalRead(this->_pinExtra) == BUTTONPRESSED ? true:false ;
}

/**
 * get the current state of the Thumb button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isThumbButtonPressed(){
    return digitalRead(this->_pinThumb) == BUTTONPRESSED ? true:false ;
}

/**
 * get the current state of the Lock button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isLockButtonPressed(){
    return digitalRead(this->_pinLock) == BUTTONPRESSED ? true:false ;
}