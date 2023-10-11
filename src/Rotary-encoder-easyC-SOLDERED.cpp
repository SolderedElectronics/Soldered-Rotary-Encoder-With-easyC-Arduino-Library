/**
 **************************************************
 *
 * @file        Rotary-encoder-easyC-SOLDERED.cpp
 * @brief       Functions for the rotary encoder with easyC
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/


#include "Rotary-encoder-easyC-SOLDERED.h"

/**
 * @brief                   Rotary specific native constructor.
 */
Rotary::Rotary()
{
    native = 0;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void Rotary::initializeNative()
{
}

/**
 * @brief                   Get data from the breakout and store them in class variables.
 */
void Rotary::getData()
{
    byte counterRaw[4];
    byte state, btnState;
    long counter;

    Wire.requestFrom(address, 5);

    if (Wire.available() == 5)
    {
        Wire.readBytes(counterRaw, 4);
        counter = *(long *)counterRaw;
        rotaryCounter = counter;

        state = Wire.read();
        rotaryState = state;
    }
}

/**
 * @brief                   Get counter from rotary encoder breakout.
 *
 * @return                  Counter variable.
 */
long Rotary::getCount()
{
    getData();
    return rotaryCounter;
}

/**
 * @brief                   Get state of the rotary encoder.
 *
 * @return                  0 If the rotary encoder doesn't move
 *                          1 If the button is presed once
 *                          2 If the button is pressed twice
 *                          3 If the button is long pressed
 *                          4 For long button press release
 *                          5 If the rotary encoder rotates counterclockwise
 *                          6 If the rotary encoder rotates clockwise
 */
byte Rotary::getState()
{
    getData();
    return rotaryState;
}

/**
 * @brief                   Reset the internal counter on the breakout.
 */
void Rotary::resetCounter()
{
    // Send 1 byte to reset the counter variable
    byte resetFlag = 170;
    sendData(&resetFlag, 1);
}