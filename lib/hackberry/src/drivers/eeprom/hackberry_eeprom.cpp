/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library used to read and write content in EEPROM memory 
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "hackberry_eeprom.h"

/**
 * Constructor of the EEPROM driver (no pins required)
 */
Hackberry_eeprom::Hackberry_eeprom()
{
    this->eepromUtils = new EEPROMUtils();
}

/**
 * Save the hand type in the eeprom 
 * @param hand RIGHT_HAND or LEFT_HAND
 */
void Hackberry_eeprom::SetHand(bool hand)
{
    if (hand == RIGHT_HAND){
        this->eepromUtils->writeChar(ADDR(selectedHand),'1');
    }
    else if (hand == LEFT_HAND){
        this->eepromUtils->writeChar(ADDR(selectedHand),'0');
    }
}


/**
 * Get the hand type saved in the eeprom 
 * @return RIGHT_HAND or LEFT_HAND
 */
bool Hackberry_eeprom::GetHand()
{
    return (this->eepromUtils->readChar(ADDR(selectedHand)) == '1') ? RIGHT_HAND : LEFT_HAND;
}


/**
 * Save the minimum position of a servomotor in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @param value minimum position (between 0 and 180 degrees)
 */
void Hackberry_eeprom::SetMinServo(int member, int value)
{
    switch(member)
    {
        case THUMB : this->eepromUtils->writeChar(ADDR(thumbMin),(char)value);
        break;
        case INDEX : this->eepromUtils->writeChar(ADDR(indexMin),(char)value);
        break;
        case FINGERS: this->eepromUtils->writeChar(ADDR(fingersMin),(char)value);
        break;
    }
}

/**
 * Save the maximum position of a servomotor in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @param value maxmimum position (between 0 and 180 degrees)
 */
void Hackberry_eeprom::SetMaxServo(int member, int value)
{
    switch(member)
    {
        case THUMB : this->eepromUtils->writeChar(ADDR(thumbMax),(char)value);
        break;
        case INDEX : this->eepromUtils->writeChar(ADDR(indexMax),(char)value);
        break;
        case FINGERS: this->eepromUtils->writeChar(ADDR(fingersMax),(char)value);
        break;
    }
}

/**
 * Get the minimum position of a servomotor saved in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @return minimum position (between 0 and 180 degrees)
 */
int Hackberry_eeprom::GetMinServo(int member)
{
    switch(member)
    {
        case THUMB :  return (unsigned char)this->eepromUtils->readChar(ADDR(thumbMin));
        break;
        case INDEX :  return (unsigned char)this->eepromUtils->readChar(ADDR(indexMin));
        break;
        case FINGERS: return (unsigned char)this->eepromUtils->readChar(ADDR(fingersMin));
        break;
        default: return -2;
        break;
    }
}

/**
 * Get the maximum position of a servomotor saved in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @return maximum position (between 0 and 180 degrees)
 */
int Hackberry_eeprom::GetMaxServo(int member)
{
    switch(member)
    {
        case THUMB :  return (unsigned char)this->eepromUtils->readChar(ADDR(thumbMax));
        break;
        case INDEX :  return (unsigned char)this->eepromUtils->readChar(ADDR(indexMax));
        break;
        case FINGERS: return (unsigned char)this->eepromUtils->readChar(ADDR(fingersMax));
        break;
        default: return -2;
        break;
    }
}


/**
 * Save the sensor type in the eeprom 
 * @param type type of the sensor (TYPE_IR_SENSOR , TYPE_EMG_SENSOR, etc..)
 */
void Hackberry_eeprom::SetSensorType(int type)
{
    this->eepromUtils->writeChar(ADDR(sensorType),(char)type);
}

/**
 * Get the sensor type saved in the eeprom 
 * @return type of the sensor (TYPE_IR_SENSOR , TYPE_EMG_SENSOR, etc..)
 */
int Hackberry_eeprom::GetSensorType()
{
    return this->eepromUtils->readChar(ADDR(sensorType));
}

/**
 * Save the sensor gain in the eeprom 
 * @param gain sensor gain value (1023 by default)
 */
void Hackberry_eeprom::SetSensorMin(int value)
{
    this->eepromUtils->writeInt(ADDR(sensorMin),value);
}

