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
    calibration_sensor(),
    calibration_servos()
{}


void RoutineHandler::init(Hackberry_hand *hand)
{
    // main routines
    this->eeprom_init.init(hand);
    this->buttons.init(hand);
    this->moves.init(hand);
    this->calibration_sensor.init(hand);
    this->calibration_servos.init(hand);

    // routine with specific drivers only
    #ifdef BATTERY_MONITORING_ENABLED
        this->batteryMonitoring.init(hand);
    #endif

    #ifdef BLUETOOTH_ENABLED
        this->bluetooth.init(hand);
    #endif
}
