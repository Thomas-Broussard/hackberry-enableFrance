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
#include "bluetooth_instructions.h"

#include "../sensor/hackberry_sensor.h"
#include "../servos/hackberry_servos.h"
#include "../buttons/hackberry_buttons.h"

// Constants
#define PIN_RX 3        // bluetooth pin
#define PIN_TX 2        // bluetooth pin
#define PIN_POWER 4

#define DATA_MODE true
#define AT_MODE false

#define AT_BAUDRATE 38400
#define DATA_BAUDRATE 38400

// class
class Hackberry_bluetooth{

    public: 
        Hackberry_bluetooth();
        void init(Hackberry_sensor sensor, Hackberry_servos servos, Hackberry_buttons buttons);

        void start();
        void stop();
        void execute();

        // Instructions functions
        void decodeInstruction(String message);
        void executeInstruction(int command, String message);

        // Send functions
        void send(char c);
        void send(String message);
        void sendATcommand(String command, String value);

            // Receive function
        String receiveString();


    private:
        // variables
        bool _enable;
        

        // wiring pins
        int _pinRx      = PIN_RX;
        int _pinTx      = PIN_TX; 
        int _pinPower   = PIN_POWER; 

        // referenced objects
        SoftwareSerial *_BTSerial;
        Hackberry_sensor *sensor;
        Hackberry_servos *servos;
        Hackberry_buttons *buttons;

        
};

// external functions
String ParseString(String data, char separator, int index);

#endif