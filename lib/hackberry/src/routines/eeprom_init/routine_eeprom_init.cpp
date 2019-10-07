/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Routine used to retrieve  parameters from eeprom and affect them to drivers 
 *  Remark : this routine is designed to be used in setup only ! do not loop it ! 
 *  
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "routine_eeprom_init.h"

Routine_eeprom_init::Routine_eeprom_init()
{

}

void Routine_eeprom_init::init(Hackberry_hand *hand)
{
    this->hand = hand;

    // Initialization of eeprom memory

    // Magic Word
    if (!this->hand->eeprom.IsMagicWordCorrect())
    {
        this->hand->eeprom. loadDefaultParameters();
    }

    // Software Version
    this->hand->eeprom.SetVersion(MAJOR_VERSION,MINOR_VERSION,PATCH_VERSION);

    // Servomotors
    this->initHand();
    this->initServos(THUMB);
    this->initServos(INDEX);
    this->initServos(FINGERS);

    // Sensor
    this->initSensor();
}

/**
 * Initialize the sensor parameters with the eeprom content
 */
void Routine_eeprom_init::initSensor()
{
    unsigned char sensorType = this->hand->eeprom.GetSensorType();
    int sensorMin = this->hand->eeprom.GetSensorMin();
    int sensorMax = this->hand->eeprom.GetSensorMax();

    this->hand->sensor.setSensorType(sensorType);
    this->hand->sensor.calibrate(sensorMin,sensorMax);
}

/**
 * Initialize the hand parameters with the eeprom content
 */
void Routine_eeprom_init::initHand()
{
    bool hand = this->hand->eeprom.GetHand();
    this->hand->servos.setHand(hand);
}

/**
 * Initialize the servomotors parameters with the eeprom content
 */
void Routine_eeprom_init::initServos(unsigned char member)
{
    unsigned char servoMin = this->hand->eeprom.GetMinServo(member);
    unsigned char servoMax = this->hand->eeprom.GetMaxServo(member);
    this->hand->servos.setLimitPositions(member,servoMin,servoMax);
}


