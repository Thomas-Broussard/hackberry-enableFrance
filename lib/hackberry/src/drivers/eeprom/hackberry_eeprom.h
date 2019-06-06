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

      // SERVOMOTORS
      void SetMinServo(int member, int value);
      void SetMaxServo(int member, int value);

      int GetMinServo(int member);
      int GetMaxServo(int member);


      // SENSOR
      void SetSensorType(int type);
      int  GetSensorType();

      void  SetSensorGain(float gain);
      float GetSensorGain();

      void SetSensorOffset(int offset);
      int  GetSensorOffset();

      // Debug usage only
      void printMemoryMap();
      void printMemoryContent();
      
      
    private:
      EEPROMUtils *eepromUtils;

      void SetMagicWord();
      bool IsMagicWordCorrect();
      void SetDefault();


};


#endif