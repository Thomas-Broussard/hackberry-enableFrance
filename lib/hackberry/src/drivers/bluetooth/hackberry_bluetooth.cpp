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
Hackberry_bluetooth::Hackberry_bluetooth(){
    
}


/**
 * Bluetooth initialization
 */
void Hackberry_bluetooth::init(Hackberry_sensor sensor, Hackberry_servos servos, Hackberry_buttons buttons) {
    // reference objects from Hackberry hand
    this->sensor = &sensor;
    this->servos = &servos;
    this->buttons= &buttons;

    // pins initialization
    pinMode(this->_pinPower, OUTPUT);

    // bluetooth initialization
    this->_BTSerial = new SoftwareSerial(this->_pinTx,this->_pinRx);
    this->_BTSerial->begin(DATA_BAUDRATE);

    this->stop(); // module power disabled by default
}

/**
 * enable Bluetooth module
 */
void Hackberry_bluetooth::start() {
    digitalWrite(this->_pinPower,HIGH);
    this->_enable = true;
}

/**
 * disable Bluetooth module
 */
void Hackberry_bluetooth::stop() {
    digitalWrite(this->_pinPower,LOW);
    this->_enable = false;
}



/** Read instructions received by bluetooth */
void Hackberry_bluetooth::execute() {
    if (this->_enable != true) return;

    String messageReceived = this->receiveString();
    if (messageReceived.length() <= 1) return;

    int command = ParseString(message,';', 0).toInt();
    this->decodeInstruction(command,message);
}



void Hackberry_bluetooth::decodeInstruction(int command, String message)
{
    switch(command)
    {
        case CMD_GEN_TEST:
            this->send("OK");
        break;

        default:break;
    }
}


/* 
 * =============================================================================================================================================
 *                                  SEND FUNCTIONS
 * =============================================================================================================================================
 */
void Hackberry_bluetooth::send(char c)
{
    if (!this->_enable) return;
    this->_BTSerial->write(c);
}

void Hackberry_bluetooth::send(String message)
{
    if (!this->_enable) return;
    for (unsigned int i = 0; i < message.length(); i++)
    {
        this->_BTSerial->write(message.charAt(i));
    }
}

void Hackberry_bluetooth::sendATcommand(String command, String value)
{
    if (!this->_enable) return;
    String message = "AT+" + command + "=" + value ;
    //this->setMode(AT_MODE);
    this->send(message);
    //this->setMode(DATA_MODE);
}

/* 
 * =============================================================================================================================================
 *                                  RECEIVE FUNCTIONS
 * =============================================================================================================================================
 */

String Hackberry_bluetooth::receiveString()
{
    if (!this->_enable) return "";
    
    String message = "";
    while (this->_BTSerial->available() > 0) 
    {
        delay(10);
        if (this->_BTSerial->available() > 0) {
            char c = this->_BTSerial->read();  //gets one byte from serial buffer
            message += c; //makes the string readString
        }
    }
    return message;
}



/*===============================================================================
  Nom 			: 	ParseString
  
  Description	: 	Permet de récupérer une partie d'une chaîne de caractère String
                  selon un caractère de parse fourni
					
  Paramètre(s) 	: data : chaine à découper
                  separator : caractère de parse
                  index : n° de la chaîne découpée à récupérer. ex : part0;part1;part2;...
  
  Retour		: 	Chaîne découpée souhaitée
===============================================================================*/
String ParseString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

