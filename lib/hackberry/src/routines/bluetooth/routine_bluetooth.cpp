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
#include "routine_bluetooth.h"


Routine_bluetooth::Routine_bluetooth()
{

}


/**
 * Initialize the bluetooth routine
 * 
 * @param hand Hackberry_hand object that contains all the hackberry drivers to use
 */
void Routine_bluetooth::init(Hackberry_hand *hand)
{
    this->hand = hand;
}


/**
 * Start the bluetooth module
 */
void Routine_bluetooth::start()
{
    DebugPrintln(F("Bluetooth started"));
    this->hand->bluetooth.start();
}


/**
 * Stop the bluetooth module
 */
void Routine_bluetooth::stop()
{
    DebugPrintln(F("Bluetooth stopped"));
    this->hand->bluetooth.stop();
}


/**
 * Execute the Bluetooth Routine main code
 */
void Routine_bluetooth::execute()
{
    if(this->hand->bluetooth.isStarted())
    {
        String messageReceived = this->hand->bluetooth.receive();
        this->checkActivity(ACTIVITY_TIME);
        if (messageReceived.length() <= 1) return;

        DebugPrint(F("[BT] Receive : "));
        DebugPrintln(messageReceived);
    
        int command = ParseString(messageReceived,PARSECHAR, 0).toInt();
        this->decodeInstruction(command,messageReceived);
    }
}

/**
 * Stop the bluetooth if it's inactive since the delay programmed
 * 
 * @param delayBeforeStop delay(in seconds) of activity time authorized
 */
void Routine_bluetooth::checkActivity(unsigned long delayBeforeStop)
{
    if ((millis() - this->hand->bluetooth.getLastActivityTime() ) >= delayBeforeStop * 1000)
    {
        this->stop();
    }
}

/**
 * Check if the bluetooth instruction received is a valid hackberry bluetooth instruction.
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 *
 * @see Routine_bluetooth#generalInstruction
 * @see Routine_bluetooth#servoInstruction
 * @see Routine_bluetooth#sensorInstruction
 */
void Routine_bluetooth::decodeInstruction(int command, String message)
{
    this->generalInstruction(command,message);
    this->servoInstruction(command,message);
    this->sensorInstruction(command,message);
}


/**
 * Check if the bluetooth instruction received is for the general (AT) commands. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
void Routine_bluetooth::generalInstruction(int command, String message)
{
    bool isPasswordSet = false;
    switch(command)
    {     
        /*
        * ----------------------------------------------------------------
        * command       : TEST
        * 
        * description   : send "OK" when test command is received
        * 
        * ----------------------------------------------------------------
        * parameters    : none 
        * 
        * return        : "OK"
        * ----------------------------------------------------------------
        */
        case CMD_GEN_TEST:
            this->hand->bluetooth.send("OK");
        break;

        /*
        * ----------------------------------------------------------------
        * command       : SET_PASS
        * 
        * description   : set the bluetooth password
        * 
        * ----------------------------------------------------------------
        * parameters    : new password (between "0000" and "9999")
        * 
        * return        : "1" if password is correctly set
        *                 "0" otherwise
        * ----------------------------------------------------------------
        */
        case  CMD_GEN_SET_PASS: 
            isPasswordSet =  this->hand->bluetooth.setPassword(message);
            this->hand->bluetooth.send(isPasswordSet ? '1':'0');
        break;

        case  CMD_GEN_SET_NAME:
            this->hand->bluetooth.setName(message); 
        break;

        case  CMD_GEN_STOP: 
            this->stop();
        break;

        case  CMD_GEN_RESET: 
            this->stop();
            this->start();
        break;

        default:break;
    }
}

