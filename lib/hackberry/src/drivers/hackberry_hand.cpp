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

// Mode Calibration (for sensors)
bool Hackberry_hand::isCalibrationEnabled()
{
    return this->isCalib;
}

unsigned long Hackberry_hand::getCalibrationTime()
{
    return this->CalibrationTime;
}

void Hackberry_hand::startCalibration()
{
    Serial.println("Start Calibration");
    this->CalibrationTime = millis();
    this->isCalib = true;
}

void Hackberry_hand::stopCalibration()
{
    Serial.println("Stop Calibration");
    this->CalibrationTime = 0;
    this->isCalib = false;
}



