/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  AT Command list for bluetooth modules
 *  
 *  You can define your own module (see template at the end of the code)
 *  
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __BLUETOOTH_AT_H__
#define __BLUETOOTH_AT_H__

// Dependencies
#include <Arduino.h>
#include "bluetooth_serial.h"

/* 
 * =============================================================================================================================================
 *                                                      BLUETOOTH AT COMMANDS INTERFACE
 * =============================================================================================================================================
 */
class IBluetoothAT
{
    public:
        IBluetoothAT(BluetoothSerial *BT)
        {
            this->BT = BT;
        }
        // Interface methods

        /**
         * Set the bluetooth module name
         * @param name Name to apply
         */
        virtual bool setName(String name);

        /**
         * Set the password of the bluetooth module
         * @param password to apply
         * @return true if password is correctly set, false otherwise
         */
        virtual bool setPassword(String password);

        /**
         * Set the bluetooth speed communication
         * 
         * @param baudrate speed to apply
         */
        virtual bool setBaud(unsigned long baudrate);

    protected: 
        BluetoothSerial *BT;
};


/* 
 * =============================================================================================================================================
 *                                                      HC06 / HC05
 * =============================================================================================================================================
 */
class HC06 : public IBluetoothAT
{
    public:
        HC06(BluetoothSerial *BT) : IBluetoothAT(BT) { }

        bool setName(String name)
        {
            if (name.length() > 20) return false;
            this->BT->send("AT+NAME" + name);
            return true;
        }

        bool setPassword(String password)
        {
            // check if password is well-formed or not
            unsigned int passLength = 4;
            String correctPassword = "";
            if (password.length() != passLength) return false;
            for (unsigned int i = 0; i < passLength; i++)
            {
                if (password.charAt(i) < '1' || password.charAt(i) > '9') return false;
                correctPassword += password.charAt(i);
            }

            // set new password
            this->BT->send("AT+PIN" + correctPassword);
            
            return true;
        }

        bool setBaud(unsigned long baudrate)
        {
            bool result = true;
            switch(baudrate)
            {
                case 1200   : this->BT->send("AT+BAUD1"); break;
                case 2400   : this->BT->send("AT+BAUD2"); break;
                case 4800   : this->BT->send("AT+BAUD3"); break;
                case 9600   : this->BT->send("AT+BAUD4"); break;
                case 19200  : this->BT->send("AT+BAUD5"); break;
                case 38400  : this->BT->send("AT+BAUD6"); break;
                case 57600  : this->BT->send("AT+BAUD7"); break;
                case 115200 : this->BT->send("AT+BAUD8"); break;
                case 230400 : this->BT->send("AT+BAUD9"); break;
                case 470800 : this->BT->send("AT+BAUDA"); break;
                case 921600 : this->BT->send("AT+BAUDB"); break;
                case 1382400: this->BT->send("AT+BAUDC"); break;
                default : result = false; break;
            }
            return result;
        }
};


/* 
 * =============================================================================================================================================
 *                                                      HM-11
 * =============================================================================================================================================
 */
class HM11 : public IBluetoothAT
{
    public:
        HM11(BluetoothSerial *BT) : IBluetoothAT(BT) { }

        bool setName(String name)
        {
            if(name.length() > 12) return false;
            this->BT->send("AT+NAME" + name);
            return true;
        }

        bool setPassword(String password)
        {
            // check if password is well-formed or not
            unsigned int passLength = 6;
            String correctPassword = "";
            if (password.length() != passLength) return false;
            for (unsigned int i = 0; i < passLength; i++)
            {
                if (password.charAt(i) < '1' || password.charAt(i) > '9') return false;
                correctPassword += password.charAt(i);
            }

            // set new password
            this->BT->send("AT+PIN" + correctPassword);
            
            return true;
        }

        bool setBaud(unsigned long baudrate)
        {
            bool result = true;
            switch(baudrate)
            {
                case 1200   : this->BT->send("AT+BAUD7"); break;
                case 2400   : this->BT->send("AT+BAUD6"); break;
                case 4800   : this->BT->send("AT+BAUD5"); break;
                case 9600   : this->BT->send("AT+BAUD0"); break;
                case 19200  : this->BT->send("AT+BAUD1"); break;
                case 38400  : this->BT->send("AT+BAUD2"); break;
                case 57600  : this->BT->send("AT+BAUD3"); break;
                case 115200 : this->BT->send("AT+BAUD4"); break;
                case 230400 : this->BT->send("AT+BAUD8"); break;
                default : result = false; break;
            }
            return result;
        }
};

/* 
 * =============================================================================================================================================
 *                                                      <BLUETOOTH MODULE NAME>
 * =============================================================================================================================================
 */

/*
// replace BluetoothModuleName by the name of your Bluetooth module
class BluetoothModuleName : public IBluetoothAT
{
    public:

        BluetoothModuleName(BluetoothSerial *BT) : IBluetoothAT(BT) { }

        void setName(String name)
        {
           // do stuff here
        }

        bool setPassword(String password)
        {
            // do stuff here
        }

        void setBaud(unsigned long baudrate)
        {
            // do stuff here
        }
};
*/


#endif
