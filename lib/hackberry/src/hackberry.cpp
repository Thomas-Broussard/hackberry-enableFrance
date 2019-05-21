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
 * Constructor
 */
Hackberry::Hackberry()
{
    this->buttons  = Hackberry_buttons();
    this->servos   = Hackberry_servos();
    this->sensor   = Hackberry_sensor();
    this->debug    = Hackberry_debug();
    this->bluetooth= Hackberry_bluetooth();
}

/**
 * Initialize the Hackberry Hand
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry::begin(bool selectedHand)
{
    // Drivers
    this->servos.init(selectedHand);
    this->buttons.init(selectedHand);
    this->sensor.init(selectedHand,STANDARD_IR_SENSOR);

    // COM
    this->debug.init(true , this->sensor,this->servos,this->buttons);
    this->bluetooth.init(this->sensor,this->servos,this->buttons);
}

/**
 * Initialize the Hackberry Hand
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 * @param enableDebug set to true to enable debug printing on serial monitor
 */
void Hackberry::begin(bool selectedHand, bool enableDebug)
{
    // Drivers
    this->servos.init(selectedHand);
    this->buttons.init(selectedHand);
    this->sensor.init(selectedHand,STANDARD_IR_SENSOR);

    // COM
    this->debug.init(enableDebug , this->sensor,this->servos,this->buttons);
    this->bluetooth.init(this->sensor,this->servos,this->buttons);
}

/**
 * Initialize the Hackberry Hand
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 * @param sensorType Type of sensor used to read the muscle activity
 */
void Hackberry::begin(bool selectedHand, int sensorType)
{
    // Drivers
    this->servos.init(selectedHand);
    this->buttons.init(selectedHand);
    this->sensor.init(selectedHand,sensorType);

    // COM
    this->debug.init(true , this->sensor,this->servos,this->buttons);
    this->bluetooth.init(this->sensor,this->servos,this->buttons);
}



