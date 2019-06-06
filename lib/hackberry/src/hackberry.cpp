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
    this->routine.init(&this->hand);
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



