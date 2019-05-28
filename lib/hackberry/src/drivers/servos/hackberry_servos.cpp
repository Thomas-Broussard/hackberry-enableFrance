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
Hackberry_servos::Hackberry_servos(int indexPin, int thumbPin, int fingersPin) {
    _pinServoIndex  = indexPin;
    _pinServoThumb  = thumbPin;
    _pinServoFingers = fingersPin;
}


/**
 * Servomotor initialization
 * 
 * @param selectedHand Direction of the hand (RIGHT_HAND or LEFT_HAND)
 */
void Hackberry_servos::init(bool selectedHand) {

    // default parameters
    _speed = DEFAULT_SPEED;

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


}


/**
 * Set the speed of the servomotors
 * 
 * @param speed speed required (from 1 to 255)
 */ 
void Hackberry_servos::setSpeed(int speed){
    this->_speed = speed;
}

/**
 * Get the speed of the servomotors
 * 
 * @return speed of servomotors (from 1 to 255)
 */ 
int Hackberry_servos::getSpeed(){
    return this->_speed;
}

/**
 * Move one of the members of the hand
 * (Absolute move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param position Desired position for the member
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::move(int member, int position,bool waitEnabled) {
    int finalPosition = 0;
    switch (member) {
        case INDEX:
            finalPosition = frameInteger(position, INDEX_MIN, INDEX_MAX);
            this->moveServo(INDEX, finalPosition,waitEnabled);
            break;

        case THUMB:
            finalPosition = frameInteger(position, THUMB_MIN, THUMB_MAX);
            this->moveServo(THUMB, finalPosition,waitEnabled);
            break;

        case FINGERS:
            finalPosition = frameInteger(position, FINGERS_MIN, FINGERS_MAX);
            this->moveServo(FINGERS, finalPosition,waitEnabled);
            break;
    }
}

/**
 * Move one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree 
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeMove(int member, int degree,bool waitEnabled) 
{
    int position = this->getPosition(member) + degree;
    this->move(member,position,waitEnabled);
}


/**
 * Put one of the hand members to be in the open position
 *
 * @param member Member to open (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::open(int member) {
    switch (member) {
        case THUMB:
            this->move(THUMB, openThumb,true);
            break;

        case INDEX:
            this->move(INDEX, openIndex,true);
            break;

        case FINGERS:
            this->move(FINGERS, openFingers,true);
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
            this->move(THUMB, closedThumb,true);
            break;

        case INDEX:
            this->move(INDEX, closedIndex,true);
            break;

        case FINGERS:
            this->move(FINGERS, closedFingers,true);
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
            servoThumb.write(wantedPosition,this->_speed);
            break;

        case INDEX:
            servoIndex.write(wantedPosition,this->_speed);
            break;

        case FINGERS:
            servoFingers.write(wantedPosition,this->_speed);
            break;
    }
}


/**
 * Moves the servomotor to the desired position
 *
 * @param member Member to move (THUMB, INDEX or FINGERS)
 * @param wantedPosition Position that the servomotor must reach
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::moveServo(int member, int wantedPosition, bool waitEnabled) {
    switch (member) 
    {
        case THUMB:
            servoThumb.write(wantedPosition,this->_speed);
            if (waitEnabled) servoThumb.wait();
            break;

        case INDEX:
            servoIndex.write(wantedPosition,this->_speed);
            if (waitEnabled) servoIndex.wait();
            break;

        case FINGERS:
            servoFingers.write(wantedPosition,this->_speed);
            if (waitEnabled) servoFingers.wait();
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