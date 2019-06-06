/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Handle the behavior of buttons
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "routine_buttons.h"


Routine_buttons::Routine_buttons()
{}

void Routine_buttons::init(Hackberry_hand *hand)
{
    this->hand = hand;
}


void Routine_buttons::execute()
{
    if (this->hand->buttons.isCalibButtonPressed())
    {
        if (this->isDebounced(&this->lastCalibDebounce, DEBOUNCE_DELAY))
        {
            this->actionCalib();
        }
    }


    else if (this->hand->buttons.isExtraButtonPressed())
    {
        if (this->isDebounced(&this->lastExtraDebounce, DEBOUNCE_DELAY))
        {
            this->actionExtra();
        }
    }

    else if (this->hand->buttons.isThumbButtonPressed())
    {
        if (this->isDebounced(&this->lastThumbDebounce, DEBOUNCE_DELAY))
        {
            this->actionThumb();
        }
    }


    else if (this->hand->buttons.isLockButtonPressed())
    {
        if (this->isDebounced(&this->lastLockDebounce, DEBOUNCE_DELAY))
        {
            this->actionLock();
        }
    }

}

/**
 * Action executed when Calib button is pressed
 * 
 * Trigger the calibration sequence for the sensor
 */
void Routine_buttons::actionCalib()
{
    Serial.println("actionCalib");
    if (!this->hand->isCalibrationEnabled())
    {
        this->hand->startCalibration();
    }
}

/**
 * Action executed when Extra button is pressed
 * 
 * idea : enable/disable bluetooth here ? 
 */
void Routine_buttons::actionExtra()
{
    Serial.println("actionExtra");
    // TODO : add code here
    if (this->hand->bluetooth.isEnabled())
    {
        this->hand->bluetooth.stop();
    }
    else
    {
        this->hand->bluetooth.start();
    }
    
}

/**
 * Action executed when Thumb button is pressed
 * 
 * put Thumb in open or close position
 */
void Routine_buttons::actionThumb()
{
    Serial.println("actionThumb");
    if (isThumbOpen)
    {
        this->hand->servos.close(THUMB);
        this->isThumbOpen = false;
    }
    else
    {
        this->hand->servos.open(THUMB);
        this->isThumbOpen = true;
    }
}

/**
 * Action executed when Lock button is pressed
 * 
 */
void Routine_buttons::actionLock()
{
    Serial.println("actionLock");
    if (isLockEnabled)
    {
        this->hand->servos.unlockMember(FINGERS);
        this->isLockEnabled = false;
    }
    else
    {
        this->hand->servos.lockMember(FINGERS);
        this->isLockEnabled = true;
    }
}

/**
 * Check if a button is debounced or not
 * 
 * @param lastDebounceTime pointer to last debounce time of the button (to update it)
 * @param debounceDelay minimum delay between toggles to debounce the circuit
 *  
 * @return true if debounce is finished ; false otherwise
 */
bool Routine_buttons::isDebounced(unsigned long *lastDebounceTime, unsigned long debounceDelay)
{
    bool result = false;
    
    result = (millis() - *lastDebounceTime) > debounceDelay;
    *lastDebounceTime = millis();
    return result;
}
