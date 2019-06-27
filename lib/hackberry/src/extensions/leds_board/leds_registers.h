#ifndef __LEDS_REGISTERS_H__
#define __LEDS_REGISTERS_H__

// MACROS : Registers manipulation
#define SET(reg,bit) reg |= (1<<bit)
#define CLR(reg,bit) reg &=~(1<<bit)

// X0 (A5)
#define X0_INIT() SET(DDRC,5)
#define X0_ON() SET(PORTC,5)
#define X0_OFF() CLR(PORTC,5)

// X1 (A4)
#define X1_INIT() SET(DDRC,4)
#define X1_ON() SET(PORTC,4)
#define X1_OFF() CLR(PORTC,4)

// X2 (A3)
#define X2_INIT() SET(DDRC,3)
#define X2_ON() SET(PORTC,3)
#define X2_OFF() CLR(PORTC,3)


// Y0 (D3)
#define Y0_INIT() SET(DDRD,3)
#define Y0_ON() CLR(PORTD,3)
#define Y0_OFF() SET(PORTD,3)

// Y1 (D4)
#define Y1_INIT() SET(DDRD,4)
#define Y1_ON() CLR(PORTD,4)
#define Y1_OFF() SET(PORTD,4)

// Y2 (D0)
#define Y2_INIT() SET(DDRD,0)
#define Y2_ON() CLR(PORTD,0)   // D0
#define Y2_OFF() SET(PORTD,0)


#endif