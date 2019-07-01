/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for debugging the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */


#ifndef __HACKBERRY_EEPROM_H__
#define __HACKBERRY_EEPROM_H__

// dépendances
#include <Arduino.h>

#include "eeprom_utils.h"
#include "eeprom_map.h"
#include "hackberry_global.h"
 

// class
class Hackberry_eeprom{

    public: 
      Hackberry_eeprom();

      // GENERAL
      void SetHand(bool hand);
      bool GetHand();
      void ChangeHand();

      void SetVersion(unsigned char major, unsigned char minor, unsigned char patch);
      void GetVersion(unsigned char *major, unsigned char *minor, unsigned char *patch);

      // SERVOMOTORS
      void SetMinServo(unsigned char member, unsigned char value);
      void SetMaxServo(unsigned char member, unsigned char value);

      unsigned char GetMinServo(unsigned char member);
      unsigned char GetMaxServo(unsigned char member);


      // SENSOR
      void SetSensorType(unsigned char type);
      unsigned char GetSensorType();

      void  SetSensorMax(int value);
      int   GetSensorMax();

      void  SetSensorMin(int value);
      int   GetSensorMin();
      

      // Debug usage only
      void printMemoryMap();
      void printMemoryContent();

      void SetMagicWord();
      bool IsMagicWordCorrect();
      
    private:
      EEPROMUtils *eepromUtils;
};


#endif