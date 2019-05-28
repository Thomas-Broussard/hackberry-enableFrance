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
Hackberry_sensor::Hackberry_sensor(int pin)
{
    this->pin1 = pin;
}

Hackberry_sensor::Hackberry_sensor(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
}

Hackberry_sensor::Hackberry_sensor(int pin1, int pin2, int pin3)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
}


void Hackberry_sensor::init(int sensorType)
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
    long result = this->_sensor->read();

    if (this->_gain != 1){
        result *= this->_gain;
    }

    if (this->_offset != 1){
        result += this->_offset;
    }
    return result;
}

/**
 * Perform a sensor reading by averaging the result on 16 consecutive points
 * 
 * @return average value of the sensor on 16 consecutive acquisitions
 */
int Hackberry_sensor::readAverage()
{
    long result = this->_sensor->readAverage();

    if (this->_gain != 1){
        result *= this->_gain;
    }

    if (this->_offset != 1){
        result += this->_offset;
    }
    return result;
}

void Hackberry_sensor::calibrate(float gain, int offset)
{
    this->_gain = gain;
    this->_offset = offset;
}


void Hackberry_sensor::setSensorType(int sensorType)
{
    this->_sensorType = sensorType;
    switch(sensorType)
    {
        case TYPE_IR_SENSOR:
            this->_sensor = new IRSensor(pin1);
        break;

        case TYPE_EMG_SENSOR:
            this->_sensor = new IRSensor(pin1);
        break;

        default:
        break;
    }
}

