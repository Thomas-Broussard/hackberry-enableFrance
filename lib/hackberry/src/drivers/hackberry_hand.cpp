
/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library to simplify the use of the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "hackberry_hand.h"

/**
 * Constructor : map all the IOs to drivers
 */
Hackberry_hand::Hackberry_hand() : 

    // Main Drivers
    buttons(),
    servos(),
    sensor(),
    eeprom(),

    // Specific Drivers
    battery()
{}

/**
 * Initialize the Hackberry Hand
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry_hand::init()
{
    // Initialize main drivers
    
    #if HACKBERRY_BOARD <= MK2
        //TODO paramètrer présence extension controle courant ?
        this->servos.init(PIN_INDEX , PIN_THUMB , PIN_FINGERS, PIN_MEASURE_INDEX , PIN_MEASURE_FINGERS);
       //this->servos.init(PIN_INDEX , PIN_THUMB , PIN_FINGERS);
    #elif HACKBERRY_BOARD >= MK3
        this->servos.init(PIN_INDEX , PIN_THUMB , PIN_FINGERS, PIN_MEASURE_INDEX , PIN_MEASURE_FINGERS);
    #endif
    
    this->buttons.init(PIN_BUTTON_CALIB , PIN_BUTTON_EXTRA , PIN_BUTTON_THUMB , PIN_BUTTON_LOCK);
    this->sensor.init(PIN_SENSOR_1);

    // init specific drivers
    #ifdef BATTERY_MONITORING_ENABLED
        this->battery.init(PIN_BATTERY);
    #endif
}

// Get Mode
Hackberry_Mode Hackberry_hand::getMode()
{
    return this->_mode;
}

void Hackberry_hand::setMode(Hackberry_Mode mode)
{
    this->_mode = mode;
}

void Hackberry_hand::enableMoves(bool enable)
{
    this->_movesEnabled = enable;
}

bool Hackberry_hand::isMovesEnabled()
{
    return this->_movesEnabled;
}


/* 
* =============================================================================================================================================
*                                  Sensor Calibration mode only
* =============================================================================================================================================
*/
unsigned long Hackberry_hand::getSensorCalibrationTime()
{
    return this->CalibrationSensor_Time;
}

void Hackberry_hand::startSensorCalibration(Hackberry_Mode modeAfterCalib)
{
    this->_nextMode = modeAfterCalib;
    this->CalibrationSensor_Time = millis();
    this->setMode(SensorCalibration);
}

void Hackberry_hand::stopSensorCalibration()
{
    this->CalibrationSensor_Time = 0;
    this->setMode(this->_nextMode);
}




/* 
* =============================================================================================================================================
*                                  Servos Calibration mode only
* =============================================================================================================================================
*/
unsigned int Hackberry_hand::getServosCalibrationStep()
{
    return this->CalibrationServos_Step;
}

void Hackberry_hand::startServosCalibration(Hackberry_Mode modeAfterCalib)
{
    this->_nextMode = modeAfterCalib;
    this->CalibrationServos_Step = 1;
    this->setMode(ServosCalibration);
}

void Hackberry_hand::nextServosCalibration()
{
    this->CalibrationServos_Step++;
}

void Hackberry_hand::stopServosCalibration()
{
    this->CalibrationServos_Step = 0;
    this->setMode(this->_nextMode);
}