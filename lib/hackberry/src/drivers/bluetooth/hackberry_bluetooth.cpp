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
 * Constructor of the Bluetooth module driver
 */

Hackberry_bluetooth::Hackberry_bluetooth()
{
}

/**
 * Initialize the Bluetooth module driver
 * 
 * @param pinRX digital input - hackberry RX pin (= bluetooth TX pin)
 * @param pinRX digital output - hackberry TX pin (= bluetooth RX pin)
 * @param pinPower digital output - used to power ON/OFF the bluetooth module
 */

void Hackberry_bluetooth::init(unsigned char pinRx, unsigned char pinTx, unsigned char pinPower)
{
    // pins initialization
    this->_pinRx = pinRx;
    this->_pinTx = pinTx;
    this->_pinPower = pinPower;
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
 * start Bluetooth module
 */
void Hackberry_bluetooth::start() {
 
    digitalWrite(this->_pinPower,HIGH);
    this->_lastActivity = millis();
    this->BT->start();
    this->_started = true;
    this->AT->setBaud(38400);
}

/**
 * stop Bluetooth module
 */
void Hackberry_bluetooth::stop() {
 
    this->BT->stop();
    this->_lastActivity = 0;
    digitalWrite(this->_pinPower,LOW);
    this->_started = false;
}

/**
 * check if bluetooth module is started or not
 * 
 * @return true if started. false otherwise
 */
bool Hackberry_bluetooth::isStarted() {
    return this->_started;
}

/**
 * Get the last activity time of the bluetooth module
 * Remark : the activity time is updated when bluetooth module is started, when it send something, or when it receive something.
 * This function is mainly use to do an automatic shutdown of the module when it is unused (since 10 minutes for example)
 * 
 * @return last activity time (in ms)
 */
unsigned long Hackberry_bluetooth::getLastActivityTime() {
    return this->_lastActivity;
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
    this->_lastActivity = millis();
}


/**
 * send Integer through bluetooth emitter
 *  
 * @param message Integer to send
 */
void Hackberry_bluetooth::send(int message) 
{
 
    this->BT->send(message);
    this->_lastActivity = millis();
}

/**
 * send String through bluetooth emitter
 *  
 * @param message String to send
 */
void Hackberry_bluetooth::send(String message) 
{
 
    this->BT->send(message);
    this->_lastActivity = millis();
}


/**
 * check if data are available in buffer of bluetooth receiver
 *  
 * @return data received as String
 */
String Hackberry_bluetooth::receive() 
{
    String messageReceived = this->BT->receive();

    if (messageReceived.length() <= 1)
    {
        return "";
    }
    else
    {
        this->_lastActivity = millis();
        return  messageReceived;
    }
    
}


/* 
 * =============================================================================================================================================
 *                                  BLUETOOTH AT COMMANDS
 * =============================================================================================================================================
 */

/**
 * Set the bluetooth module name
 * 
 * @param name Name to apply
 */
void Hackberry_bluetooth::setName(String name)
{
    this->_lastActivity = millis();
    this->AT->setName(name);
}

/**
 * Set the password of the bluetooth module
 * 
 * @param password to apply
 * @return true if password is correctly set, false otherwise
 */
bool Hackberry_bluetooth::setPassword(String password)
{
    this->_lastActivity = millis();
    return this->AT->setPassword(password);
}

/**
 * Set the bluetooth speed communication
 * 
 * @param baudrate speed to apply (in baud per seconds)
 */
void Hackberry_bluetooth::setBaud(unsigned long baudrate)
{
    this->_lastActivity = millis();
    this->AT->setBaud(baudrate);
}
