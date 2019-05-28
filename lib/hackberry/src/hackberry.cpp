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
void Hackberry::begin(bool selectedHand, int sensorType, bool enableDebug)
{
    // Drivers
    this->servos.init(selectedHand);
    this->buttons.init();
    this->sensor.init(TYPE_IR_SENSOR);

    // COM
    //this->debug.init(enableDebug , this->sensor,this->servos,this->buttons);
    this->bluetooth.init(this->sensor,this->servos,this->buttons);
}




