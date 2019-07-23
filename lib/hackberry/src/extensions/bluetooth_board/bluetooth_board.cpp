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
#include "bluetooth_board.h"

/**
 * Constructor of the Bluetooth module driver
 */

Extension_Bluetooth::Extension_Bluetooth()
{
}

/**
 * Initialize the Bluetooth module driver
 * 
 * @param pinRX digital input - hackberry RX pin (= bluetooth TX pin)
 * @param pinRX digital output - hackberry TX pin (= bluetooth RX pin)
 * @param pinPower digital output - used to power ON/OFF the bluetooth module
 */

void Extension_Bluetooth::init(Hackberry_hand *hand)
{
    this->hand = hand;

    // pins initialization
    #ifdef PIN_BLUETOOTH_POWER
        pinMode(PIN_BLUETOOTH_POWER, OUTPUT);
    #endif

    // bluetooth initialization
    //this->BT = new BluetoothSerial();
    this->BT->begin(38400);

    this->AT = new HC06(this->BT);
    
    this->stop(); // module power disabled by default
}


/**
 * Execute the Bluetooth Routine main code
 */
void Extension_Bluetooth::execute()
{
    if (this->hand->getMode() == Bluetooth && !this->_isStarted){
        this->start();
    }
    else if (this->hand->getMode() == Standard && this->_isStarted){
        this->stop();
    }
    
    if (!this->_isStarted) return;

    String messageReceived = this->receive();
    this->checkActivity(ACTIVITY_TIME);
    if (messageReceived.length() <= 1) return;

    int command = ParseString(messageReceived,PARSECHAR, 0).toInt();
    this->decodeInstruction(command,messageReceived);
}


/* 
 * =============================================================================================================================================
 *                                  GENERAL FUNCTIONS
 * =============================================================================================================================================
 */

/**
 * start Bluetooth module
 */
void Extension_Bluetooth::start() 
{
    #ifdef PIN_BLUETOOTH_POWER
        digitalWrite(PIN_BLUETOOTH_POWER, HIGH);
    #endif

    this->_lastActivityTime = millis();
    this->AT->setBaud(38400);
    this->_isStarted = true;
    this->hand->setMode(Bluetooth);
}

/**
 * stop Bluetooth module
 */
void Extension_Bluetooth::stop() 
{
    this->_lastActivityTime = 0;

    #ifdef PIN_BLUETOOTH_POWER
        digitalWrite(PIN_BLUETOOTH_POWER, LOW);
    #endif

    this->_isStarted = false;
    this->hand->setMode(Standard);
}

/**
 * Stop the bluetooth if it's inactive since the delay programmed
 * 
 * @param delayBeforeStop delay(in seconds) of activity time authorized
 */
