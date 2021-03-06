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
        this->eepromUtils->writeChar(ADDR(selectedHand),0x01);
    }
    else if (hand == LEFT_HAND){
        this->eepromUtils->writeChar(ADDR(selectedHand),0x02);
    }
}


/**
 * Get the hand type saved in the eeprom 
 * @return RIGHT_HAND or LEFT_HAND
 */
bool Hackberry_eeprom::GetHand()
{
    return (this->eepromUtils->readChar(ADDR(selectedHand)) == 0x01) ? RIGHT_HAND : LEFT_HAND;
}

void Hackberry_eeprom::ChangeHand()
{
    bool currentHand = this->GetHand();
    this->SetHand( (currentHand == RIGHT_HAND) ? LEFT_HAND : RIGHT_HAND );
}


void Hackberry_eeprom::SetVersion(unsigned char major, unsigned char minor, unsigned char patch)
{
    this->eepromUtils->writeChar(ADDR(majorVersion),major);
    this->eepromUtils->writeChar(ADDR(minorVersion),minor);
    this->eepromUtils->writeChar(ADDR(patchVersion),patch);
}


void Hackberry_eeprom::GetVersion(unsigned char *major, unsigned char *minor, unsigned char *patch)
{
    *major = this->eepromUtils->readChar(ADDR(majorVersion));
    *minor = this->eepromUtils->readChar(ADDR(minorVersion));
    *patch = this->eepromUtils->readChar(ADDR(patchVersion));
}

/**
 * Save the minimum position of a servomotor in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @param value minimum position (between 0 and 180 degrees)
 */
void Hackberry_eeprom::SetMinServo(unsigned char member, unsigned char value)
{
    switch(member)
    {
        case THUMB : this->eepromUtils->writeChar(ADDR(thumbMin),value);
        break;
        case INDEX : this->eepromUtils->writeChar(ADDR(indexMin),value);
        break;
        case FINGERS: this->eepromUtils->writeChar(ADDR(fingersMin),value);
        break;
    }
}

/**
 * Save the maximum position of a servomotor in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @param value maxmimum position (between 0 and 180 degrees)
 */
void Hackberry_eeprom::SetMaxServo(unsigned char member, unsigned char value)
{
    switch(member)
    {
        case THUMB : this->eepromUtils->writeChar(ADDR(thumbMax),value);
        break;
        case INDEX : this->eepromUtils->writeChar(ADDR(indexMax),value);
        break;
        case FINGERS: this->eepromUtils->writeChar(ADDR(fingersMax),value);
        break;
    }
}
/**
 * Get the minimum position of a servomotor saved in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @return minimum position (between 0 and 180 degrees)
 */
unsigned char Hackberry_eeprom::GetMinServo(unsigned char member)
{
    switch(member)
    {
        case THUMB :  return (unsigned char)this->eepromUtils->readChar(ADDR(thumbMin));
        break;
        case INDEX :  return (unsigned char)this->eepromUtils->readChar(ADDR(indexMin));
        break;
        case FINGERS: return (unsigned char)this->eepromUtils->readChar(ADDR(fingersMin));
        break;
        default: return 255;
        break;
    }
}

/**
 * Get the maximum position of a servomotor saved in the eeprom 
 * @param member THUMB, INDEX or FINGERS 
 * @return maximum position (between 0 and 180 degrees)
 */
unsigned char Hackberry_eeprom::GetMaxServo(unsigned char member)
{
    switch(member)
    {
        case THUMB :  return (unsigned char)this->eepromUtils->readChar(ADDR(thumbMax));
        break;
        case INDEX :  return (unsigned char)this->eepromUtils->readChar(ADDR(indexMax));
        break;
        case FINGERS: return (unsigned char)this->eepromUtils->readChar(ADDR(fingersMax));
        break;
        default: return 255;
        break;
    }
}


/**
 * Save the sensor type in the eeprom 
 * @param type type of the sensor (TYPE_IR_SENSOR , TYPE_EMG_SENSOR, etc..)
 */
void Hackberry_eeprom::SetSensorType(unsigned char type)
{
    this->eepromUtils->writeChar(ADDR(sensorType),type);
}

