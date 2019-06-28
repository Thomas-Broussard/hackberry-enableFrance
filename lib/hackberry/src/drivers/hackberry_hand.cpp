
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
    #ifdef MAPPING_MK2
        this->servos.init(PIN_INDEX , PIN_THUMB , PIN_FINGERS);
    #endif
    #ifdef MAPPING_MK3
        this->servos.init(PIN_INDEX , PIN_THUMB , PIN_FINGERS, PIN_MEASURE_INDEX , PIN_MEASURE_FINGERS);
    #endif
    
    this->buttons.init(PIN_BUTTON_CALIB , PIN_BUTTON_EXTRA , PIN_BUTTON_THUMB , PIN_BUTTON_LOCK);
    this->sensor.init(PIN_SENSOR_1);

    // init specific drivers
    #ifdef BATTERY_MONITORING_ENABLED
        this->hand.battery.init(PIN_BATTERY);
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


/* 
* =============================================================================================================================================
*                                  Sensor Calibration mode only
* =============================================================================================================================================
*/
unsigned long Hackberry_hand::getSensorCalibrationTime()
{
    return this->CalibrationSensor_Time;
}

void Hackberry_hand::startSensorCalibration()
{
    this->CalibrationSensor_Time = millis();
    this->setMode(SensorCalibration);
}

void Hackberry_hand::stopSensorCalibration()
{
    this->CalibrationSensor_Time = 0;
    this->setMode(Standard);
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

void Hackberry_hand::startServosCalibration()
{
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
    this->setMode(Standard);
}