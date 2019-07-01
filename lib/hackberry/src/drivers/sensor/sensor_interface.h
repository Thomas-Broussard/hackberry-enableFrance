/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Interface for different sensor type reading
 *  
 *  You can define your own sensor (see template at the end of the code)
 *  
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __SENSOR_INTERFACE_H__
#define __SENSOR_INTERFACE_H__

// Dependencies
#include <Arduino.h>

/* 
 * =============================================================================================================================================
 *                                                      SENSOR INTERFACE
 * =============================================================================================================================================
 */
class ISensor
{
    public:
        ISensor(){}

        // Common methods
        int readAverage()
        {
            int result = 0; 
            for (int i = 0; i < 16; i++) 
            {
                result += this->read();
            }
            return (result >> 4);
        }

        virtual int read();
};


/* 
 * =============================================================================================================================================
 *                                                      ANALOG SENSOR
 * =============================================================================================================================================
 */
class AnalogSensor : public ISensor
{
    public:
        AnalogSensor(unsigned char pin)
        {
            this->_pinSensor = pin;  
            pinMode(_pinSensor, INPUT);
        }

        int read()
        {
            return analogRead(_pinSensor);
        }

    private:
        unsigned char _pinSensor;  
};


/* 
 * =============================================================================================================================================
 *                                                      <SENSOR NAME>
 * =============================================================================================================================================
 */

/*
// replace SensorName by the name of your Sensor
class SensorName : public ISensor
{
    public:
        SensorName()
        {
            // set sensor pins here
        }

        int read()
        {
            // do stuff here
        }

    private:
        // reference sensor pins here
};
*/


#endif
