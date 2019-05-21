/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Common functions to send and receive data from bluetooth module
 *  
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __BLUETOOTH_DATA_H__
#define __BLUETOOTH_DATA_H__

// Dependencies
#include <Arduino.h>
#include <SoftwareSerial.h>


class BluetoothData
{
    private: 
        SoftwareSerial *_BTSerial;
        bool _enable = false;

    public:
        BluetoothData(SoftwareSerial *BTSerial)
        {
            this->_BTSerial = BTSerial;
        }

        /* 
        * =============================================================================================================================================
        *                                  START / STOP  FUNCTIONS
        * =============================================================================================================================================
        */

        void start() {
            this->_enable = true;
        }

        void stop() {
            this->_enable = false;
        }

        bool isEnabled() {
            return this->_enable ;
        }

        /* 
        * =============================================================================================================================================
        *                                  SEND FUNCTIONS
        * =============================================================================================================================================
        */

        void send(char c)
        {
            if (!this->_enable) return;
            this->_BTSerial->write(c);
        }

        void send(String message)
        {
            if (!this->_enable) return;
            for (unsigned int i = 0; i < message.length(); i++)
            {
                this->_BTSerial->write(message.charAt(i));
            }
        }

        void send(int message)
        {
            if (!this->_enable) return;
            this->send(String(message));
        }

        
        /* 
        * =============================================================================================================================================
        *                                  RECEIVE FUNCTIONS
        * =============================================================================================================================================
        */
        String receive()
        {
            if (!this->_enable) return "";
            
            String message = "";
            while (this->_BTSerial->available() > 0) 
            {
                delay(10);
                if (this->_BTSerial->available() > 0) {
                    char c = this->_BTSerial->read();  //gets one byte from serial buffer
                    message += c; //makes the string readString
                }
            }
            return message;
        }
};

#endif
