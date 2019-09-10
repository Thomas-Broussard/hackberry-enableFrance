
#include "ADC_interruptible.h"
ADC_interruptible::ADC_interruptible(){}

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

volatile byte ADC_interruptible::ADC_inProgress = false;
volatile byte ADC_interruptible::ADC_interrupted = false;


int  ADC_interruptible::readFromIT(int pin)
{//call from interrupt service routine
    int value;

    if(ADC_interruptible::ADC_inProgress==false)
    {
        value = analogRead(pin);
        return value;
    }
    else //ADC interrupted
    {
        delayMicroseconds(100);// wait pending conversion end 
        value = analogRead(pin);
        ADC_interruptible::ADC_interrupted = true;
        return value;
    }
}
int  ADC_interruptible::read(int pin)
{   //call from background
    int value;
    ADC_interruptible::ADC_inProgress=true;
    do
    {
        ADC_interruptible::ADC_interrupted = false;
        value = analogRead(pin);
    } while (ADC_interruptible::ADC_interrupted);
    ADC_interruptible::ADC_inProgress=false;
return value;
}