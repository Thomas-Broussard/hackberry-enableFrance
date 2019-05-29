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

       /**
        * enable the bluetooth module
        */
        void start() {
            this->_enable = true;
        }

        /**
        * disable the bluetooth module
        */
        void stop() {
            this->_enable = false;
        }

        /**
        * check if bluetooth module is enabled
        * 
        * @return true if enabled, false otherwise
        */
        bool isEnabled() {
            return this->_enable ;
        }

        /* 
        * =============================================================================================================================================
        *                                  SEND FUNCTIONS
        * =============================================================================================================================================
        */

        /**
        *  send character through bluetooth emitter
        *  
        * @param c character to send
        */
        void send(char c)
        {
            if (!this->_enable) return;
            this->_BTSerial->write(c);
        }

        /**
        * send String through bluetooth emitter
        *  
        * @param message String to send
        */
        void send(String message)
        {
            if (!this->_enable) return;
            for (unsigned int i = 0; i < message.length(); i++)
            {
                this->_BTSerial->write(message.charAt(i));
            }
        }

        /**
        * send Integer through bluetooth emitter
        *  
        * @param message Integer to send
        */
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

       /**
        * check if data are available in buffer of bluetooth receiver
        *  
        * @return data received as String
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
