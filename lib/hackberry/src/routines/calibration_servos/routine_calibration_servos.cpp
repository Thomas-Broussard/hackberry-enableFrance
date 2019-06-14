/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Routine for Hackberry servomotors calibration
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "routine_calibration_servos.h"


Routine_calibration_servos::Routine_calibration_servos()
{

}

/**
 * Initialize the calibration servos routine
 * 
 * @param hand Hackberry_hand object that contains all the hackberry drivers to use
 */
void Routine_calibration_servos::init(Hackberry_hand *hand)
{
    this->hand = hand;
}

/**
 * Execute the calibration servos main code
 */
void Routine_calibration_servos::execute()
{
    // code executed when calibration is enabled
    if (this->hand->getMode() == ServosCalibration && this->_currentStep == IDLE)
    {
        this->start();
    }

    // code executed when calibration is in progress
    else if(this->hand->getMode() == ServosCalibration)
    {
        int nextStep = this->hand->getServosCalibrationStep();

        // next step enabled
        if (this->_currentStep != nextStep)
        {
            this->SaveParamBeforeNextStep();

            this->_currentStep = nextStep;
            DebugPrintln(F("Next Calib Step"));
        }

        // calibration sequence
        if (this->_currentStep < END)
        {
            this->calibration();
        }
        // end of the calibration sequence
        else
        {
            this->end();
        }
    }

}

/**
 * Start the calibration sequence
 */
void Routine_calibration_servos::start()
{
    this->_currentStep = 1;
}


/**
 * End of the calibration sequence
 */
void Routine_calibration_servos::end()
{
    this->_currentStep = IDLE;
    this->EndCalibServos();

    DebugPrintln(F("Servos Calib Finished"));
        
    DebugPrint(F("MinIndex = ")); 
    DebugPrintln( this->hand->eeprom.GetMinServo(INDEX) );
    DebugPrint(F("MaxIndex = ")); 
    DebugPrintln( this->hand->eeprom.GetMaxServo(INDEX) );

    DebugPrint(F("MinFingers = ")); 
    DebugPrintln( this->hand->eeprom.GetMinServo(FINGERS) );
    DebugPrint(F("MaxFingers = ")); 
    DebugPrintln( this->hand->eeprom.GetMaxServo(FINGERS) );

    DebugPrint(F("MinThumb = ")); 
    DebugPrintln( this->hand->eeprom.GetMinServo(THUMB) );
    DebugPrint(F("MaxThumb = ")); 
    DebugPrintln( this->hand->eeprom.GetMaxServo(THUMB) );

    this->hand->stopServosCalibration();
}

void Routine_calibration_servos::calibration()
{   
    switch(this->_currentStep)
    {
        // STEP 1 :THUMB CALIBRATION
        case THUMB_CLOSE :
        case THUMB_OPEN :
            if (this->hand->buttons.isCalibButtonPressed())
            {
                this->hand->servos.forceRelativeClose(THUMB,STEP);
            }
            else if (this->hand->buttons.isThumbButtonPressed())
            {
                this->hand->servos.forceRelativeOpen(THUMB,STEP);
            }
        break;

        // STEP 2 :INDEX CALIBRATION
        case INDEX_CLOSE :
        case INDEX_OPEN :
            if (this->hand->buttons.isCalibButtonPressed())
            {
                this->hand->servos.forceRelativeClose(INDEX,STEP);
            }
            else if (this->hand->buttons.isThumbButtonPressed())
            {
                this->hand->servos.forceRelativeOpen(INDEX,STEP);
            }
        break;

        // STEP 3 :FINGERS CALIBRATION
        case FINGERS_CLOSE :
        case FINGERS_OPEN :
            if (this->hand->buttons.isCalibButtonPressed())
            {
                this->hand->servos.forceRelativeClose(FINGERS,STEP);
            }
            else if (this->hand->buttons.isThumbButtonPressed())
            {
                this->hand->servos.forceRelativeOpen(FINGERS,STEP);
            }
        break;

        default:break;
    }
}

/**
 * Save current calibration parameters before the next step enabling
 */
void Routine_calibration_servos::SaveParamBeforeNextStep()
{
    switch(this->_currentStep)
    {
        case INDEX_CLOSE :
            this->limIndex[0] = this->hand->servos.getPosition(INDEX);
            DebugPrint(F("Save Index : "));
            DebugPrintln(this->limIndex[0]);
        break;

        case INDEX_OPEN :
            this->limIndex[1] = this->hand->servos.getPosition(INDEX);
            DebugPrint(F("Save Index : "));
            DebugPrintln(this->limIndex[1]);
        break;

        case FINGERS_CLOSE :
            this->limFingers[0] = this->hand->servos.getPosition(FINGERS);
            DebugPrint(F("Save Fingers : "));
            DebugPrintln(this->limFingers[0]);
        break;

        case FINGERS_OPEN :
            this->limFingers[1] = this->hand->servos.getPosition(FINGERS);
            DebugPrint(F("Save Fingers : "));
            DebugPrintln(this->limFingers[1]);
        break;

        case THUMB_CLOSE :
            this->limThumb[0] = this->hand->servos.getPosition(THUMB);
            DebugPrint(F("Save Thumb : "));
            DebugPrintln(this->limThumb[0]);
        break;

        case THUMB_OPEN :
            this->limThumb[1] = this->hand->servos.getPosition(THUMB);
            DebugPrint(F("Save Thumb : "));
            DebugPrintln(this->limThumb[1]);
        break;

        default:break;
    }
}

void Routine_calibration_servos::SaveServoParam(int member, unsigned char lim1, unsigned char lim2)
{
    unsigned char min = (lim1 < lim2) ? lim1:lim2;
    unsigned char max = (lim1 < lim2) ? lim2:lim1;

    this->hand->eeprom.SetMinServo(member,min);
    this->hand->eeprom.SetMaxServo(member,max);

    this->hand->servos.setLimitPositions(member,min,max);
}

void Routine_calibration_servos::EndCalibServos()
{
    this->SaveServoParam(THUMB,this->limThumb[0],this->limThumb[1]);
    this->SaveServoParam(INDEX,this->limIndex[0],this->limIndex[1]);
    this->SaveServoParam(FINGERS,this->limFingers[0],this->limFingers[1]);
}