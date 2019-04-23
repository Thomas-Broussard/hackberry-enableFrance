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


#ifndef __HACKBERRY_DEBUG_H__
#define __HACKBERRY_DEBUG_H__

// dépendances
#include "hackberry.h"

// Display print on the serial monitor only if Debug mode is enabled
// (Comment "#define DEBUG_EXII" to disable all prints)
#define DEBUG_EXII

#ifdef DEBUG_EXII
   #define DebugPrintln(x)  Serial.println(x)
   #define DebugPrint(x)    Serial.print(x)
#else
   #define DebugPrintln(x)
   #define DebugPrint(x)  
#endif

// class
class Hackberry_debug{

    public: 
    Hackberry_debug(Hackberry _hackberry);

    void printAll();
    
    private:

    // Hackberry Hand
    Hackberry _hackberry;
};




#endif