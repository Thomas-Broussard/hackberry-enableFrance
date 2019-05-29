/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for controlling Hackberry bluetooth communication
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_BLUETOOTH_H__
#define __HACKBERRY_BLUETOOTH_H__

// Dependencies
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "hackberry_global.h"
#include "bluetooth_AT_interface.h"
#include "bluetooth_data.h"

#define DATA_MODE true
#define AT_MODE false

// class
class Hackberry_bluetooth{

    public: 
        Hackberry_bluetooth(int pinRx, int pinTx, int pinPower);
        void init();

        void start();
        void stop();

        // Data functions
        void send(char c);
        void send(String message);
        void send(int message);

        String receive();
        
        // AT commands
        void setName(String name);
        bool setPassword(String password);
        void setBaud(unsigned long baudrate);
    
    private:        
        // wiring pins
        int _pinRx;
        int _pinTx; 
        int _pinPower; 

        // bluetooth objects
        SoftwareSerial *_BTSerial;
        IBluetoothAT  *AT;
        BluetoothData *BT;
};

#endif