/**
 * Check if the bluetooth instruction received is for the servomotors. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
void Routine_bluetooth::servoInstruction(int command, String message)
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
                this->hand->servos.relativeMove(targetMember,degree);
            }
        break;

        case  CMD_SRV_MOVE_DOWN: 
            if (paramExist(message,1) && paramExist(message,2))
            {
                targetMember = getParam(message,1).toInt();
                degree -= getParam(message,2).toInt();

                this->hand->servos.relativeMove(targetMember,degree);
            }
        break;

        case  CMD_SRV_SAVE_MAX: 
        {
            if (paramExist(message,1) && paramExist(message,2))
            {
                targetMember = getParam(message,1).toInt();
                int value = getParam(message,2).toInt();

                this->hand->eeprom.SetMaxServo(targetMember,value);
            }
        }
        break;

        case  CMD_SRV_SAVE_MIN: 
        {
            if (paramExist(message,1) && paramExist(message,2))
            {
                targetMember = getParam(message,1).toInt();
                int value = getParam(message,2).toInt();

                this->hand->eeprom.SetMinServo(targetMember,value);
            }
        }
        break;

        case  CMD_SRV_LOAD_MAX:
        {
            if (paramExist(message,1))
            {
                targetMember = getParam(message,1).toInt();
                int value = this->hand->eeprom.GetMaxServo(targetMember);
                this->hand->bluetooth.send(value);
            }
        }
         break;

        case  CMD_SRV_LOAD_MIN:
        {
            if (paramExist(message,1))
            {
                targetMember = getParam(message,1).toInt();
                int value = this->hand->eeprom.GetMinServo(targetMember);
                this->hand->bluetooth.send(value);
            }
        }
         break;

        case  CMD_SRV_SET_HAND:
        {
            if (paramExist(message,1))
            {
                int hand = getParam(message,1).toInt();
                this->hand->eeprom.SetHand((hand == RIGHT_HAND) ? RIGHT_HAND:LEFT_HAND);
            }
        }
         break;

        case  CMD_SRV_GET_HAND:
        {
            int value = (this->hand->eeprom.GetHand() == RIGHT_HAND) ? 1:0;
            this->hand->bluetooth.send(value);
        }
         break;

        case  CMD_SRV_SET_SPEED:
            if (paramExist(message,1))
            {
                speed = getParam(message,1).toInt();
                this->hand->servos.setSpeed(speed);
            }
         break;

        case  CMD_SRV_GET_SPEED:
                speed = this->hand->servos.getSpeed();
                this->hand->bluetooth.send(speed);
         break;

        case  CMD_SRV_TEST:
         break;

        default:break;
    }
}


/**
 * Check if the bluetooth instruction received is for the sensor. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
void Routine_bluetooth::sensorInstruction(int command, String message)
{
    switch(command)
    {
        case  CMD_SENS_GET_VALUE:
        {
            int value = this->hand->sensor.readAverage();
            this->hand->bluetooth.send(value);
        } 
         break;

        case  CMD_SENS_SET_TYPE:
            if (paramExist(message,1))
            {
                int type = getParam(message,1).toInt();
                this->hand->eeprom.SetSensorType(type);
            }
         break;

        case  CMD_SENS_GET_TYPE:
        {
            int value = this->hand->eeprom.GetSensorType();
            this->hand->bluetooth.send(value);
        }
         break;

        case  CMD_SENS_CALIB:
            //this->sensor->calibrate();
            //this->hand->sensor.calibrate();
         break;

        default:break;
    }
}


/* 
 * =============================================================================================================================================
 *                                  EXTERNAL FUNCTIONS
 * =============================================================================================================================================
 */

/**
 * Parse a string with a parse character and retrieve the cut string parsed at the index
 * 
 * @param data String to parse
 * @param separator Parsing character
 * @param index Index of the parsed String to retrieve
 * 
 * @return parsed String required ( or "" if not found)
 */
String ParseString(String data, char separator, int index)
{
  unsigned char found = 0;
  signed char strIndex[] = {0, -1};
  unsigned char maxIndex = data.length()-1;

  for(unsigned char i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


/**
 * Parse a String with the default Parsing character and retrieve the indexed parameter
 * 
 * @param message String to parse
 * @param index Index of the parsed String to retrieve
 * 
 * @return parsed String required ( or "" if not found)
 */
String getParam(String message, unsigned char index)
{
    return ParseString(message, PARSECHAR , index);
}


/**
 * check if the required parameters exist or not in the message
 * 
 * @param message Message that contain the parameters
 * @param index Index of the parameter (1, 2 , 3...)
 * 
 * @return true if the parameter exist ; false otherwise
 */
bool paramExist(String message, unsigned char index)
{
    return (getParam(message,index) == "") ? false:true;  
}

