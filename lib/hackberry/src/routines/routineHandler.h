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

#ifndef __ROUTINE_H__
#define __ROUTINE_H__

// dependencies
#include <Arduino.h>
#include "bluetooth/routine_bluetooth.h"


// class
class RoutineHandler{

    public: 
        RoutineHandler();
        void init(Hackberry_hand hand);

        Routine_bluetooth bluetooth;
};

#endif