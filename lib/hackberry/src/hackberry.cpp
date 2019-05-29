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


void Hackberry::init(bool selectedHand, int sensorType)
{
    this->hand.init(selectedHand,sensorType);
    this->routine.init(this->hand);
}



