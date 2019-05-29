/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for controlling Hackberry bluetooth communication
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */
#include "Hackberry_bluetooth.h"

/**
 * Constructor of the Servomotor class
 */
Hackberry_bluetooth::Hackberry_bluetooth(int pinRx, int pinTx, int pinPower)
{
    this->_pinRx = pinRx;
    this->_pinTx = pinTx;
    this->_pinPower = pinPower;
}


/**
 * Bluetooth initialization
 */
void Hackberry_bluetooth::init() 
{
    // pins initialization
    pinMode(this->_pinPower, OUTPUT);

    // bluetooth initialization
    this->_BTSerial = new SoftwareSerial(this->_pinTx,this->_pinRx);
    this->_BTSerial->begin(38400);

    this->BT = new BluetoothData(this->_BTSerial);
    this->AT = new HC06(this->BT);
    
    this->stop(); // module power disabled by default
}


/* 
 * =============================================================================================================================================
 *                                  GENERAL FUNCTIONS
 * =============================================================================================================================================
 */

/**
 * enable Bluetooth module
 */
void Hackberry_bluetooth::start() {
    digitalWrite(this->_pinPower,HIGH);
    this->BT->start();
}

/**
 * disable Bluetooth module
 */
void Hackberry_bluetooth::stop() {
    this->BT->stop();
    digitalWrite(this->_pinPower,LOW);
}


/* 
 * =============================================================================================================================================
 *                                  BLUETOOTH DATA
 * =============================================================================================================================================
 */

/**
 *  send character through bluetooth emitter
 *  
 * @param c character to send
 */
void Hackberry_bluetooth::send(char c) 
{
    this->BT->send(c);
}


/**
 * send Integer through bluetooth emitter
 *  
 * @param message Integer to send
 */
void Hackberry_bluetooth::send(int message) 
{
    this->BT->send(message);
}

/**
 * send String through bluetooth emitter
 *  
 * @param message String to send
 */
void Hackberry_bluetooth::send(String message) 
{
    this->BT->send(message);
}


/**
 * check if data are available in buffer of bluetooth receiver
 *  
 * @return data received as String
 */
String Hackberry_bluetooth::receive() 
{
    String messageReceived = this->BT->receive();
    return (messageReceived.length() <= 1) ? "" : messageReceived;
}


/* 
 * =============================================================================================================================================
 *                                  BLUETOOTH AT COMMANDS
 * =============================================================================================================================================
 */

/**
 * Set the bluetooth module name
 * @param name Name to apply
 */
void Hackberry_bluetooth::setName(String name)
{
    this->AT->setName(name);
}

/**
 * Set the password of the bluetooth module
 * @param password to apply
 * @return true if password is correctly set, false otherwise
 */
bool Hackberry_bluetooth::setPassword(String password)
{
    return this->AT->setPassword(password);
}

/**
 * Set the bluetooth speed communication
 * 
 * @param baudrate speed to apply
 */
void Hackberry_bluetooth::setBaud(unsigned long baudrate)
{
    this->AT->setBaud(baudrate);
}
