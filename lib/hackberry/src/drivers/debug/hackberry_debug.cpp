/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for debugging the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "hackberry_debug.h"

/**
 * Constructor
 * 
 * @param hackberry current Hackberry Hand object in use
 */
Hackberry_debug::Hackberry_debug()
{
  
}

/**
 * Initialize debug printing for Hackberry hand
 * 
 * @param hackberry Hackberry hand object
 * @param enable set to true to enable the debug printing
 */
void Hackberry_debug::init(bool enable, Hackberry_sensor sensor, Hackberry_servos servos, Hackberry_buttons buttons)
{
  this->_enable = enable;
  if(!enable) return;
  
  // link debug feature to current hackberry components
  this->sensor = &sensor;
  this->servos = &servos;
  this->buttons= &buttons;
  // init serial port
  Serial.begin(DEBUG_BAUDRATE);
}



/**
 * Print sensor debug information on the serial monitor
 */
void Hackberry_debug::printSensor()
{
    if(!this->_enable) return;

    String value = String(this->sensor->read());
    Serial.print("Sensor Value = ");
    Serial.println(value);
}

/**
 * Print servo debug information on the serial monitor
 * 
 * @param member Member concerned  (THUMB, INDEX or FINGERS)
 */
void Hackberry_debug::printServo(int member)
{
    if(!this->_enable) return;

    switch(member){
      case THUMB :   Serial.print("THUMB Position   = ");
      break;
      case INDEX :   Serial.print("INDEX Position   = ");
      break;
      case FINGERS : Serial.print("FINGERS Position = ");
      break;
    }
    int result = servos->getPosition(member);

    if (result == ERROR_CODE){
      Serial.println("error");
    }
    else{
      Serial.println(String(result));
    }
}

/**
 * Print all servos debug information on the serial monitor
 */
void Hackberry_debug::printServos()
{
  this->printServo(THUMB);
  this->printServo(INDEX);
  this->printServo(FINGERS);
}

void Hackberry_debug::printAll()
{
  Serial.println("\n-----------------------------");
  Serial.println("---------- DEBUG ------------");
  Serial.println("-----------------------------");

  this->printSensor();  Serial.println();
  this->printServos();

  Serial.println("-----------------------------");
  Serial.println("-----------------------------\n");
}
