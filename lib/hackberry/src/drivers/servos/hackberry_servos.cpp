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
Hackberry_servos::Hackberry_servos(unsigned char indexPin, unsigned char thumbPin, unsigned char fingersPin) {
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

    // set default parameters
    this->setSpeed(DEFAULT_SPEED);

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


bool Hackberry_servos::getHand()
{
    return this->_selectedHand;
}
/**
 * Change the hand used (useful to change the servomotors direction)
 */ 
void Hackberry_servos::changeHand()
{
    this->_selectedHand = !this->_selectedHand; 
}



/**
 * Set the speed of the servomotors
 * 
 * @param speed speed required (from 1 to 255)
 */ 
void Hackberry_servos::setSpeed(unsigned char  speed){
    this->_speed = constrain(speed,0,100);
}

/**
 * Get the speed of the servomotors
 * 
 * @return speed of servomotors (from 1 to 255)
 */ 
unsigned char  Hackberry_servos::getSpeed(){
    return this->_speed;
}

/**
 * Move one of the members of the hand
 * (Absolute move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param position Desired position for the member
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::move(unsigned char member, unsigned char position,bool waitEnabled) {
    unsigned char finalPosition = 0;
    switch (member) 
    {
        case INDEX:
            if (this->_lockIndex) return;
            finalPosition = this->framePosition(position, this->_openIndex, this->_closedIndex);
            this->moveServo(INDEX, finalPosition,waitEnabled);
            break;

        case THUMB:
            if (this->_lockThumb) return;
            finalPosition =this->framePosition(position, this->_openThumb, this->_closedThumb);
            this->moveServo(THUMB, finalPosition,waitEnabled);
            break;

        case FINGERS:
            if (this->_lockFingers) return;
            finalPosition = this->framePosition(position, this->_openFingers, this->_closedFingers);
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
void Hackberry_servos::relativeMove(unsigned char member, unsigned char degree,bool waitEnabled) 
{
    unsigned char position = this->getPosition(member) + degree;
    this->move(member,position,waitEnabled);
}

/**
 * Open one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree  (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeOpen(unsigned char member, unsigned char degree,bool waitEnabled) 
{
    unsigned char openDegree =  (this->_selectedHand == RIGHT_HAND) ? degree:-degree;
    this->relativeMove(member,openDegree,waitEnabled);
}

/**
 * Close one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::relativeClose(unsigned char member, unsigned char degree,bool waitEnabled) 
{
    unsigned char closeDegree = (this->_selectedHand == RIGHT_HAND) ? -degree:degree;
    this->relativeMove(member,closeDegree,waitEnabled);
}


/**
 * Put one of the hand members to be in the open position
 *
 * @param member Member to open (THUMB, INDEX or FINGERS)
 */
void Hackberry_servos::open(unsigned char member) {
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
void Hackberry_servos::close(unsigned char member) {
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
void Hackberry_servos::moveServo(unsigned char member, unsigned char wantedPosition) {
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
void Hackberry_servos::moveServo(unsigned char member, unsigned char wantedPosition, bool waitEnabled) {
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
unsigned char Hackberry_servos::getPosition(unsigned char  member){
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
unsigned char  Hackberry_servos::getOpenPosition(unsigned char member){
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
unsigned char  Hackberry_servos::getClosePosition(unsigned char member){
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
void Hackberry_servos::setLimitPositions(unsigned char member, unsigned char limit1, unsigned char limit2)
{
    // 1 - define the min and max limit
    unsigned char frame1 = this->framePosition(limit1,0,180);
    unsigned char frame2 = this->framePosition(limit2,0,180);
    unsigned char min = (frame1 < frame2) ? frame1:frame2;
    unsigned char max = (frame1 > frame2) ? frame1:frame2;

    // 2 - set min and max as open and close position (depending on selected hand)
    unsigned char open =  (this->_selectedHand == RIGHT_HAND) ? max:min;
    unsigned char close = (this->_selectedHand == RIGHT_HAND) ? min:max;

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
void Hackberry_servos::lockMember(unsigned char member)
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
void Hackberry_servos::unlockMember(unsigned char member)
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
unsigned char Hackberry_servos::framePosition(unsigned char value, unsigned char lim1, unsigned char lim2) {
    unsigned char min = (lim1 < lim2) ? lim1 : lim2;
    unsigned char max = (lim1 > lim2) ? lim1 : lim2;
    return constrain(value,min,max);
}


/**
 *  move one of the members of the hand
 * (Absolute move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param position Desired position for the member
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::forceMove(unsigned char member, unsigned char position) {
    unsigned char finalPosition = constrain(position, 0, 180);
    this->moveServo(member, finalPosition,false);
}

/**
 * Force Move one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree (between -180 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::forceRelativeMove(unsigned char member, unsigned char degree) 
{
    unsigned char position = this->getPosition(member) + degree;
    this->forceMove(member,position);
}

/**
 * Force Open one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree  (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::forceRelativeOpen(unsigned char member, unsigned char degree) 
{
    unsigned char openDegree =  (this->_selectedHand == RIGHT_HAND) ? degree:-degree;
    this->forceRelativeMove(member,openDegree);
}

/**
 * Force Close one of the members of the hand
 * (Relative move)
 * @param membre Member to move  (THUMB, INDEX or FINGERS)
 * @param degree number of rotation degree (between 0 and 180°)
 * @param waitEnabled true : wait the end of the move to do another action
 */
void Hackberry_servos::forceRelativeClose(unsigned char member, unsigned char degree) 
{
    unsigned char closeDegree = (this->_selectedHand == RIGHT_HAND) ? -degree:degree;
    this->forceRelativeMove(member,closeDegree);
}