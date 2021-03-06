/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : 
 *  Routine for Hackberry servomotors calibration
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __ROUTINE_CALIBRATION_SERVOS_H__
#define __ROUTINE_CALIBRATION_SERVOS_H__

// dependencies
#include <Arduino.h>
#include "hackberry_mapping.h"
#include "drivers/hackberry_hand.h"

#define STEP 1

enum servosCalibSteps{
    IDLE,
    THUMB_OPEN,
    THUMB_CLOSE,
    INDEX_OPEN,
    INDEX_CLOSE,
    FINGERS_OPEN,
    FINGERS_CLOSE,
    END
};

// class
class Routine_calibration_servos {

    public: 
        Routine_calibration_servos();
        void init(Hackberry_hand *hand);
        void execute();

        void start();
        void end();
        void calibration();
        void CalibHand(bool hand);
        
    private:
        Hackberry_hand *hand;
        bool calibrationFinished = false;
        int _currentStep = IDLE;
        bool handCalibActiv = false;

        unsigned char limThumb[2];
        unsigned char limIndex[2];
        unsigned char limFingers[2];
        int count_blinking;
        bool state_blinking;
        void blinking();
        void SaveParamBeforeNextStep();
        void SaveServoParam(int member, unsigned char lim1, unsigned char lim2);
        void EndCalibServos();
        void MoveInitialPosition();
        void opencloseopen(int member);
};

#endif