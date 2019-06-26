#ifndef __LEDS_REGISTERS_H__
#define __LEDS_REGISTERS_H__

// MACROS : Registers manipulation
#define SET(reg,bit) reg |= (1<<bit)
#define CLR(reg,bit) reg &=~(1<<bit)

// turn on the GPIO
#define X0_ON() SET(PORTD,PORTD3)   // D3
#define X1_ON() SET(PORTC,PORTC5)   // A5
#define X2_ON() SET(PORTC,PORTC4)   // A4

#define Y0_ON() CLR(PORTD,PORTD4)   // D4
#define Y1_ON() CLR(PORTD,PORTD7)   // D7
#define Y2_ON() CLR(PORTD,PORTD8)   // D8

// turn off the GPIO
#define X0_OFF() CLR(PORTD,PORTD3)
#define X1_OFF() CLR(PORTC,PORTC5)
#define X2_OFF() CLR(PORTC,PORTC4)

#define Y0_OFF() SET(PORTD,PORTD4)
#define Y1_OFF() SET(PORTD,PORTD7)
#define Y2_OFF() SET(PORTD,PORTD8)

// initialize GPIO as outputs
#define X0_INIT() CLR(DDRD,DDD3)
#define X1_INIT() CLR(DDRC,DDC5)
#define X2_INIT() CLR(DDRC,DDC4)

#define Y0_INIT() CLR(DDRD,DDD4)
#define Y1_INIT() CLR(DDRD,DDD7)
#define Y2_INIT() CLR(DDRD,DDD8)

#endif