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

    Wire.beginTransmission(0x30);
    Wire.requestFrom(0x30, 5);

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
 * @return                  0 if the rotary encoder doesn't move
 *                          1 if the rotary encoder rotates clockwise
 *                          2 if the rotary encoder rotates counterclockwise
 *                          3 if the button is pressed                          
 */
byte Rotary::getState()
{
    getData();
    return rotaryState;
}