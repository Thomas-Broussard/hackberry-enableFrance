/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Library for reading the Hackberry Hand Sensor
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __HACKBERRY_SENSOR_H__
#define __HACKBERRY_SENSOR_H__

// dépendances
#include "hackberry.h"


// class
class Hackberry_sensor{

    public: 
    Hackberry_sensor(Hackberry _hackberry);

    private:

    // Hackberry Hand
    Hackberry _hackberry;

    // Wiring pins
};


#endif