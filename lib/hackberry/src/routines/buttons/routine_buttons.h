/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Handle the behavior of buttons
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __ROUTINE_BUTTONS_H__
#define __ROUTINE_BUTTONS_H__

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"
#include "drivers/hackberry_hand.h"

#define DEBOUNCE_DELAY 100 // delay (ms) between two action on the same button, to avoid mechanical and physical button issues during transition

// class
class Routine_buttons
{
    public: 
        Routine_buttons();
        void init(Hackberry_hand hand);
        void execute();

    private:
        Hackberry_hand *hand;

        bool isThumbOpen = false;
        bool isLockEnabled = false;

        unsigned long lastCalibDebounce = 0;
        unsigned long lastExtraDebounce = 0;
        unsigned long lastThumbDebounce = 0;
        unsigned long lastLockDebounce  = 0;
        
        void actionCalib();
        void actionExtra();
        void actionThumb();
        void actionLock();

        bool isDebounced(unsigned long *lastDebounceTime, unsigned long debounceDelay);
};

#endif