/**
 * Get the sensor type saved in the eeprom 
 * @return type of the sensor (TYPE_IR_SENSOR , TYPE_EMG_SENSOR, etc..)
 */
unsigned char Hackberry_eeprom::GetSensorType()
{
    return (unsigned char)this->eepromUtils->readChar(ADDR(sensorType));
}

/**
 * Save the sensor maximum value in the eeprom 
 * @param value max sensor value (MIN_ADC by default)
 */
void Hackberry_eeprom::SetSensorMin(int value)
{
    this->eepromUtils->writeInt(ADDR(sensorMin),value);
}

/**
 * Get the sensor minimum value saved in the eeprom 
 * @return sensor min value (MAX_ADC by default)
 */
int Hackberry_eeprom::GetSensorMin()
{
    return this->eepromUtils->readInt(ADDR(sensorMin));
}

/**
 * Get the max sensor value saved in the eeprom 
 * @return sensor max sensor value (MAX_ADC by default)
 */
void Hackberry_eeprom::SetSensorMax(int value)
{
    this->eepromUtils->writeInt(ADDR(sensorMax),value);
}

/**
 * Get the min sensor value saved in the eeprom 
 * @return sensor min sensor value (MIN_ADC by default)
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
    Serial.println(F("\nEEPROM MAPPING"));
    
    Serial.print(F("Hand         |   "));    Serial.println( ADDR(selectedHand));

    Serial.print(F("MinThumb     |   "));    Serial.println( ADDR(thumbMin));
    Serial.print(F("MinIndex     |   "));    Serial.println( ADDR(indexMin));
    Serial.print(F("MinFingers   |   "));    Serial.println( ADDR(fingersMin));

    Serial.print(F("MaxThumb     |   "));    Serial.println( ADDR(thumbMax));
    Serial.print(F("MaxIndex     |   "));    Serial.println( ADDR(indexMax));
    Serial.print(F("MaxFingers   |   "));    Serial.println( ADDR(fingersMax));

    Serial.print(F("SensorType   |   "));    Serial.println( ADDR(sensorType));
    Serial.print(F("SensorMin    |   "));    Serial.println( ADDR(sensorMin));
    Serial.print(F("SensorMax    |   "));    Serial.println( ADDR(sensorMax));
}


/**
 * Display the memory content on the serial monitor (debug usage only)
 */
void Hackberry_eeprom::printMemoryContent()
{
    Serial.println(F("\nEEPROM CONTENT"));

    Serial.print(F("Hand = ")); Serial.println( this->GetHand() == RIGHT_HAND ? "RIGHT_HAND":"LEFT_HAND");

    Serial.print(F("MinThumb = ")); Serial.println( this->GetMinServo(THUMB) );
    Serial.print(F("MinIndex = ")); Serial.println( this->GetMinServo(INDEX) );
    Serial.print(F("MinFingers = ")); Serial.println( this->GetMinServo(FINGERS) );

    Serial.print(F("MaxThumb = ")); Serial.println( this->GetMaxServo(THUMB) );
    Serial.print(F("MaxIndex = ")); Serial.println( this->GetMaxServo(INDEX) );
    Serial.print(F("MaxFingers = ")); Serial.println( this->GetMaxServo(FINGERS) );


    Serial.print(F("SensorType = ")); Serial.println( this->GetSensorType() );
    Serial.print(F("Sensormin = ")); Serial.println( this->GetSensorMin() );
    Serial.print(F("SensorMax = ")); Serial.println( this->GetSensorMax() );
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
void Hackberry_eeprom::loadDefaultParameters()
{
    this->SetHand(RIGHT_HAND);

    this->SetMinServo(THUMB,THUMB_MIN);  
    this->SetMaxServo(THUMB,THUMB_MAX);

    this->SetMinServo(INDEX,INDEX_MIN);  
    this->SetMaxServo(INDEX,INDEX_MAX);

    this->SetMinServo(FINGERS,FINGERS_MIN);
    this->SetMaxServo(FINGERS,FINGERS_MAX);

    this->SetSensorType(TYPE_IR_SENSOR);
    this->SetSensorMin(MIN_ADC);
    this->SetSensorMax(MAX_ADC);

    this->SetMagicWord();
}