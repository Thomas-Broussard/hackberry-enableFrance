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
void Hackberry_servos::init() {
    // pins initialization
    pinMode(this->_pinServoIndex, OUTPUT);
    pinMode(this->_pinServoThumb, OUTPUT);
    pinMode(this->_pinServoFingers, OUTPUT);

    // Link pins with servomotors    
    this->servoIndex.attach(_pinServoIndex);
    this->servoThumb.attach(_pinServoThumb);
    this->servoFingers.attach(_pinServoFingers);
    
    // Limit positions of servomotors according to the selected hand
    /** TODO: load parameters from the EEPROM */
    this->setLimitPositions(THUMB,THUMB_MIN,THUMB_MAX);
    this->setLimitPositions(INDEX,INDEX_MIN,INDEX_MAX);
    this->setLimitPositions(FINGERS,FINGERS_MIN,FINGERS_MAX);
}

/**
 * Set the hand used
 * 
 * @param selectedHand true (RIGHT_HAND) or false (LEFT_HAND)
 */ 
void Hackberry_servos::setHand(bool selectedHand)
{
    this->_selectedHand = selectedHand;
    this->setLimitPositions(THUMB,this->_openThumb,this->_closedThumb);
    this->setLimitPositions(INDEX,this->_openIndex,this->_closedIndex);
    this->setLimitPositions(FINGERS,this->_openFingers,this->_closedFingers);
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
    switch (member) 
    {
        case INDEX:
            if (this->_lockIndex) return;
            finalPosition = this->frameInteger(position, this->_openIndex, this->_closedIndex);
            this->moveServo(INDEX, finalPosition,waitEnabled);
            break;

        case THUMB:
            if (this->_lockThumb) return;
            finalPosition =this->frameInteger(position, this->_openThumb, this->_closedThumb);
            this->moveServo(THUMB, finalPosition,waitEnabled);
            break;

        case FINGERS:
            if (this->_lockFingers) return;
            finalPosition = this->frameInteger(position, this->_openFingers, this->_closedFingers);
            this->moveServo(FINGERS, finalPosition,waitEnabled);
            break;

        default:
            break;
    }
}

/**
 * Move one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree (between -180 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeMove(int member, int degree,bool waitEnabled) 
{
    int position = this->getPosition(member) + degree;
    this->move(member,position,waitEnabled);
}

/**
 * Open one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree  (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeOpen(int member, int degree,bool waitEnabled) 
{
    int openDegree =  (this->_selectedHand == RIGHT_HAND) ? degree:-degree;
    this->relativeMove(member,openDegree,waitEnabled);
}

/**
 * Close one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeClose(int member, int degree,bool waitEnabled) 
{
    int closeDegree = (this->_selectedHand == RIGHT_HAND) ? -degree:degree;
    this->relativeMove(member,closeDegree,waitEnabled);
}


/**
 * Put one of the hand members to be in the open position
 *
 * @param member Member to open (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::open(int member) {
    switch (member) {
        case THUMB:
            this->move(THUMB, this->_openThumb,true);
            break;

        case INDEX:
            this->move(INDEX, this->_openIndex,true);
            break;

        case FINGERS:
            this->move(FINGERS, this->_openFingers,true);
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
            this->move(THUMB, this->_closedThumb,true);
            break;

        case INDEX:
            this->move(INDEX, this->_closedIndex,true);
            break;

        case FINGERS:
            this->move(FINGERS, this->_closedFingers,true);
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
    switch (member) 
    {
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
 * Get the open position of a servomotor
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 * @return open position of the member
 */
int Hackberry_servos::getOpenPosition(int member){
    switch (member) 
    {
        case INDEX:
            return this->_openIndex;
            break;

        case THUMB:
            return this->_openThumb;
            break;

        case FINGERS:
            return this->_openFingers;
            break;

        default: 
            return -1; // error code 
            break;
    }
}

/**
 * Get the close position of a servomotor
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 * @return close position of the member
 */
int Hackberry_servos::getClosePosition(int member){
    switch (member) 
    {
        case INDEX:
            return this->_closedIndex;
            break;

        case THUMB:
            return this->_closedThumb;
            break;  

        case FINGERS:
            return this->_closedFingers;
            break;

        default: 
            return -1; // error code 
            break;
    }
}


/**
 * Set the two limit positions of a servomotor as open and close position
 * (depending on selected hand)
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 * @return close position of the member
 */
void Hackberry_servos::setLimitPositions(int member, int limit1, int limit2)
{
    // 1 - define the min and max limit
    int frame1 = this->frameInteger(limit1,0,180);
    int frame2 = this->frameInteger(limit2,0,180);
    int min = (frame1 < frame2) ? frame1:frame2;
    int max = (frame1 > frame2) ? frame1:frame2;

    // 2 - set min and max as open and close position (depending on selected hand)
    int open =  (this->_selectedHand == RIGHT_HAND) ? max:min;
    int close = (this->_selectedHand == RIGHT_HAND) ? min:max;

    // 3 - set open and close position to the member
    switch (member) 
    {
        case INDEX:
                this->_openIndex = open;
                this->_closedIndex = close;
            break;

        case THUMB:
                this->_openThumb = open;
                this->_closedThumb = close;
            break;

        case FINGERS:
                this->_openFingers = open;
                this->_closedFingers = close;
            break;

        default: 
            break;
    }
}

/**
 * Lock a member (the member can't move anymore)
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::lockMember(int member)
{
    switch (member) 
    {
        case INDEX:
                this->_lockIndex = true;
            break;

        case THUMB:
                this->_lockThumb = true;
            break;

        case FINGERS:
                this->_lockFingers = true;
            break;

        default: 
            break;
    }
}

/**
 * Unlock a member (the member can move)
 *
 * @param member Member required (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::unlockMember(int member)
{
    switch (member) 
    {
        case INDEX:
                this->_lockIndex = false;
            break;

        case THUMB:
                this->_lockThumb = false;
            break;

        case FINGERS:
                this->_lockFingers = false;
            break;

        default: 
            break;
    }
}


/**
 * Frames an integer between a min value and a max value
 * 
 * @param value Value to frame
 * @param lim1 first limit value
 * @param lim2 second limit value
 * @return value framed between min and max
 */
int Hackberry_servos::frameInteger(int value, int lim1, int lim2) {
    int min = (lim1 < lim2) ? lim1 : lim2;
    int max = (lim1 > lim2) ? lim1 : lim2;
    return constrain(value,min,max);
}