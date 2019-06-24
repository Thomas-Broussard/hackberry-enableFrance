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
#include "hackberry.h"


/**
 * Constructor : map all the IOs to drivers
 */
Hackberry::Hackberry() : 
    hand(),
    routine()
{}

/**
 * Constructor : initialize the hand and all the drivers
 */
void Hackberry::init()
{
    this->hand.init();
    this->initSpecificDrivers();
    this->routine.init(&this->hand);
    this->printSignature();
}

/**
 * Constructor : initialize the hand and all the drivers
 * 
 * @param selectedHand hand type (RIGHT_HAND or LEFT_HAND)
 * @param sensorType type of the sensor used
 */
void Hackberry::init(bool selectedHand,int sensorType)
{
    this->init();
    this->setHand(selectedHand);
    this->setSensorType(sensorType);
}

/**
 * Set the hand type
 * 
 * @param selectedHand hand type (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry::setHand(bool selectedHand)
{
    this->hand.servos.setHand(selectedHand);
    this->hand.eeprom.SetHand(selectedHand);
}


/**
 * Set the sensor type
 * 
 * @param sensorType type of the sensor used
 */
void Hackberry::setSensorType(int sensorType)
{
    this->hand.sensor.setSensorType(sensorType);
    this->hand.eeprom.SetSensorType(sensorType);
}

/**
 * Initialize specific drivers depending on mapping version or extension board
 * 
 */
void Hackberry::initSpecificDrivers()
{
    #ifdef BATTERY_MONITORING_ENABLED
        this->hand.battery.init(PIN_BATTERY);
    #endif

    #ifdef BLUETOOTH_ENABLED
        this->hand.bluetooth.init(PIN_RX_BT,PIN_TX_BT,PIN_POWER_BT);
    #endif
}


void Hackberry::printSignature()
{
    DebugPrintln(F("-------------------------------------"));
    DebugPrintln((String)"Hackberry Library - Version " + MAJOR_VERSION + "." + MINOR_VERSION + "." + PATCH_VERSION);
    DebugPrintln(F("Author : Thomas Broussard "));
    DebugPrintln(F("-------------------------------------"));
}
