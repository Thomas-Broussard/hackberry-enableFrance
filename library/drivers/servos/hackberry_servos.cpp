/* 
 *  =============================================================================================================================================
 *  Projet : Hackberry e-Nable France
 *  Auteur : Thomas Broussard
 * 
 *  ---------------------------------------------------------------------------------------------------------------------------------------------
 *  Description :
 *  Library for controlling Hackberry hand servomotors
 * 
 *  Credits : 
 *  Program inspired by the HACKberry project, created by exiii Inc.
 *  https://github.com/mission-arm/HACKberry
 * =============================================================================================================================================
 */

#include "hackberry_servos.h"



Hackberry_servos::Hackberry_servos(Hackberry hackberry)
{
    this->_hackberry = hackberry;
}


/**
 * initialise les servomoteurs
 */
void Hackberry_servos::init(bool mainChoisie)
{
    // initialisation des pins
    pinMode(_pinServoIndex, OUTPUT);
    pinMode(_pinServoTHUMB, OUTPUT);
    pinMode(_pinServoFINGERS, OUTPUT);

    // Association des pins aux servomoteurs
    servoIndex.attach(_pinServoIndex);
    servoTHUMB.attach(_pinServoTHUMB);
    servoFINGERS.attach(_pinServoFINGERS);

    // Positions limites des servomoteurs selon la main choisie
    /** TODO : charger les paramètres depuis la mémoire EEPROM */
    if (selectedHand == RIGHT_HAND)
    {
        THUMBOuvert     = THUMB_MAX;
        IndexOuvert     = INDEX_MAX;
        FINGERSOuvert    = FINGERS_MAX;

        closedThumb      = THUMB_MIN;
        closedIndex      = INDEX_MIN;
        closedFingers     = FINGERS_MIN;
    }
    else if (selectedHand == LEFT_HAND)
    {
        THUMBOuvert     = THUMB_MIN;
        IndexOuvert     = INDEX_MIN;
        FINGERSOuvert    = FINGERS_MIN;

        THUMBFerme      = THUMB_MAX;
        IndexFerme      = INDEX_MAX;
        FINGERSFerme     = FINGERS_MAX;
    }
}

/**
 * Allows to move one of the members of the hand
 * 
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param position Desired position for the member
 */
void Hackberry_servos::move(int member, int position)
{
    int finalPosition = 0;
    switch (member)
    {
        case INDEX : 
            finalPosition = limite(position,INDEX_MIN,INDEX_MAX);
            this->moveServo(servoIndex,finalPosition);
        break;

        case THUMB : 
            finalPosition = limite(position,THUMB_MIN,THUMB_MAX);
            this->moveServo(servoTHUMB,finalPosition);
        break;        

        case FINGERS : 
            finalPosition = limite(position,FINGERS_MIN,FINGERS_MAX);
            this->moveServo(servoFINGERS,finalPosition);
        break;
    }
}


/**
 * Allows one of the hand members to be in the open position
 *
 * @param member Member to open (INCH, INDEX or FINGERS)
 */
void Hackberry_servos::open(int member)
{
    switch (member)
    {
        case THUMB : 
            this->move(THUMB,openThumb); 
        break;

        case INDEX : 
            this->move(INDEX,openIndex); 
        break;

        case FINGERS : 
            this->move(FINGERS,openFingers); 
        break;
    }
}

/**
 * Allows one of the hand members to be in the closed position
 *
 * @param member Member to close (INCH, INDEX or FINGERS)
 */
void Hackberry_servos::close(int member)
{
    switch (member)
    {
        case THUMB : 
            this->move(THUMB,closedThumb); 
        break;

        case INDEX : 
            this->move(INDEX,closedIndex); 
        break;

        case FINGERS : 
            this->move(FINGERS,closedFingers); 
        break;
    }
}

/**
 * Allows to put the whole hand in open position
 */
void Hackberry_servos::openAll()
{
    this->open(THUMB);
    this->open(INDEX);
    this->open(FINGERS);
}
 
/**
 * Allows to put the whole hand in closed position
 */
void Hackberry_servos::closeAll()
{
    this->close(THUMB);
    this->close(INDEX);
    this->close(FINGERS);
}

/**
 * Moves the servomotor to the desired position
 *
 * @param servo Servomotor to move
 * @param wantedPosition Position that the servomotor must reach
 */
void Hackberry_servos::moveServo(Servo servo, int wantedPosition)
{
    int step = 1; // number of degrees that the servomotor will go through each loop
    int currentPosition = servo.read();
    int Angle = wantedPosition - currentPosition;
    
    if (Angle > 0){
        for (int i = 0 ; i < Angle ; i+= step ))
        {
            servo.write(currentPosition + i);
        }
    }

    else if (Angle < 0){
        for (int i = 0 ; i > Angle ; i-= step ))
        {
            servo.write(currentPosition + i);
        }
    }
}