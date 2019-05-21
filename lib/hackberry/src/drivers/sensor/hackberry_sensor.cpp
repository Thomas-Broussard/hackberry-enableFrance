/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for reading the Hackberry Hand Sensor
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "hackberry_sensor.h"


/**
 * Constructor
 * 
 */
Hackberry_sensor::Hackberry_sensor()
{
}

void Hackberry_sensor::init(bool selectedHand, int sensorType)
{
    this->setSensorType(sensorType);
}


/**
 * read the value of the sensor
 * 
 * @return sensor value read
 */
int Hackberry_sensor::read()
{
    return this->_sensor->read();
}

/**
 * Perform a sensor reading by averaging the result on 16 consecutive points
 * 
 * @return average value of the sensor on 16 consecutive acquisitions
 */
int Hackberry_sensor::readAverage()
{
    return this->_sensor->readAverage();
}

void Hackberry_sensor::calibrate()
{
    this->_sensor->calibrate();
}


void Hackberry_sensor::setSensorType(int sensorType)
{
    this->_sensorType = sensorType;
    switch(sensorType)
    {
        case STANDARD_IR_SENSOR:
            this->_sensor = new IRSensor(A1);
        break;

        default:
        break;
    }
}

