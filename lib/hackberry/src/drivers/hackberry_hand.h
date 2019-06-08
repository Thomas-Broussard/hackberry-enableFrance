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

#ifndef __HACKBERRY_HAND_H__
#define __HACKBERRY_HAND_H__

// dependencies
#include <Arduino.h>

// Mapping of IOs
#include "hackberry_mapping.h"


// drivers
#include "buttons/hackberry_buttons.h"
#include "servos/hackberry_servos.h"
#include "sensor/hackberry_sensor.h"
#include "bluetooth/hackberry_bluetooth.h"
#include "eeprom/hackberry_eeprom.h"
#include "battery/hackberry_battery.h"



// class
class Hackberry_hand
{
    public:
        Hackberry_hand();

        // initialization
        void init();

        // Hackberry hand components
        Hackberry_buttons   buttons;
        Hackberry_servos    servos;
        Hackberry_sensor    sensor;
        Hackberry_battery   battery;
        Hackberry_bluetooth bluetooth;
        Hackberry_eeprom    eeprom;


        // Modes
        Hackberry_Mode getMode();
        void setMode(Hackberry_Mode mode);

        bool isSensorCalibrationEnabled();
        

        // Sensor Calibration mode only
        void startSensorCalibration();
        void stopSensorCalibration();
        unsigned long getSensorCalibrationTime();

        // Servos Calibration mode only
        unsigned int getServosCalibrationStep();
        void startServosCalibration();
        void nextServosCalibration();
        void stopServosCalibration();


    private:      
        Hackberry_Mode _mode;

        // Specifics variables
        unsigned long CalibrationSensor_Time; 
        unsigned int CalibrationServos_Step = 0;
};

#endif
