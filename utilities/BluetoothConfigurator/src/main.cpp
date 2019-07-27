/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Program used for configuration of bluetooth modules connected to the Hackberry board
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include <Arduino.h>
#include <SoftwareSerial.h>

#define PIN_RX_BT 1
#define PIN_TX_BT 0

SoftwareSerial mySerial(PIN_TX_BT, PIN_RX_BT); // RX, TX

// functions call
void setBaudrate(unsigned long baudrate);
void setName(String newName);
bool setPassword(String password);
void configBluetooth(unsigned long baudrateTried,unsigned long baudTarget);


// baudrate to check
unsigned long baudrate[8] = { 1200,2400,4800,9600,19200,38400,57600,115200};
unsigned long  baudTarget = 38400;

String defaultName = "Hackberry";
String defaultPassword = "0000";
/* 
* ====================================================================================
*                                  Program
* ====================================================================================
*/
void setup()
{
  pinMode(A3,OUTPUT);
  digitalWrite(A3,HIGH);
  delay(500);

  for (int i = 0 ; i < 8 ; i++)
  {
    configBluetooth(baudrate[i],baudTarget);
  }  

  // Set standard name and standard password for bluetooth
  mySerial.begin(baudTarget);
  delay(1000);
  setName(defaultName);
  delay(1000);
  setPassword(defaultPassword);
  delay(1000);

  Serial.begin(baudTarget);
}

void loop()
{
  // check response from bluetooth config
  if (mySerial.available())
  Serial.write(mySerial.read());
  if (Serial.available())
  mySerial.write(Serial.read());
}



/* 
* ====================================================================================
*                                  Functions
* ====================================================================================
*/
void setBaudrate(unsigned long baudrate)
{
  switch(baudrate){
    case 1200     : mySerial.print("AT+BAUD1"); break;
    case 2400     : mySerial.print("AT+BAUD2"); break;
    case 4800     : mySerial.print("AT+BAUD3"); break;
    case 9600     : mySerial.print("AT+BAUD4"); break;
    case 19200    : mySerial.print("AT+BAUD5"); break;
    case 38400    : mySerial.print("AT+BAUD6"); break;
    case 57600    : mySerial.print("AT+BAUD7"); break;
    case 115200   : mySerial.print("AT+BAUD8"); break;
    case 230400   : mySerial.print("AT+BAUD9"); break;
    case 460800   : mySerial.print("AT+BAUDA"); break;
    case 921600   : mySerial.print("AT+BAUDB"); break;
    case 1382400  : mySerial.print("AT+BAUDC"); break;
    default: return; break;
  }
  mySerial.begin(baudrate);
}

void setName(String newName){
  mySerial.print("AT+NAME"+newName);
}

bool setPassword(String password)
{
  String pin = "";
  for (int i = 0; i < 4; i++){
    if (password.charAt(i) < '0' || password.charAt(i) > '9') return false;
  }
  mySerial.print("AT+PIN"+password);
  return true;
}


void configBluetooth(unsigned long baudrateTried,unsigned long baudTarget)
{
  //Serial.println((String)"\nConfigure bluetooth baudrate to " + baudTarget + " bauds with baudrate " + baudrateTried);
  mySerial.begin(baudrateTried);
  delay(1000);
  setBaudrate(baudTarget);
  delay(1000);
}