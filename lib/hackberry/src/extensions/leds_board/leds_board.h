/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description : Extension board with LEDS stripe
 * 
 *  leds are driven as a matrix of 3x3 , but used as a led stripe (from 0 to 8)
 * 
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */


#include <Arduino.h>
#include "hackberry_global.h"
#include "drivers/hackberry_hand.h"
#include "leds_register.h"


// class
class Extension_Leds{

    public: 
        Extension_Leds();
        void init(Hackberry_hand *hand);
        void display();
        void write(unsigned char index, bool state);
        void clear();
        

    private:
        Hackberry_hand *hand;
        bool _pattern[3][3];    

        void writeX(unsigned char index, bool state);
        void writeY(unsigned char index, bool state);     
};
