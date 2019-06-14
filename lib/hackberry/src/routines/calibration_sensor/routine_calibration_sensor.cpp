/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Routine for Hackberry sensor calibration
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
 * Initialize the sensor calibration routine
 * 
 * @param hand Hackberry_hand object that contains all the hackberry drivers to use
 */
void Routine_calibration_sensor::init(Hackberry_hand *hand)
{
    this->hand = hand;
}

/**
 * Execute the sensor calibration routine main code
 */
void Routine_calibration_sensor::execute()
{
    // code executed when calibration is enabled
    if(this->hand->getMode() == SensorCalibration)
    {
        this->checkCalibrationEnd(CALIBRATION_TIME);
        this->launchCalibration();
    }
}

/**
 * Stop the calibration after the delay programmed 
 * @param delayBeforeStop_ms delay(in milliseconds) of activity time authorized
 */
void Routine_calibration_sensor::checkCalibrationEnd(unsigned long delayBeforeStop_ms)
{
    
    if ((millis() - this->hand->getSensorCalibrationTime()) >= delayBeforeStop_ms)
    {
        this->hand->stopSensorCalibration();
        this->endCalibration();
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
    this->hand->sensor.calibrate(this->_sensorMin,this->_sensorMax);

    this->hand->eeprom.SetSensorMin(this->_sensorMin);
    this->hand->eeprom.SetSensorMax(this->_sensorMax);

    #ifdef DEBUG_ROUTINE_ENABLED
        Serial.println("-------------------------");
        Serial.println("Sensor Calibration Finished");
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
