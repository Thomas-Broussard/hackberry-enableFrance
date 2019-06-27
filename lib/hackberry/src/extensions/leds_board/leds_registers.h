#ifndef __LEDS_REGISTERS_H__
#define __LEDS_REGISTERS_H__

// MACROS : Registers manipulation
#define SET(reg,bit) reg |= (1<<bit)
#define CLR(reg,bit) reg &=~(1<<bit)

// turn on the GPIO
#define X0_ON() SET(PORTD,3)   // D3
#define X1_ON() SET(PORTC,5)   // A5
#define X2_ON() SET(PORTC,4)   // A4

#define Y0_ON() CLR(PORTD,4)   // D4
#define Y1_ON() CLR(PORTD,7)   // D7
#define Y2_ON() CLR(PORTB,0)   // D8

// turn off the GPIO
#define X0_OFF() CLR(PORTD,3)
#define X1_OFF() CLR(PORTC,5)
#define X2_OFF() CLR(PORTC,4)

#define Y0_OFF() SET(PORTD,4)
#define Y1_OFF() SET(PORTD,7)
#define Y2_OFF() SET(PORTB,0)

// initialize GPIO as outputs
#define X0_INIT() SET(DDRD,3)
#define X1_INIT() SET(DDRC,5)
#define X2_INIT() SET(DDRC,4)

#define Y0_INIT() SET(DDRD,4)
#define Y1_INIT() SET(DDRD,7)
#define Y2_INIT() SET(DDRB,0)

#endif