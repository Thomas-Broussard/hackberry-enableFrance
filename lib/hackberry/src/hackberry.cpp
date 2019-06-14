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


void Hackberry::init()
{
    this->hand.init();
    this->initSpecificDrivers();
    this->routine.init(&this->hand);
    this->initExtension();
}

void Hackberry::init(bool selectedHand,int sensorType)
{
    this->init();
    this->setHand(selectedHand);
    this->setSensorType(sensorType);
}

void Hackberry::setHand(bool selectedHand)
{
    this->hand.servos.setHand(selectedHand);
    this->hand.eeprom.SetHand(selectedHand);
}

void Hackberry::setSensorType(int sensorType)
{
    this->hand.sensor.setSensorType(sensorType);
    this->hand.eeprom.SetSensorType(sensorType);
}

/* 
* =============================================================================================================================================
*                                  EXTENSION BOARDS
* =============================================================================================================================================
*/
void Hackberry::initSpecificDrivers()
{
     // Mk3 Specific Drivers
    #ifdef MAPPING_MK3
        this->hand.battery.init(PIN_BATTERY);
    #endif
}


void Hackberry::initExtension()
{
    // Extension GPIO : Board with header pin to use GPIOs with wires and breadboard (for prototyping)
    #if defined(EXTENSION_GPIO)

    // Extension Bluetooth : Board with bluetooth module to communicate with other devices
    #elif defined(EXTENSION_BLUETOOTH)
    this->hand.bluetooth.init(PIN_RX,PIN_TX,PIN_POWER);

    // Extension Leds : Board with leds to indicate status
    #elif defined(EXTENSION_LEDS)

    // undefined or unknown extension board
    #else 
        
    
    #endif
}

