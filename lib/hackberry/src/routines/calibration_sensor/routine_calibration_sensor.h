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
class Routine_calibration_sensor {

    public: 
        Routine_calibration_sensor();
        void init(Hackberry_hand *hand);
        void execute();

    private:
        Hackberry_hand *hand;

        bool calibrationFinished = false;
        int _sensorMin = MAX_ADC;
        int _sensorMax = MIN_ADC;

        void launchCalibration();
        void endCalibration();
        void checkCalibrationEnd(unsigned long delayBeforeStop);
};

#endif