/**
 * Get the sensor gain saved in the eeprom 
 * @return sensor gain value (1023 by default)
 */
int Hackberry_eeprom::GetSensorMin()
{
    return this->eepromUtils->readInt(ADDR(sensorMin));
}

/**
 * Save the sensor offset in the eeprom 
 * @param offset sensor offset value (0 by default)
 */
void Hackberry_eeprom::SetSensorMax(int value)
{
    this->eepromUtils->writeInt(ADDR(sensorMax),value);
}

/**
 * Get the sensor offset saved in the eeprom 
 * @return sensor offset value (0 by default)
 */
int Hackberry_eeprom::GetSensorMax()
{
    return this->eepromUtils->readInt(ADDR(sensorMax));
}

/**
 * Display the memory map on the serial monitor (debug usage only)
 */
void Hackberry_eeprom::printMemoryMap()
{
    Serial.println("=========================");
    Serial.println("      EEPROM MAPPING");
    Serial.println("=========================");
    Serial.println("Variable     | Address(dec)");
    Serial.println("-----------------------");
    
    Serial.print("Hand         |   ");    Serial.println( ADDR(selectedHand));

    Serial.print("MinThumb     |   ");    Serial.println( ADDR(thumbMin));
    Serial.print("MinIndex     |   ");    Serial.println( ADDR(indexMin));
    Serial.print("MinFingers   |   ");    Serial.println( ADDR(fingersMin));

    Serial.print("MaxThumb     |   ");    Serial.println( ADDR(thumbMax));
    Serial.print("MaxIndex     |   ");    Serial.println( ADDR(indexMax));
    Serial.print("MaxFingers   |   ");    Serial.println( ADDR(fingersMax));

    Serial.print("SensorType   |   ");    Serial.println( ADDR(sensorType));
    Serial.print("SensorMin    |   ");    Serial.println( ADDR(sensorMin));
    Serial.print("SensorMax    |   ");    Serial.println( ADDR(sensorMax));
    
    Serial.println("=========================");
    Serial.println("=========================");
}


/**
 * Display the memory content on the serial monitor (debug usage only)
 */
void Hackberry_eeprom::printMemoryContent()
{
    Serial.println("=========================");
    Serial.println("      EEPROM CONTENT");
    Serial.println("=========================");

    Serial.print("Hand          = "); Serial.println( this->GetHand() == RIGHT_HAND ? "RIGHT_HAND":"LEFT_HAND");

    Serial.print("MinThumb      = "); Serial.println( this->GetMinServo(THUMB) );
    Serial.print("MinIndex      = "); Serial.println( this->GetMinServo(INDEX) );
    Serial.print("MinFingers    = "); Serial.println( this->GetMinServo(FINGERS) );

    Serial.print("MaxThumb      = "); Serial.println( this->GetMaxServo(THUMB) );
    Serial.print("MaxIndex      = "); Serial.println( this->GetMaxServo(INDEX) );
    Serial.print("MaxFingers    = "); Serial.println( this->GetMaxServo(FINGERS) );


    Serial.print("SensorType    = "); Serial.println( this->GetSensorType() );
    Serial.print("Sensormin     = "); Serial.println( this->GetSensorMin() );
    Serial.print("SensorMax     = "); Serial.println( this->GetSensorMax() );
    
    Serial.println("=========================");
    Serial.println("=========================");
}




/* 
* =============================================================================================================================================
*                                  PRIVATE FUNCTIONS
* =============================================================================================================================================
*/

/**
 * Save the magic word in the eeprom 
 * Remark : The magic word is a predefined code save at the beginning of the eeprom memory.
 * It is used to check if the memory had been previously initialized or not.
 */
void Hackberry_eeprom::SetMagicWord()
{
    this->eepromUtils->writeFloat(ADDR(magicWord),MAGIC_WORD);
}

/**
 * Check if the Magic Word is present in eeprom memory or not
 * Remark : The magic word is a predefined code save at the beginning of the eeprom memory.
 * It is used to check if the memory had been previously initialized or not.
 * 
 * @return true if correct. false otherwise
 */
bool Hackberry_eeprom::IsMagicWordCorrect()
{
    return (this->eepromUtils->readFloat(ADDR(magicWord)) == MAGIC_WORD);
}