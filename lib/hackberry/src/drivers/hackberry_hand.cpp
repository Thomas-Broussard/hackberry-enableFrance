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
    buttons(PIN_BUTTON_CALIB , PIN_BUTTON_EXTRA , PIN_BUTTON_THUMB , PIN_BUTTON_LOCK),
    servos(PIN_INDEX , PIN_THUMB , PIN_FINGERS),
    sensor(PIN_SENSOR_1 , PIN_SENSOR_2),
    battery(PIN_BATTERY),
    bluetooth(PIN_RX , PIN_TX , PIN_POWER),
    eeprom()
{}

/**
 * Initialize the Hackberry Hand
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry_hand::init()
{
    // Drivers
    this->servos.init();
    this->buttons.init();
    this->sensor.init();
    this->bluetooth.init();
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