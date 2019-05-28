/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Common functions to read and write data in EEPROM
 *  
 *  see : http://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html#ga44c64ebb425fcb34b8d4dc19c4079869
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __EEPROM_UTILS_H__
#define __EEPROM_UTILS_H__

// Dependencies
#include <Arduino.h>
#include <EEPROM.h>

class EEPROMUtils
{
    public:
        EEPROMUtils(){}

        /* 
        * =============================================================================================================================================
        *                                  WRITE FUNCTIONS
        * =============================================================================================================================================
        */
       // Remark : update checks first if the value needs to change, so it does a read and if your value is different then it writes it. 

        void writeChar(int addr, char data)
        {
            EEPROM.update(addr,data);
        }

        void writeInt(int addr, int data)
        {
            byte two = (data & 0xFF);
            byte one = ((data >> 8) & 0xFF);
            
            EEPROM.update(addr, two);
            EEPROM.update(addr + 1, one);
        }

        void writeStr(int addr, String data)
        {
            int _size = data.length();
            for(int i=0;i<_size;i++)
            {
                EEPROM.update(addr+i,data[i]);
            }
            EEPROM.update(addr + _size , '\0');   //Add termination null character for String Data
        }

        void writeFloat(int addr, float data)
        {
            EEPROM.put(addr, data);
        }

        

        /* 
        * =============================================================================================================================================
        *                                  READ FUNCTIONS
        * =============================================================================================================================================
        */

        char readChar(int addr)
        {
            return EEPROM.read(addr);
        }

        int readInt(int addr)
        {
            long two = EEPROM.read(addr);
            long one = EEPROM.read(addr + 1);
            return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
        }

        String readStr(int addr)
        {
            char data[100]; //Max 100 Bytes
            int len=0;
            unsigned char k;
            k=EEPROM.read(addr);
            while(k != '\0' && len<500)   //Read until null character
            {    
                k = EEPROM.read(addr + len);
                data[len]=k;
                len++;
            }
            data[len]='\0';
            return String(data);
        }

        float readFloat(int addr)
        {
            float f = 0.00f;
            EEPROM.get(addr,f);
            return f;
        }
};

#endif
