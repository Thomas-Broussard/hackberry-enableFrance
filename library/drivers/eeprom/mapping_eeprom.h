/* 
 *  =============================================================================================================================================
 *  Projet : Hackberry e-Nable France
 *  Auteur : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Organization of the EEPROM memory of the Hackberry hand
 *
 *  Memory size of the ATmega328P-AU: 1024 bytes
 *
 *  Maximum storage possible:
 *      2048 characters
 *  or  1024 integers
 *  or  512  float
 *
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#ifndef __MAPPING_EEPROM_H__
#define __MAPPING_EEPROM_H__


/*
#########################################################
        LIMIT POSITIONS OF SERVOMOTORS
#########################################################
*/
#define ADDR_THUMB_MIN          0x000       // int
#define ADDR_THUMB_MAX          0x002       // int

#define ADDR_INDEX_MIN          0x004       // int
#define ADDR_INDEX_MAX          0x006       // int

#define ADDR_FINGERS_MIN         0x008       // int
#define ADDR_FINGERS_MAX         0x00A       // int


/*
#########################################################
        GENERAL PARAMETERS OF THE HAND
#########################################################
*/

// speed of servomotors
#define ADDR_SPEED_MIN        0x100  // int
#define ADDR_SPEED_MAX        0x102  // int
#define ADDR_SPEED_REVERSE    0x104  // int




#endif