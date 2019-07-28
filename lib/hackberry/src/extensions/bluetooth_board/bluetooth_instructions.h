/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  List of instructions for Hackberry bluetooth library
 * 
 *  Template of an instruction : 
 * 
 *  CMD;param1;param2;...;paramN
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

/*-----------------------------------
* File generated with cmdlist.py
-----------------------------------*/

#ifndef __BLUETOOTH_INSTRUCTIONS_H__
#define __BLUETOOTH_INSTRUCTIONS_H__

	#define CMD_ERROR			-1
	
//-----------------------------------
//COMMAND LIST GEN
//-----------------------------------
	#define CMD_GEN_TEST 		0 	// check the bluetooth connection.
	#define CMD_GEN_SET_PASS 	1 	// set new bluetooth password.
	#define CMD_GEN_SET_NAME 	2 	// set new name.
	#define CMD_GEN_STOP 		3 	// stop the bluetooth device.
	#define CMD_GEN_RESET 		4 	// reset parameters.
	#define CMD_GEN_VERSION 	5 	// get version of the current software.
	#define CMD_GEN_BATTERY 	6 	// get the current level of battery (or -1 if battery can't be read).
	#define CMD_GEN_BOARD 		7 	// get the name of the main hackberry board.

//-----------------------------------
//COMMAND LIST SRV
//-----------------------------------
	#define CMD_SRV_MOVE 		8 	// move motor to the given position.
	#define CMD_SRV_SAVE_MAX 	9 	// save current position as max limit.
	#define CMD_SRV_SAVE_MIN 	10 	// save current position as min limit.
	#define CMD_SRV_LOAD_MAX 	11 	// load max limit value.
	#define CMD_SRV_LOAD_MIN 	12 	// load min limit value.
	#define CMD_SRV_SET_HAND 	13 	// set type of hand.
	#define CMD_SRV_GET_HAND 	14 	// get current type of hand.
	#define CMD_SRV_SET_SPEED 	15 	// Set the motors speed.
	#define CMD_SRV_GET_SPEED 	16 	// Get the motors speed.
	#define CMD_SRV_TEST 		17 	// Launch the test procedure for motors.
	#define CMD_SRV_ENABLE 		18 	// enable move drived by sensor.
	#define CMD_SRV_DISABLE 	19 	// disable move drived by sensor.

//-----------------------------------
//COMMAND LIST SENS
//-----------------------------------
	#define CMD_SENS_GET_VALUE 	20 	// get current sensor value.
	#define CMD_SENS_SET_TYPE 	21 	// set type of sensor used (IR,EMG,etc…).
	#define CMD_SENS_GET_TYPE 	22 	// get type of sensor used (IR,EMG,etc…).
	#define CMD_SENS_CALIB 		23 	// launch sensor calibration.

//-----------------------------------
//COMMAND LIST SRV
//-----------------------------------
	#define CMD_SRV_GET_POS 	24 	// get the current position of a servomotor.
	#define CMD_SRV_FORCE_MOVE 	25 	// forced move motor to the given position.

#endif