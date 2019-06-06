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

#ifndef __ROUTINE_CALIBRATION_H__
#define __ROUTINE_CALIBRATION_H__

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"
#include "drivers/hackberry_hand.h"

#define CALIBRATION_TIME 10 // seconds

// class
class Routine_calibration {

    public: 
        Routine_calibration();
        void init(Hackberry_hand *hand);
        void execute();

    private:
        Hackberry_hand *hand;

        bool calibrationFinished = false;
        int _sensorMin = 1023;
        int _sensorMax = 0;

        void launchCalibration();
        void checkActivity(unsigned long delayBeforeStop);
};

#endif