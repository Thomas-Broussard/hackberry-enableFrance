/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for manipulating the EEPROM of the main Hackberry
 *
 *  WARNING: do not write in loop memory or you will destroy this last prematurely!
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#ifndef __HACKBERRY_EEPROM_H__
#define __HACKBERRY_EEPROM_H__

// dependencies
#include <EEPROM.h>
#include "hackberry.h"

#include "mapping_eeprom.h" // memory mapping of EEPROM

// class
class Hackberry_eeprom{

    public: 
    Hackberry_eeprom(Hackberry _hackberry);

   // EEPROM Read
   int readInt(int addr);
   String readString(int addr);
   //float readFloat(int addr);

   // EEPROM Write
   void writeInt(int addr, int val);
   void writeString(int addr, String val);
   //void writeFloat(int addr, float val);

    private:
    // Hackberry Hand
    Hackberry _hackberry;
};




#endif