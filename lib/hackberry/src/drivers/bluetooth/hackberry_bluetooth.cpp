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
Hackberry_bluetooth::Hackberry_bluetooth(int pinRx, int pinTx, int pinPower){
    this->_pinRx = pinRx;
    this->_pinTx = pinTx;
    this->_pinPower = pinPower;
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


/** Read instructions received by bluetooth */
void Hackberry_bluetooth::routine() 
{
    String messageReceived = this->BT->receive();
    if (messageReceived.length() <= 1) return;

    int command = ParseString(messageReceived,';', 0).toInt();
    this->decodeInstruction(command,messageReceived);
}


/* 
 * =============================================================================================================================================
 *                                  DECODE INSTRUCTIONS
 * =============================================================================================================================================
 */
void Hackberry_bluetooth::decodeInstruction(int command, String message)
{
    this->generalInstruction(command,message);
    this->servoInstruction(command,message);
    this->sensorInstruction(command,message);
}

void Hackberry_bluetooth::generalInstruction(int command, String message)
{
    switch(command)
    {
        // General (AT commands)
        case CMD_GEN_TEST:
            this->BT->send("OK");
        break;

        case  CMD_GEN_SET_PASS: 
            this->AT->setPassword(message);
        break;

        case  CMD_GEN_SET_NAME:
            this->AT->setName(message); 
        break;

        case  CMD_GEN_STOP: 
            this->stop();
        break;

        case  CMD_GEN_RESET: 
        break;

        default:break;
    }
}

void Hackberry_bluetooth::servoInstruction(int command, String message)
{
    int targetMember = 0;
    int degree = 0;
    int speed = 1;

    switch(command)
    {
        case  CMD_SRV_MOVE_UP: 
            if (paramExist(message,1) && paramExist(message,2))
            {
                targetMember = getParam(message,1).toInt();
                degree += getParam(message,2).toInt();

                this->servos->relativeMove(targetMember,degree, true);
            }
        break;

        case  CMD_SRV_MOVE_DOWN: 
        if (paramExist(message,1) && paramExist(message,2))
            {
                targetMember = getParam(message,1).toInt();
                degree -= getParam(message,2).toInt();

                this->servos->relativeMove(targetMember,degree, true);
            }
        break;

        case  CMD_SRV_SAVE_MAX: 
        break;

        case  CMD_SRV_SAVE_MIN: 
        break;

        case  CMD_SRV_LOAD_MAX:
         break;

        case  CMD_SRV_LOAD_MIN:
         break;

        case  CMD_SRV_SET_HAND:
         break;

        case  CMD_SRV_GET_HAND:
         break;

        case  CMD_SRV_SET_SPEED:
            if (paramExist(message,1))
            {
                speed = getParam(message,1).toInt();
                this->servos->setSpeed(speed);
            }
         break;

        case  CMD_SRV_GET_SPEED:
            speed = this->servos->getSpeed();
            this->BT->send(speed);
         break;

        case  CMD_SRV_TEST:
         break;

        default:break;
    }
}

void Hackberry_bluetooth::sensorInstruction(int command, String message)
{
    switch(command)
    {
        case  CMD_SENS_GET_VALUE:
         break;

        case  CMD_SENS_SET_TYPE:
         break;

        case  CMD_SENS_GET_TYPE:
         break;

        case  CMD_SENS_CALIB:
            //this->sensor->calibrate();
         break;

        default:break;
    }
}


/* 
 * =============================================================================================================================================
 *                                  EXTERNAL FUNCTIONS
 * =============================================================================================================================================
 */
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

String getParam(String message, int index)
{
    return ParseString(message,';', index);
}

bool paramExist(String message, int index)
{
    return (getParam(message,index) == "") ? false:true;  
}

