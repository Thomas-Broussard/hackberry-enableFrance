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
    // special function of the buttons at start-up
    if(this->hand->getMode() == PowerOn)
    {
        if (this->hand->buttons.isPressed(BUTTON_EXTRA))
        {
            if(millis()>1000){
                DebugPrintln(F("Start Init&HandChoice"));
                // TODO this->hand->eeprom.loadDefaultParameters();
                this->hand->setMode(HandCalibration);
            }
            
        }
        else if (this->hand->buttons.isPressed(BUTTON_CALIB)
                && this->hand->buttons.isPressed(BUTTON_THUMB) )
        {
            if(millis()>1000)
            {
                DebugPrintln(F("Start Servos Calib"));
                this->hand->servos.move(FINGERS,0);
                delay(100);
                this->hand->servos.move(FINGERS,180);
                this->hand->startServosCalibration(Standard);
            }
        }       
        else
        {
            DebugPrintln(F("EndPowerOn"));
            this->hand->setMode(Standard);
        }
    }
    // standard function of the buttons
    else if (this->hand->buttons.isPressed(BUTTON_CALIB))
    {
        if (this->isDebounced(&this->lastCalibDebounce, DEBOUNCE_DELAY))
        {
            this->actionCalib();
        }
        if(this->hand->buttons.isPressedFor(BUTTON_CALIB , LONG_BUTTON_PRESS))
        {
            if (this->isDebounced(&this->lastLongCalibDebounce, LONG_DEBOUNCE_DELAY))
            {
                this->longActionCalib();
            }
        }
    }

    else if (this->hand->buttons.isPressed(BUTTON_EXTRA))
    {
        if (this->isDebounced(&this->lastExtraDebounce, DEBOUNCE_DELAY))
        {
            this->actionExtra();
        }
        if(this->hand->buttons.isPressedFor(BUTTON_EXTRA, LONG_BUTTON_PRESS))
        {
            if (this->isDebounced(&this->lastLongExtraDebounce, LONG_DEBOUNCE_DELAY))
            {
                this->longActionExtra();
            }
        }
    }

    else if (this->hand->buttons.isPressed(BUTTON_THUMB))
    {
        if (this->isDebounced(&this->lastThumbDebounce, DEBOUNCE_DELAY))
        {
            this->actionThumb();
        }
        if(this->hand->buttons.isPressedFor(BUTTON_THUMB , LONG_BUTTON_PRESS))
        {
            if (this->isDebounced(&this->lastLongThumbDebounce, LONG_DEBOUNCE_DELAY))
            {
                this->longActionThumb();
            }
        }
    }

    else if (this->hand->buttons.isPressed(BUTTON_LOCK))
    {
        if (this->isDebounced(&this->lastLockDebounce, DEBOUNCE_DELAY))
        {
            this->actionLock();
        }
        if(this->hand->buttons.isPressedFor(BUTTON_LOCK, LONG_BUTTON_PRESS))
        {
            if (this->isDebounced(&this->lastLongLockDebounce, LONG_DEBOUNCE_DELAY))
            {
                this->longActionLock();
            }
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
    DebugPrintln(F("Calib Pressed"));

    switch (this->hand->getMode())
    {
        default:break;
    }
}

/**
 * Action executed when Calib button is pressed for a long time
 * 
 * Start the Sensor Calibration sequence
 */
void Routine_buttons::longActionCalib()
{
    DebugPrintln(F("Calib Pressed Long"));

    switch (this->hand->getMode())
    {
        case Standard :
            DebugPrintln(F("Start Sensor Calib"));
            this->hand->servos.move(INDEX,0);
            delay(100);
            this->hand->servos.move(INDEX,180);
            this->hand->startSensorCalibration(Standard);
        break;

        default:break;
    }
}


/**
 * Action executed when Extra button is pressed
 * 
 * validate servos calibration step (ServosCalibration mode only)
 */
void Routine_buttons::actionExtra()
{
    DebugPrintln(F("Extra Pressed"));

    switch (this->hand->getMode())
    {
        case ServosCalibration : 
            this->hand->nextServosCalibration();
        break;
        default:break;
    }
}

/**
 * Action executed when Extra button is pressed for a long time
 * 
 * launch servomotors calibration
 */
void Routine_buttons::longActionExtra()
{
    DebugPrintln(F("Extra Pressed Long"));

    switch (this->hand->getMode())
    {
        case Standard :
            DebugPrintln(F("Start Servos Calib"));
            this->hand->servos.move(FINGERS,0);
            delay(100);
            this->hand->servos.move(FINGERS,180);
            this->hand->startServosCalibration(Standard);
        break;

        default:break;
    }
}
 

/**
 * Action executed when Thumb button is pressed
 * 
 * put Thumb in open or close position
 */
void Routine_buttons::actionThumb()
{
    DebugPrintln(F("Thumb Pressed"));

    switch (this->hand->getMode())
    {
        case Standard :
            if (isThumbOpen)
            {
                DebugPrintln(F("Close Thumb"));
                this->hand->servos.close(THUMB);
                this->isThumbOpen = false;
            }
            else
            {
                DebugPrintln(F("Open Thumb"));
                this->hand->servos.open(THUMB);
                this->isThumbOpen = true;
            }
        break;

        default:break;
    }
}


/**
 * Action executed when Thumb button is pressed for a long time
 * button for extension boards
 */
void Routine_buttons::longActionThumb()
{
    DebugPrintln(F("Thumb Pressed Long"));

    switch (this->hand->getMode())
    {
        
        case Standard:
            #if EXTENSION_BOARD == BLUETOOTH_BOARD
                this->hand->setMode(Bluetooth);
            #endif
            break;

        case Bluetooth:
            #if EXTENSION_BOARD == BLUETOOTH_BOARD
                this->hand->setMode(Standard);
            #endif
            break;
             

        default:break;
    }
}


/**
 * Action executed when Lock button is pressed
 * 
 */
void Routine_buttons::actionLock()
{
    DebugPrintln(F("Lock Pressed"));
    
    switch (this->hand->getMode())
    {
        case Standard :
            if (isLockEnabled)
            {
                DebugPrintln(F("Unlock Fingers"));
                this->hand->servos.unlockMember(FINGERS);
                this->isLockEnabled = false;
            }
            else
            {
                DebugPrintln(F("Lock Fingers"));
                this->hand->servos.lockMember(FINGERS);
                this->isLockEnabled = true;
            }
        break;
        case ServosCalibration : 
            this->hand->endServosCalibration();       //nextServosCalibration();
        break;
        default:break;
    }
}


/**
 * Action executed when Lock button is pressed for a long time
 * 
 */
void Routine_buttons::longActionLock()
{
    DebugPrintln(F("Lock Pressed Long"));
    
    switch (this->hand->getMode())
    {
        case Bluetooth:
        case Standard:
            this->hand->servos.changeHand();
            this->hand->eeprom.ChangeHand();

            DebugPrint(F("new Hand type = "));
            DebugPrintln(this->hand->eeprom.GetHand() == RIGHT_HAND ? "Right":"Left");
        default:break;
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
