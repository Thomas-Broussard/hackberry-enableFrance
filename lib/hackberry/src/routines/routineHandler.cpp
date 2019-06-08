/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Handle all the routines of the hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * 
 * =============================================================================================================================================
 */
#include "routineHandler.h"


/**
 * Constructor : instantiate all routines
 */
RoutineHandler::RoutineHandler() : 
    bluetooth(),
    buttons(),
    moves(),
    batteryMonitoring(),
    eeprom_init(),
    calibration_sensor()
{}


void RoutineHandler::init(Hackberry_hand *hand)
{
    this->calibration_sensor.init(hand);
    this->bluetooth.init(hand);
    this->buttons.init(hand);
    this->moves.init(hand);
    this->batteryMonitoring.init(hand);
    this->eeprom_init.init(hand);
    
}
