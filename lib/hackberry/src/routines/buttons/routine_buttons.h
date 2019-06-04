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

#include "bluetooth_instructions.h"

#define PARSECHAR  ';'

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

        void actionCalib();
        void actionExtra();
        void actionThumb();
        void actionLock();
};

#endif