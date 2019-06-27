#include "leds_board.h"

Extension_Leds::Extension_Leds()
{
    this->init();
    //this->write(0,true);
    this->write(1,true);
    //this->write(2,true);

    this->write(3,true);
    //this->write(4,true);
    this->write(5,true);

    //this->write(6,true);
    this->write(7,true);
    //this->write(8,true);
}

void Extension_Leds::init(Hackberry_hand *hand)
{
    this->hand = hand;

    // initialize pins as GPIO
    X0_INIT(); X1_INIT(); X2_INIT();
    Y0_INIT(); Y1_INIT(); Y2_INIT();
}

void Extension_Leds::init()
{
    // initialize pins as GPIO
    X0_INIT(); X1_INIT(); X2_INIT();
    Y0_INIT(); Y1_INIT(); Y2_INIT();
}

void Extension_Leds::write(unsigned char ledNumber, bool state)
{
    switch(ledNumber)
    {
        case 0 : this->_pattern[0][0] = state; break;
        case 1 : this->_pattern[1][0] = state; break;
        case 2 : this->_pattern[2][0] = state; break;
        case 3 : this->_pattern[0][1] = state; break;
        case 4 : this->_pattern[1][1] = state; break;
        case 5 : this->_pattern[2][1] = state; break;
        case 6 : this->_pattern[0][2] = state; break;
        case 7 : this->_pattern[1][2] = state; break;
        case 8 : this->_pattern[2][2] = state; break;
    }
    
}

void Extension_Leds::clear()
{
    X0_OFF(); X1_OFF(); X2_OFF();
    Y0_OFF(); Y1_OFF(); Y2_OFF();
}

void Extension_Leds::writeX(unsigned char index, bool state)
{
    switch(index)
    {
        case 0 : if(state) X0_ON(); else X0_OFF(); break;
        case 1 : if(state) X1_ON(); else X1_OFF(); break;
        case 2 : if(state) X2_ON(); else X2_OFF(); break;
        default:break;
    }
}

void Extension_Leds::writeY(unsigned char index, bool state)
{
    switch(index)
    {
        case 0 : if(state) Y0_ON(); else Y0_OFF(); break;
        case 1 : if(state) Y1_ON(); else Y1_OFF(); break;
        case 2 : if(state) Y2_ON(); else Y2_OFF(); break;
        default:break;
    }
}

void Extension_Leds::display()
{
    for (int y = 0 ; y < 3; y++)
    {
        writeY(y,true);
        for(int x = 0 ; x < 3; x++)
        {
            if (_pattern[x][y])
            {
                writeX(x,true);
                delayMicroseconds(200); // TODO : try to remove this
                writeX(x,false);
            }
        }
        writeY(y,false);
    }
}

