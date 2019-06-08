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
#include "buttons/routine_buttons.h"
#include "moves/routine_moves.h"
#include "battery/routine_battery.h"
#include "eeprom_init/routine_eeprom_init.h"
#include "calibration_sensor/routine_calibration_sensor.h"
#include "calibration_servos/routine_calibration_servos.h"

// class
class RoutineHandler{

    public: 
        RoutineHandler();
        void init(Hackberry_hand *hand);

        Routine_bluetooth bluetooth;
        Routine_buttons buttons;
        Routine_moves moves;
        Routine_battery batteryMonitoring;
        Routine_eeprom_init eeprom_init;
        Routine_calibration_sensor calibration_sensor;
        Routine_calibration_servos calibration_servos;

    private:
};
 
#endif