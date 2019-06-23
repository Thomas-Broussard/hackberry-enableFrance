/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Manages the movements of the servomotors according to the muscular activity detected by the sensor
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __ROUTINE_MOVES_H__
#define __ROUTINE_MOVES_H__

// dependencies
#include <Arduino.h>
#include "hackberry_global.h"
#include "drivers/hackberry_hand.h"

#define STEP_MOVE_DEGREE 5 // number of degrees traveled each time the routine is executed

#define MIN_STEP_DEGREE 0 
#define MAX_STEP_DEGREE 10

#define OPEN_THRESHOLD  400//341 // threshold value of the sensor below which the hand opens
#define CLOSE_THRESHOLD 600//682 // threshold value of the sensor above which the hand closes
// remark : if the value of the sensor is between these two thresholds, the hand does not move


// class
class Routine_moves
{
    public: 
        Routine_moves();
        void init(Hackberry_hand *hand);
        void execute();

    private:
        Hackberry_hand *hand;
        unsigned long lastMoveTime = 0;

        int speedOfMove(int sensorValue);
        bool isMoveExecutable();
};

#endif