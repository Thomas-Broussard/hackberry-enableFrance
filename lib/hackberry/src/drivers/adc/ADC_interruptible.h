/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Joël Liénard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : 
 *    Library for secure acces to ADC from background and interrupt service routine
 * 
 * =============================================================================================================================================
 */
#ifndef __ADC_interruptible_H__
#define __ADC_interruptible_H__

#include <Arduino.h>

class ADC_interruptible{
public:
 ADC_interruptible();
 static int read(int pin);  //from background
 static int readFromIT(int pin); //from interrupt service routine

    static volatile byte ADC_inProgress;
    static volatile byte ADC_interrupted;
};


#endif