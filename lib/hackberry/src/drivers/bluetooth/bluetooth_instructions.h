/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  List of instructions for Hackberry bluetooth library
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __BLUETOOTH_INSTRUCTIONS_H__
#define __BLUETOOTH_INSTRUCTIONS_H__


// General (AT commands)
#define CMD_GEN_TEST        0 // check bluetooth connection
#define CMD_GEN_SET_PASS    1 // set new password
#define CMD_GEN_SET_NAME    2 // set new name
#define CMD_GEN_STOP        3 // stop the bluetooth device
#define CMD_GEN_RESET       4 // reset the parameters

// Servomotors
#define CMD_SRV_MOVE_UP     10 // rotation servo clockwise
#define CMD_SRV_MOVE_DOWN   11 // rotation servo reverse clockwise

#define CMD_SRV_SAVE_MAX    12 // save current position as max limit
#define CMD_SRV_SAVE_MIN    13 // save current position as min limit

#define CMD_SRV_LOAD_MAX    14 // load max limit value
#define CMD_SRV_LOAD_MIN    15 // load min limit value

#define CMD_SRV_SET_HAND    16 // set type of hand (right or left)
#define CMD_SRV_GET_HAND    17 // get current type of hand

#define CMD_SRV_SET_SPEED   18 // set servomotor speed (0 - 100%)
#define CMD_SRV_GET_SPEED   19 // get servomotor speed

#define CMD_SRV_TEST        20 // test servomotors


// Sensors
#define CMD_SENS_GET_VALUE  30 // get current sensor value (0 - 1024)

#define CMD_SENS_SET_TYPE   31 // set type of sensor used (IR, EMG, etc..)
#define CMD_SENS_GET_TYPE   32 // get type of sensor used (IR, EMG, etc..)

#define CMD_SENS_CALIB      33 // launch calibration code





/* end */
#endif