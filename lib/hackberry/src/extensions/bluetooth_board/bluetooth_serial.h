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


class BluetoothSerial
{
    private: 

    public:
        BluetoothSerial()
        {
        }

        /* 
        * =============================================================================================================================================
        *                                  SEND FUNCTIONS
        * =============================================================================================================================================
        */
        /**
        * start serial communication with bluetooth module
        *  
        * @param c character to send
        */
        void begin(unsigned int baudrate)
        {
            Serial.begin(baudrate);
        }

        /**
        *  send character through bluetooth emitter
        *  
        * @param c character to send
        */
        void send(char c)
        {
            Serial.print(c);
        }

        /**
        * send String through bluetooth emitter
        *  
        * @param message String to send
        */
        void send(String message)
        {
            Serial.print(message);
        }

        /**
        * send Integer through bluetooth emitter
        *  
        * @param message Integer to send
        */
        void send(int message)
        {
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
            String message = "";
            while (Serial.available() > 0) 
            {
                delay(10);
                if (Serial.available() > 0) {
                    char c = Serial.read();  //gets one byte from serial buffer
                    message += c; //makes the string readString
                }
            }
            return message;
        }
};

#endif
