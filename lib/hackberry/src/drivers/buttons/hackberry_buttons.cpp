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
 */
Hackberry_buttons::Hackberry_buttons()
{
}

/**
 * Initialize the Buttons Driver
 * 
 * @param pinCalib digital input - pin of the Calibration button (located at the top left of the hand)
 * @param pinExtra digital input - pin of the Extra button (located at the center left of the hand)
 * @param pinThumb digital input - pin of the Thumb button (located at the bottom left of the hand)
 * @param pinLock digital input - pin of the Lock button (located at the right of the hand)
 */
void Hackberry_buttons::init(unsigned char pinCalib, unsigned char pinExtra, unsigned char pinThumb, unsigned char pinLock)
{
    this->_pins[BUTTON_CALIB] = pinCalib;
    this->_pins[BUTTON_EXTRA] = pinExtra; 
    this->_pins[BUTTON_THUMB] = pinThumb;
    this->_pins[BUTTON_LOCK]  = pinLock;

    for(int pin: _pins)
    {
        pinMode(pin, INPUT_PULLUP);
    }
}


/**
 * Get the current state of the button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isPressed(int index){
    bool isPressed = this->isButtonPressed(this->_pins[index]);

    if (this->_isPressed[index] != isPressed)
    {
        this->_PressedTime[index] = millis();
        this->_isPressed[index] = isPressed;
    }
    return isPressed;  
}

/**
 * Check if the button is pressed since the programmed delay
 * 
 * @param delay_ms programmed delay (in milliseconds)
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isPressedFor(int index,unsigned long delay_ms)
{
    bool isPressed = this->isButtonPressed(this->_pins[index]);
    // Check if button is pressed or not 
    if (!isPressed)
    {
        this->_PressedTime[index] = millis();
        return false;
    }
    else
    {
        return ((millis() - this->_PressedTime[index] ) >= delay_ms);
    }  
}


/**
 * Get the current state of button (even if it's wired on an analog pin, but it's not recommended)
 * 
 * @param pin pin of the button to check
 * @return true if button pressed. false if button released 
 */
bool Hackberry_buttons::isButtonPressed(unsigned char pin){
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
