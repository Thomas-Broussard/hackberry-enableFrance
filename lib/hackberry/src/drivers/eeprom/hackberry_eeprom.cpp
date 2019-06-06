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

    // initialization of eeprom memory
    if (!this->IsMagicWordCorrect())
    {
        this->SetDefault();
    }
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
 * @param gain sensor gain value (1.00 by default)
 */
void Hackberry_eeprom::SetSensorGain(float gain)
{
    this->eepromUtils->writeFloat(ADDR(sensorGain),gain);
}

/**
 * Get the sensor gain saved in the eeprom 
 * @return sensor gain value (1.00 by default)
 */
float Hackberry_eeprom::GetSensorGain()
{
    return this->eepromUtils->readFloat(ADDR(sensorGain));
}

/**
 * Save the sensor offset in the eeprom 
 * @param offset sensor offset value (0 by default)
 */
void Hackberry_eeprom::SetSensorOffset(int offset)
{
    this->eepromUtils->writeInt(ADDR(sensorOffset),offset);
}

/**
 * Get the sensor offset saved in the eeprom 
 * @return sensor offset value (0 by default)
 */
int Hackberry_eeprom::GetSensorOffset()
{
    return this->eepromUtils->readInt(ADDR(sensorOffset));
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
    Serial.print("SensorGain   |   ");    Serial.println( ADDR(sensorGain));
    Serial.print("SensorOffset |   ");    Serial.println( ADDR(sensorOffset));
    
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
    Serial.print("SensorGain    = "); Serial.println( this->GetSensorGain() );
    Serial.print("SensorOffset  = "); Serial.println( this->GetSensorOffset() );
    
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


/**
 * Save the default parameters in the eeprom 
 * Remark : This function is mainly called when the magic word is incorrect, to reformat the eeprom memory.
 */
void Hackberry_eeprom::SetDefault()
{
    this->SetHand(RIGHT_HAND);

    this->SetMinServo(THUMB,THUMB_MIN);  
    this->SetMaxServo(THUMB,THUMB_MAX);

    this->SetMinServo(INDEX,INDEX_MIN);  
    this->SetMaxServo(INDEX,INDEX_MAX);

    this->SetMinServo(FINGERS,FINGERS_MIN);
    this->SetMaxServo(FINGERS,FINGERS_MAX);

    this->SetSensorType(TYPE_IR_SENSOR);
    this->SetSensorGain(1.00);
    this->SetSensorOffset(0);

    this->SetMagicWord();
}