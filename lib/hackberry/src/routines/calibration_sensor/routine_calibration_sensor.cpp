/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Routine for Hackberry bluetooth communication
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "routine_calibration_sensor.h"


Routine_calibration_sensor::Routine_calibration_sensor()
{

}


/**
 * Initialize the bluetooth routine
 * 
 * @param hand Hackberry_hand object that contains all the hackberry drivers to use
 */
void Routine_calibration_sensor::init(Hackberry_hand *hand)
{
    this->hand = hand;
}

/**
 * Execute the Bluetooth Routine main code
 */
void Routine_calibration_sensor::execute()
{
    // code executed when calibration is enabled
    if(this->hand->isSensorCalibrationEnabled())
    {
        this->checkCalibrationEnd(CALIBRATION_TIME);
        this->launchCalibration();
    }
    // code executed when calibration is finished
    if (this->calibrationFinished)
    {
        this->endCalibration();
    }
}

/**
 * Stop the calibration after the delay programmed 
 * @param delayBeforeStop delay(in seconds) of activity time authorized
 */
void Routine_calibration_sensor::checkCalibrationEnd(unsigned long delayBeforeStop)
{
    
    if ((millis() - this->hand->getSensorCalibrationTime()) >= delayBeforeStop * 1000)
    {
        this->hand->stopSensorCalibration();
        this->calibrationFinished = true;
    }
}

void Routine_calibration_sensor::launchCalibration()
{
    int sensorValue = this->hand->sensor.readRawAverage();

    // record the maximum sensor value
    if (sensorValue > this->_sensorMax) {
      this->_sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < this->_sensorMin) {
      this->_sensorMin = sensorValue;
    }
}

void Routine_calibration_sensor::endCalibration()
{
    this->calibrationFinished = false;
    this->hand->sensor.calibrate(this->_sensorMin,this->_sensorMax);

    this->hand->eeprom.SetSensorMin(this->_sensorMin);
    this->hand->eeprom.SetSensorMax(this->_sensorMax);

    #ifdef DEBUG_ROUTINE_ENABLED
        Serial.println("-------------------------");
        Serial.println("Sensor Calibration Stopped");
        Serial.println("-------------------------");
        Serial.println("Results : ");
        Serial.print("SensorMin = ");
        Serial.println(this->hand->eeprom.GetSensorMin());
        Serial.print("SensorMax = ");
        Serial.println(this->hand->eeprom.GetSensorMax());
        Serial.println("-------------------------\n");
    #endif
        

    // reset the calibration parameters
    this->_sensorMax = MIN_ADC;
    this->_sensorMin = MAX_ADC;
}
