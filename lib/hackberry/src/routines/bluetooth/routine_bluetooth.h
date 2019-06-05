/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for monitoring the Hackberry Hand Battery
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __ROUTINE_BLUETOOTH_H__
#define __ROUTINE_BLUETOOTH_H__

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"
#include "drivers/hackberry_hand.h"

#include "bluetooth_instructions.h"

#define PARSECHAR  ';'
#define ACTIVITY_TIME 600 // seconds

// class
class Routine_bluetooth{

    public: 
        Routine_bluetooth();
        void init(Hackberry_hand hand);
        void start();
        void stop();
        void execute();

    private:
        Hackberry_hand *hand;

        void checkActivity(unsigned long delayBeforeStop);
        void decodeInstruction(int command, String message);
        void generalInstruction(int command, String message);
        void servoInstruction(int command, String message);
        void sensorInstruction(int command, String message);
};

// external functions
String ParseString(String data, char separator, int index);
String getParam(String message, int index);
bool paramExist(String message, int index);

#endif