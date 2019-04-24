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


/**
 * Initialize sensor driver
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 * @param sensorType Type of sensor used to read the muscle activity
 */
void Hackberry_sensor::init(bool selectedHand, int sensorType)
{
    this->_sensorType = sensorType;

    switch(sensorType)
    {
        case STANDARD_IR_SENSOR:
            this->_pinSensor = A1;  
            pinMode(_pinSensor, INPUT);
        break;

        default:
        break;
    }
}

/**
 * read the value of the sensor
 * 
 * @return sensor value read
 */
int Hackberry_sensor::read()
{
    switch(_sensorType)
    {
        case STANDARD_IR_SENSOR: 
            return analogRead(_pinSensor);
        break;
        default:
            return -1; // error code
        break;
    }
}



/**
 * Perform a sensor reading by averaging the result on 16 consecutive points
 * 
 * @return average value of the sensor on 16 consecutive acquisitions
 */
int Hackberry_sensor::readAverage()
{
    int result = 0; 

    for (int i = 0; i < 16; i++) 
    {
        result += this->read();
    }
    return (result >> 4);
}
