/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for debugging the Hackberry hand
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "hackberry_debug.h"

/**
 * Constructor
 * 
 * @param hackberry current Hackberry Hand object in use
 */
Hackberry_debug::Hackberry_debug(Hackberry hackberry)
{
    this->_hackberry = hackberry;
}


/**
 * Print all debug information on the serial monitor
 * 
 */
void Hackberry_debug::printAll(){
  DebugPrintln("\n\n#######################################"); 
  DebugPrintln("\n\n########## DEBUG HACKBERRY ############");   
  DebugPrintln("\n\n#######################################"); 
  /**
   * TODO : Add debug info here
  */
  DebugPrintln("#######################################\n"); 
}


