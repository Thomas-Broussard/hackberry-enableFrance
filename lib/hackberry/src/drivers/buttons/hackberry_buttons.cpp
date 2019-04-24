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
Hackberry_buttons::Hackberry_buttons()
{
}

/**
 * Initialize pins of buttons
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry_buttons::init(bool selectedHand)
{
    // pins selection
    if (selectedHand == RIGHT_HAND)
    {
        this->_pinCalib       = A6;
        this->_pinExtra       = A7; 
        this->_pinThumb       = A0;
        this->_pinLock        = 10;
    }
    else if (selectedHand == LEFT_HAND)
    {
        this->_pinCalib       = A6;
        this->_pinExtra       = A7; 
        this->_pinThumb       = A0;
        this->_pinLock        = 10;
    }   

    // pins initialization
    pinMode(_pinCalib, INPUT_PULLUP);
    pinMode(_pinExtra, INPUT_PULLUP);
    pinMode(_pinThumb, INPUT_PULLUP);
    pinMode(_pinLock , INPUT_PULLUP);
}


/**
 * Function called when the Calibration button is pressed
 */
void Hackberry_buttons::buttonAction_Calib()
{
    /** TODO : complete this function */
}

/**
 * Function called when the Extra button is pressed
 */
void Hackberry_buttons::buttonAction_Extra()
{
    /** TODO : complete this function */
}

/**
 * Function called when the Thumb button is pressed
 */
void Hackberry_buttons::buttonAction_Thumb()
{
    /** TODO : complete this function */
}

/**
 * Function called when the Lock button is pressed
 */
void Hackberry_buttons::buttonAction_Lock()
{
    /** TODO : complete this function */
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
    return digitalRead(this->_pinThumb)== BUTTONPRESSED ? true:false ;
}

/**
 * get the current state of the Lock button
 * 
 * @return true : button pressed / false : button released 
 */
bool Hackberry_buttons::isLockButtonPressed(){
    return digitalRead(this->_pinLock) == BUTTONPRESSED ? true:false ;
}