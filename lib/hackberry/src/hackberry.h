/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library to simplify the use of the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_H__
#define __HACKBERRY_H__

// dependencies
#include <Arduino.h>

// drivers
#include "drivers/hackberry_hand.h"
#include "routines/routineHandler.h"

// class
class Hackberry
{
    public:
        Hackberry();

        void init();
        void init(bool selectedHand, int sensorType);

        // Hand general settings 
        void setHand(bool selectedHand);
        void setSensorType(int sensorType);

        void printSignature();

        Hackberry_hand hand;
        RoutineHandler routine;
};



#endif
