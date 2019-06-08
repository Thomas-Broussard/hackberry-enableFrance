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
 * Constructor of the Buttons driver
 * 
 * @param pinCalib digital input - pin of the Calibration button (located at the top left of the hand)
 * @param pinExtra digital input - pin of the Extra button (located at the center left of the hand)
 * @param pinThumb digital input - pin of the Thumb button (located at the bottom left of the hand)
 * @param pinLock digital input - pin of the Lock button (located at the right of the hand)
 */
Hackberry_buttons::Hackberry_buttons(int pinCalib, int pinExtra, int pinThumb, int pinLock)
{
    this->_pinCalib       = pinCalib;
    this->_pinExtra       = pinExtra; 
    this->_pinThumb       = pinThumb;
    this->_pinLock        = pinLock;
}

/**
 * Initialize the pins of buttons
 */
void Hackberry_buttons::init()
{
    pinMode(_pinCalib, INPUT_PULLUP);
    pinMode(_pinExtra, INPUT_PULLUP);
    pinMode(_pinThumb, INPUT_PULLUP);
    pinMode(_pinLock , INPUT_PULLUP);
}

/**
 * Get the current state of the Calib button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isCalibButtonPressed(){
    return  this->isButtonPressed(this->_pinCalib);
}

/**
 * Get the current state of the Extra button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isExtraButtonPressed(){
    return  this->isButtonPressed(this->_pinExtra);
}

/**
 * Get the current state of the Thumb button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isThumbButtonPressed(){
    return this->isButtonPressed(this->_pinThumb);
}

/**
 * Get the current state of the Lock button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isLockButtonPressed(){
    return this->isButtonPressed(this->_pinLock);
}


/**
 * Get the current state of button (even if it's wired on an analog pin, but it's not recommended)
 * 
 * @param pin pin of the button to check
 * @return true if button pressed. false if button released 
 */
bool Hackberry_buttons::isButtonPressed(int pin){
    // analog pin
    if (pin == A6 || pin == A7)
    {
        return analogRead(pin) < ANALOGBUTTON_PRESSED ? true : false;
    }
    // digital pin
    else
    {
        return digitalRead(pin) == DIGITALBUTTON_PRESSED ? true:false ;
    }
}
