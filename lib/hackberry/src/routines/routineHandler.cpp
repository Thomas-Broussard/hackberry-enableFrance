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
    batteryMonitoring()
{}


void RoutineHandler::init(Hackberry_hand hand)
{
    this->bluetooth.init(hand);
    this->buttons.init(hand);
    this->moves.init(hand);
    this->batteryMonitoring.init(hand);
}
