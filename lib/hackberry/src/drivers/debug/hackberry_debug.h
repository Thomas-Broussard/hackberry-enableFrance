/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for debugging the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */


#ifndef __HACKBERRY_DEBUG_H__
#define __HACKBERRY_DEBUG_H__
/*
// dépendances
#include <Arduino.h>
#include "hackberry.h"
#include "hackberry_global.h"

// communication speed 
#define DEBUG_BAUDRATE 9600

// class
class Hackberry_debug{

    public: 
      Hackberry_debug();

      void begin(Hackberry hackberry,bool enable);
      void enable(bool enable);

      void print(String str);
      void println(String str);
      void println();

      void printAll();
      void printSensor();
      void printServo(int member);
      void printServos();


    private:
      Hackberry *hackberry;
      bool _enable = false;
};*/

// dépendances
#include <Arduino.h>
#include "../sensor/hackberry_sensor.h"
#include "../servos/hackberry_servos.h"
#include "../buttons/hackberry_buttons.h"

// communication speed 
#define DEBUG_BAUDRATE 9600

// class
class Hackberry_debug{

    public: 
      Hackberry_debug();

      void init(bool enable, Hackberry_sensor sensor, Hackberry_servos servos, Hackberry_buttons buttons);

      void printSensor();
      void printServo(int member);
      void printServos();
      void printAll();

    private:

      Hackberry_sensor *sensor;
      Hackberry_servos *servos;
      Hackberry_buttons *buttons;

      bool _enable = false;
};


#endif