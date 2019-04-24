/* 
 *  =============================================================================================================================================
 *  Project : Hackberry e-Nable France
 *  Author  : Thomas Broussard
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


/**
 * Constructor of the Servomotor class
 * @param hackberry current Hackberry Hand object in use
 */
Hackberry_servos::Hackberry_servos() {
    
}


/**
 * Servomotor initialization
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry_servos::init(bool selectedHand) {

    // pins initialization
    pinMode(_pinServoIndex, OUTPUT);
    pinMode(_pinServoThumb, OUTPUT);
    pinMode(_pinServoFingers, OUTPUT);

    // Link pins with servomotors    
    servoIndex.attach(_pinServoIndex);
    servoThumb.attach(_pinServoThumb);
    servoFingers.attach(_pinServoFingers);
    

    // Limit positions of servomotors according to the selected hand
    /** TODO: load parameters from the EEPROM */
    if (selectedHand == RIGHT_HAND) {
        openThumb = THUMB_MAX;
        openIndex = INDEX_MAX;
        openFingers = FINGERS_MAX;

        closedThumb = THUMB_MIN;
        closedIndex = INDEX_MIN;
        closedFingers = FINGERS_MIN;
    } 
    
    else if (selectedHand == LEFT_HAND) {
        openThumb = THUMB_MIN;
        openIndex = INDEX_MIN;
        openFingers = FINGERS_MIN;

        closedThumb = THUMB_MAX;
        closedIndex = INDEX_MAX;
        closedFingers = FINGERS_MAX;
    }

    // Test 
    this->closeAll();
    delay(1000);
    this->openAll();
}

/**
 * Move one of the members of the hand
 * 
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param position Desired position for the member
 */
void Hackberry_servos::move(int member, int position) {
    int finalPosition = 0;
    switch (member) {
        case INDEX:
            finalPosition = frameInteger(position, INDEX_MIN, INDEX_MAX);
            this->moveServo(INDEX, finalPosition);
            break;

        case THUMB:
            finalPosition = frameInteger(position, THUMB_MIN, THUMB_MAX);
            this->moveServo(THUMB, finalPosition);
            break;

        case FINGERS:
            finalPosition = frameInteger(position, FINGERS_MIN, FINGERS_MAX);
            this->moveServo(FINGERS, finalPosition);
            break;
    }
}


/**
 * Put one of the hand members to be in the open position
 *
 * @param member Member to open (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::open(int member) {
    switch (member) {
        case THUMB:
            this->move(THUMB, openThumb);
            break;

        case INDEX:
            this->move(INDEX, openIndex);
            break;

        case FINGERS:
            this->move(FINGERS, openFingers);
            break;
    }
}

/**
 * Put one of the hand members to be in the closed position
 *
 * @param member Member to close (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::close(int member) {
    switch (member) {
        case THUMB:
            this->move(THUMB, closedThumb);
            break;

        case INDEX:
            this->move(INDEX, closedIndex);
            break;

        case FINGERS:
            this->move(FINGERS, closedFingers);
            break;
    }
}

/**
 * Put the whole hand in open position
 */
void Hackberry_servos::openAll() {
    this->open(THUMB);
    this->open(INDEX);
    this->open(FINGERS);
}

/**
 * Put the whole hand in closed position
 */
void Hackberry_servos::closeAll() {
    this->close(THUMB);
    this->close(INDEX);
    this->close(FINGERS);
}

/**
 * Moves the servomotor to the desired position
 *
 * @param member Member to move (THUMB, INDEX or FINGERS)
 * @param wantedPosition Position that the servomotor must reach
 */
void Hackberry_servos::moveServo(int member, int wantedPosition) {
    switch (member) 
    {
        case THUMB:
            servoThumb.write(wantedPosition,DEFAULT_SPEED);
            break;

        case INDEX:
            servoIndex.write(wantedPosition,DEFAULT_SPEED);
            break;

        case FINGERS:
            servoFingers.write(wantedPosition,DEFAULT_SPEED);
            break;
    }
}

/**
 * Get the last position of a servomotor
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 * @return last position of the member
 */
int Hackberry_servos::getPosition(int member){
    switch (member) {
        case INDEX:
            return servoIndex.read();
            break;

        case THUMB:
            return servoThumb.read();
            break;

        case FINGERS:
            return servoFingers.read();
            break;

        default: 
            return -1; // error code 
            break;
    }
}


/**
 * Frames an integer between a min value and a max value
 * 
 * @param value Value to frame
 * @param min Min value
 * @param max Max value
 * @return value framed between min and max
 */
int frameInteger(int value, int min, int max) {
    return (value < min) ? min : ((value > max) ? max : value);
}