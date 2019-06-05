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
 * Constructor
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


void Hackberry_eeprom::SetHand(bool hand)
{
    if (hand == RIGHT_HAND){
        this->eepromUtils->writeChar(ADDR(selectedHand),'1');
    }
    else if (hand == LEFT_HAND){
        this->eepromUtils->writeChar(ADDR(selectedHand),'0');
    }
}

bool Hackberry_eeprom::GetHand()
{
    return (this->eepromUtils->readChar(ADDR(selectedHand)) == '1') ? RIGHT_HAND : LEFT_HAND;
}



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

void Hackberry_eeprom::SetSensorType(int type)
{
    this->eepromUtils->writeChar(ADDR(sensorType),(char)type);
}

int Hackberry_eeprom::GetSensorType()
{
    return this->eepromUtils->readChar(ADDR(sensorType));
}


void Hackberry_eeprom::SetSensorGain(float gain)
{
    this->eepromUtils->writeFloat(ADDR(sensorGain),gain);
}

float Hackberry_eeprom::GetSensorGain()
{
    return this->eepromUtils->readFloat(ADDR(sensorGain));
}


void Hackberry_eeprom::SetSensorOffset(int offset)
{
    this->eepromUtils->writeInt(ADDR(sensorOffset),offset);
}

int Hackberry_eeprom::GetSensorOffset()
{
    return this->eepromUtils->readInt(ADDR(sensorOffset));
}


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




/* 
* =============================================================================================================================================
*                                  PRIVATE FUNCTIONS
* =============================================================================================================================================
*/
void Hackberry_eeprom::SetMagicWord()
{
    this->eepromUtils->writeFloat(ADDR(magicWord),MAGIC_WORD);
}

bool Hackberry_eeprom::IsMagicWordCorrect()
{
    return (this->eepromUtils->readFloat(ADDR(magicWord)) == MAGIC_WORD);
}

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