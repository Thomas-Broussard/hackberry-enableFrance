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


void Hackberry_sensor::init(unsigned char pin1, unsigned char pin2, unsigned char pin3)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;

    this->setSensorType(DEFAULT_SENSOR);
}


/**
 * read the value of the sensor
 * 
 * @return sensor value read
 */
int Hackberry_sensor::read()
{
    int rawValue = this->_sensor->read();
    int value = map(rawValue, this->_sensorMin, this->_sensorMax, MIN_ADC , MAX_ADC);
    return constrain(value,MIN_ADC,MAX_ADC);
}

int Hackberry_sensor::readRaw()
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
    int rawValue = this->_sensor->readAverage();
    int value = map(rawValue, this->_sensorMin, this->_sensorMax, MIN_ADC , MAX_ADC);
    return constrain(value,MIN_ADC,MAX_ADC);
}

int Hackberry_sensor::readRawAverage()
{
    return this->_sensor->readAverage();
}

void Hackberry_sensor::calibrate(int sensorMin, int sensorMax)
{
    this->_sensorMin = sensorMin;
    this->_sensorMax = sensorMax;
}


void Hackberry_sensor::setSensorType(unsigned char sensorType)
{
    this->_sensorType = sensorType;
    switch(sensorType)
    {
        case TYPE_IR_SENSOR:
            this->_sensor = new IRSensor(pin1);
        break;

        case TYPE_EMG_SENSOR:
            //this->_sensor = new IRSensor(pin1);
        break;

        default:
        break;
    }
}

