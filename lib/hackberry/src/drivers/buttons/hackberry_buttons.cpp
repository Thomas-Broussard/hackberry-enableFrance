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
    bool result = this->isButtonPressed(this->_pinCalib);

    if (this->_isCalibPressed != result)
    {
        this->_CalibPressedTime = millis();
        this->_isCalibPressed = result;
    }
    return result;  
}

/**
 * Get the current state of the Extra button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isExtraButtonPressed(){
    bool result = this->isButtonPressed(this->_pinExtra);

    if (this->_isExtraPressed != result)
    {
        this->_ExtraPressedTime = millis();
        this->_isExtraPressed = result;
    }
    return result; 
}

/**
 * Get the current state of the Thumb button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isThumbButtonPressed(){
    bool result = this->isButtonPressed(this->_pinThumb);

    if (this->_isThumbPressed != result)
    {
        this->_ThumbPressedTime = millis();
        this->_isThumbPressed = result;
    }
    return result; 
}

/**
 * Get the current state of the Lock button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isLockButtonPressed(){
    bool result = this->isButtonPressed(this->_pinLock);

    if (this->_isLockPressed != result)
    {
        this->_LockPressedTime = millis();
        this->_isLockPressed = result;
    }
    return result; 
}


/**
 * Check if the Calib button is pressed since the programmed delay
 * 
 * @param delay_ms programmed delay (in milliseconds)
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isCalibButtonPressedFor(unsigned long delay_ms)
{
    // Check if button is pressed or not 
    if (!this->_isCalibPressed)
    {
        this->_CalibPressedTime = millis();
        return false;
    }
    else
    {
        return ((millis() - this->_CalibPressedTime ) >= delay_ms);
    }  
}

/**
 * Check if the Extra button is pressed since the programmed delay
 * 
 * @param delay_ms programmed delay (in milliseconds)
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isExtraButtonPressedFor(unsigned long delay_ms)
{
    // Check if button is pressed or not 
    if (!this->_isExtraPressed)
    {
        this->_ExtraPressedTime = millis();
        return false;
    }
    else
    {
        return ((millis() - this->_ExtraPressedTime ) >= delay_ms);
    }  
}

/**
 * Check if the Thumb button is pressed since the programmed delay
 * 
 * @param delay_ms programmed delay (in milliseconds)
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isThumbButtonPressedFor(unsigned long delay_ms)
{
    // Check if button is pressed or not 
    if (!this->_isThumbPressed)
    {
        this->_ThumbPressedTime = millis();
        return false;
    }
    else
    {
        return ((millis() - this->_ThumbPressedTime ) >= delay_ms);
    }  
}

/**
 * Check if the Lock button is pressed since the programmed delay
 * 
 * @param delay_ms programmed delay (in milliseconds)
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isLockButtonPressedFor(unsigned long delay_ms)
{
    // Check if button is pressed or not 
    if (!this->_isLockPressed)
    {
        this->_LockPressedTime = millis();
        return false;
    }
    else
    {
        return ((millis() - this->_LockPressedTime ) >= delay_ms);
    }  
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
