#include "leds_board.h"

Extension_Leds::Extension_Leds()
{

}

void Extension_Leds::init(Hackberry_hand *hand)
{
    this->hand = hand;

    // Initialize X pins
    for (int i = 0; i < NB_X_PINS; i++)
    {
        pinMode(this->_pinX[i],OUTPUT);
    }

    // Initialize Y pins
    for (int i = 0; i < NB_Y_PINS; i++)
    {
        pinMode(this->_pinY[i],OUTPUT);
    }
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
    CLR_X0(); CLR_X1(); CLR_X2();
    CLR_Y0(); CLR_Y1(); CLR_Y2();
}

void Extension_Leds::writeX(unsigned char index, bool state)
{
    switch(index)
    {
        case 0 : state ? X0_ON():X0_OFF(); break;
        case 1 : state ? X1_ON():X1_OFF(); break;
        case 3 : state ? X2_ON():X2_OFF(); break;
    }
}

void Extension_Leds::writeY(unsigned char index, bool state)
{
    switch(index)
    {
        case 0 : state ? Y0_ON():Y0_OFF(); break;
        case 1 : state ? Y1_ON():Y1_OFF(); break;
        case 3 : state ? Y2_ON():Y2_OFF(); break;
    }
}

void Extension_Leds::display()
{
    for (int y = 0 ; y < 3; y++)
    {
        writeY(y,true);
        for(int x = 0 ; x < 3; x++)
        {
            if (pattern[x][y])
            {
                writeX(x,true);
                delayMicroseconds(100); // TODO : try to remove this
                writeX(x,false);
            }
        }
        writeY(y,false);
    }
}

