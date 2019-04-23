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
 * @param hackberry current Hackberry Hand object in use
 */
Hackberry_buttons::Hackberry_buttons(Hackberry hackberry)
{
    this->_hackberry = hackberry;
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
        this->_pinExtra       = A5; 
        this->_pinThumb       = A4;
        this->_pinLock        = A3;
    }
    else if (selectedHand == LEFT_HAND)
    {
        this->_pinCalib       = 11;
        this->_pinExtra       = 10; 
        this->_pinThumb       = 8;
        this->_pinLock        = 7;
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
    this->_hackberry._isThumbOpen = !this->_hackberry._isThumbOpen;
}

/**
 * Function called when the Lock button is pressed
 */
void Hackberry_buttons::buttonAction_Lock()
{
    /** TODO : complete this function */
}
