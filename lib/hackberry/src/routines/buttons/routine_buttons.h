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
#include "hackberry_mapping.h"
#include "drivers/hackberry_hand.h"

#define DEBOUNCE_DELAY 1000 // delay (ms) between two action on the same button, to avoid mechanical and physical button issues during transition

#define LONG_DEBOUNCE_DELAY 5000  // delay (ms) between two long action on the same button
#define LONG_BUTTON_PRESS 5000 // time (ms) required to take into account the long press of a button 

// class
class Routine_buttons
{
    public: 
        Routine_buttons();
        void init(Hackberry_hand *hand);
        void execute();

    private:
        Hackberry_hand *hand;

        bool isThumbOpen = false;
        bool isLockEnabled = false;

        unsigned long lastCalibDebounce = 0;
        unsigned long lastExtraDebounce = 0;
        unsigned long lastThumbDebounce = 0;
        unsigned long lastLockDebounce  = 0;

        unsigned long lastLongCalibDebounce = 0;
        unsigned long lastLongExtraDebounce = 0;
        unsigned long lastLongThumbDebounce = 0;
        unsigned long lastLongLockDebounce  = 0;
        
        void actionCalib();
        void actionExtra();
        void actionThumb();
        void actionLock();

        void longActionCalib();
        void longActionExtra();
        void longActionThumb();
        void longActionLock();

        bool isDebounced(unsigned long *lastDebounceTime, unsigned long debounceDelay);
};

#endif 