void Extension_Bluetooth::checkActivity(unsigned long delayBeforeStop)
{
    if ((millis() - this->_lastActivityTime ) >= delayBeforeStop * 1000)
    {
        this->stop();
    }
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
void Extension_Bluetooth::send(char c) 
{
    if (!this->_isStarted) return;

    this->BT->send(c);
    this->_lastActivityTime = millis();
}

/**
 * send String through bluetooth emitter
 *  
 * @param message String to send
 */
void Extension_Bluetooth::send(String message) 
{
    if (!this->_isStarted) return;
    
    for (unsigned int i = 0; i < message.length(); i++)
    {
        this->BT->send(message.charAt(i));
    }
    this->_lastActivityTime = millis();
}

/**
 * send Integer through bluetooth emitter
 *  
 * @param message Integer to send
 */
void Extension_Bluetooth::send(int message) 
{
    if (!this->_isStarted) return;
    this->send(String(message));
    //this->_lastActivityTime = millis(); // useless
}

void Extension_Bluetooth::resp(int cmd, int message)
{
    this->send((String) cmd + PARSECHAR + message + "\r\n");
}

void Extension_Bluetooth::resp(int cmd, String message)
{
    this->send((String) cmd + PARSECHAR + message + "\r\n");
}

void Extension_Bluetooth::resp(int cmd, char message)
{
    this->send((String) cmd + PARSECHAR + message + "\r\n");
}

/**
 * check if data are available in buffer of bluetooth receiver
 *  
 * @return data received as String
 */
String Extension_Bluetooth::receive() 
{
    if (!this->_isStarted) return "";

    // Get Rx Buffer
    String messageReceived = this->BT->receive();

    // Return content
    if (messageReceived.length() <= 1)
    {
        return "";
    }
    else
    {
        this->_lastActivityTime = millis();
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
bool Extension_Bluetooth::setName(String name)
{
    if (!this->_isStarted) return false;
    this->_lastActivityTime = millis();
    return this->AT->setName(name);
}

/**
 * Set the password of the bluetooth module
 * 
 * @param password to apply
 * @return true if password is correctly set, false otherwise
 */
bool Extension_Bluetooth::setPassword(String password)
{
    if (!this->_isStarted) return false;
    this->_lastActivityTime = millis();
    return this->AT->setPassword(password);
}

/**
 * Set the bluetooth speed communication
 * 
 * @param baudrate speed to apply (in baud per seconds)
 */
bool Extension_Bluetooth::setBaud(unsigned long baudrate)
{
    if (!this->_isStarted) return false;
    this->_lastActivityTime = millis();
    return this->AT->setBaud(baudrate);
}



/* 
 * =============================================================================================================================================
 *                                  INSTRUCTIONS FUNCTIONS
 * =============================================================================================================================================
 */


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
void Extension_Bluetooth::decodeInstruction(int command, String message)
{
    if (!this->_isStarted) return;
    if(!this->generalInstruction(command,message))
    if(!this->servoInstruction(command,message))
        this->sensorInstruction(command,message);
}


/**
 * Check if the bluetooth instruction received is for the general (AT) commands. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
bool Extension_Bluetooth::generalInstruction(int command, String message)
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
            this->resp(CMD_GEN_TEST,"OK");
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
            isPasswordSet =  this->setPassword(message);
            this->resp(CMD_GEN_SET_PASS, isPasswordSet ?'1':'0');
        break;

        case  CMD_GEN_SET_NAME:
            this->setName(message); 
        break;

        case  CMD_GEN_STOP: 
            this->stop();
        break;

        case  CMD_GEN_RESET: 
            this->stop();
            this->start();
        break;

        case CMD_GEN_VERSION:
            this->resp(CMD_GEN_VERSION, (String) MAJOR_VERSION + "." + MINOR_VERSION + "." + PATCH_VERSION);
        break;

        case CMD_GEN_BOARD:
            this->resp(CMD_GEN_BOARD, BOARD_NAME);
        break;

        default: return false;
        break;
    }
    return true;
}

/**
 * Check if the bluetooth instruction received is for the servomotors. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
bool Extension_Bluetooth::servoInstruction(int command, String message)
{
    int targetMember = 0;
    int degree = 0;
    int speed = 1;

    switch(command)
    {

        case  CMD_SRV_MOVE:
            if (paramExist(message,1) && paramExist(message,2))
                {
                    targetMember = getParam(message,1).toInt();
                    degree = getParam(message,2).toInt();
                    this->hand->servos.move(targetMember,degree);
                }
         break;

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
                this->resp(CMD_SRV_LOAD_MAX,(String)(targetMember + PARSECHAR + value));
            }
        }
         break;

        case  CMD_SRV_LOAD_MIN:
        {
            if (paramExist(message,1))
            {
                targetMember = getParam(message,1).toInt();
                int value = this->hand->eeprom.GetMinServo(targetMember);
                this->resp(CMD_SRV_LOAD_MIN,(String)(targetMember + PARSECHAR + value));
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
            this->resp(CMD_SRV_GET_HAND,value);
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
                this->resp(CMD_SRV_GET_SPEED,speed);
         break;

        case  CMD_SRV_TEST:
         break;

         

        default: return false;
        break;
    }
    return true;
}


/**
 * Check if the bluetooth instruction received is for the sensor. 
 * If it is, it executes the corresponding code
 * 
 * @param command command to check and execute (if possible)
 * @param message whole message received, which can contain the command parameters
 */
bool Extension_Bluetooth::sensorInstruction(int command, String message)
{
    switch(command)
    {
        case  CMD_SENS_GET_VALUE:
        {
            int value = this->hand->sensor.readAverage();
            this->resp(CMD_SENS_GET_VALUE,value);
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
            this->resp(CMD_SENS_GET_TYPE,value);
        }
         break;

        case  CMD_SENS_CALIB:
            //this->sensor->calibrate();
            //this->hand->sensor.calibrate();
         break;

        default: return false;
        break;
    }
    return true;
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

