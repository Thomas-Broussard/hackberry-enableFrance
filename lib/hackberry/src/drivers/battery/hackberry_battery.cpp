/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for monitoring the Hackberry Hand Battery
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "hackberry_battery.h"

/**
 * Constructor of the Battery driver
 * 
 * @param pinBattery analog input - pin of the battery monitoring system
 */
Hackberry_battery::Hackberry_battery(unsigned char pinBattery)
{
    this->_pinBattery = pinBattery;
}

void Hackberry_battery::init()
{ 
    pinMode(this->_pinBattery, INPUT);
}

/**
 * read the level of the battery monitor
 * 
 * @return lvl of battery (between 0 and 100%)
 */
unsigned char Hackberry_battery::read()
{
    unsigned int rawValue = this->readRawValue();
    unsigned char value = map(rawValue, ADC_BAT_MIN, ADC_BAT_MAX, 0 , 100);
    return constrain(value, 0, 100);
}

/**
 * Perform a battery monitor reading by averaging the result on 16 consecutive points
 * 
 * @return average level of the battery (between 0 and 100%) on 16 consecutive acquisitions
 */
unsigned char Hackberry_battery::readAverage()
{
    unsigned int rawValue = this->readRawAverage();
    unsigned char value = map(rawValue, ADC_BAT_MIN, ADC_BAT_MAX, 0 , 100);
    return constrain(value , 0, 100); 
}



/**
 * read the raw value of the battery monitor
 * 
 * @return raw value read (between 0 and 1023)
 */
int Hackberry_battery::readRawValue()
{
    return analogRead(_pinBattery);
}

/**
 * Perform a raw battery monitor reading by averaging the result on 16 consecutive points
 * 
 * @return average raw value of the battery monitor on 16 consecutive acquisitions
 */
int Hackberry_battery::readRawAverage()
{
   int result = 0; 
    for (int i = 0; i < 16; i++) 
    {
        result += this->readRawValue();
    }
    return (result >> 4);
}
