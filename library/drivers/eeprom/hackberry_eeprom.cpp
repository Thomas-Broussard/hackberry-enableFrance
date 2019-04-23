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

#include "hackberry_eeprom.h"


/**
 * Constructor
 * 
 * @param hackberry current Hackberry Hand object in use
 */
Hackberry_eeprom::Hackberry_eeprom(Hackberry hackberry)
{
    this->_hackberry = hackberry;
}

/**
 * Get an integer from memory
 *
 * @param addr address targeted memory
 * @return integer read
 */
int Hackberry_eeprom::read(int addr){
  return EEPROM.read(addr);
}

/**
 * Get a string from memory
 * Note: The string must not exceed 100 characters
 *
 * @param addr address targeted memory
 * @return string read
 */
String Hackberry_eeprom::readString(int addr){
  char data[100];
  int len=0;
  int k;
  k=EEPROM.read(add);
  while(k != '\0' && len<512)   //Lecture de la mémoire jusqu'à tomber sur un caractère de fin de chaîne
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}


/**
 * Get a float from EEPROM memory
 *
 * @param addr address targeted memory
 * @return float read
 */
/*
float Hackberry_eeprom::readFloat(int addr){
  
}*/


/**
 * Saves an integer in memory
 *
 * @param addr address targeted memory
 * @param val integer to save
 */
void Hackberry_eeprom::write(int addr, int val){
  EEPROM.write(addr,val);
}



/**
 * Save a string in the memory
 * Note: The string must not exceed 100 characters
 *
 * @param addr address targeted memory
 * @param val String to save
 */
void Hackberry_eeprom::writeString(int addr, String val){
  int _size = val.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(addr+i,val[i]);
  }
  EEPROM.write(addr+_size,'\0');   //Fin de chaîne de caractère
  EEPROM.commit();
}

/**
 * Saves float in memory
 *
 * @param addr address targeted memory
 * @param val float to save
 */
/*
void Hackberry_eeprom::writeFloat(int addr, float val){
  
}*/