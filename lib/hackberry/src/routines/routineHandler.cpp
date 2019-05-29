/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Routine for Hackberry bluetooth communication
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "routineHandler.h"


/**
 * Constructor : map all the IOs to drivers
 */
RoutineHandler::RoutineHandler() : 
    bluetooth()
{}


void RoutineHandler::init(Hackberry_hand hand)
{
    this->bluetooth.init(hand);
}