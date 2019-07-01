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

#ifndef __EXTENSION_BLUETOOTH_H__
#define __EXTENSION_BLUETOOTH_H__

// Dependencies
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "hackberry_mapping.h"
#include "drivers/hackberry_hand.h"

#include "bluetooth_serial.h"
#include "bluetooth_AT_interface.h"
#include "bluetooth_instructions.h"

#define PARSECHAR  ';'
#define ACTIVITY_TIME 600 // seconds

#define BLUETOOTH_BAUDRATE 38400

// WARNING : Bluetooth can't be used with Debug print on MK2 !  
#if HACKBERRY_BOARD == MK2
    #define PIN_BLUETOOTH_RX 1
    #define PIN_BLUETOOTH_TX 0
    #define PIN_BLUETOOTH_POWER A3

#elif HACKBERRY_BOARD == MK3
    #define PIN_BLUETOOTH_RX 3
    #define PIN_BLUETOOTH_TX 4
    #define PIN_BLUETOOTH_POWER A3

#endif

// class
class Extension_Bluetooth{

    public: 
        Extension_Bluetooth();

        // General functions
        void init(Hackberry_hand *hand);
        void execute();

        void start();
        void stop();
        bool isStarted();

        // Rx/Tx functions
        void send(char c);
        void send(String message);
        void send(int message);
        String receive();
        
        // AT commands
        bool setName(String name);
        bool setPassword(String password);
        bool setBaud(unsigned long baudrate);
    
    private:        
        Hackberry_hand *hand;

        // bluetooth objects
        BluetoothSerial *BT;
        IBluetoothAT  *AT;
        
        unsigned long _lastActivityTime = 0;
        bool _isStarted = false;

        void checkActivity(unsigned long delayBeforeStop);
        void decodeInstruction(int command, String message);
        void generalInstruction(int command, String message);
        void servoInstruction(int command, String message);
        void sensorInstruction(int command, String message);
};

// External functions
String ParseString(String data, char separator, int index);
String getParam(String message, unsigned char index);
bool paramExist(String message, unsigned char index);

#endif