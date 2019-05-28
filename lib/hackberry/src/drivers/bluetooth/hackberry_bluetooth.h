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
#include "bluetooth_AT_interface.h"

#include "../sensor/hackberry_sensor.h"
#include "../servos/hackberry_servos.h"
#include "../buttons/hackberry_buttons.h"

#define DATA_MODE true
#define AT_MODE false

// class
class Hackberry_bluetooth{

    public: 
        Hackberry_bluetooth(int pinRx, int pinTx, int pinPower);
        void init(Hackberry_sensor sensor, Hackberry_servos servos, Hackberry_buttons buttons);

        void start();
        void stop();
        void routine();

        // Instructions functions
        void decodeInstruction(int command, String message);

    
    private:

        // private functions
        void generalInstruction(int command, String message);
        void servoInstruction(int command, String message);
        void sensorInstruction(int command, String message);
        
        // wiring pins
        int _pinRx;
        int _pinTx; 
        int _pinPower; 

        // referenced objects
        SoftwareSerial *_BTSerial;
        Hackberry_sensor *sensor;
        Hackberry_servos *servos;
        Hackberry_buttons *buttons;

        IBluetoothAT  *AT;
        BluetoothData *BT;
};

// external functions
String ParseString(String data, char separator, int index);
String getParam(String message, int index);
bool paramExist(String message, int index);

#endif