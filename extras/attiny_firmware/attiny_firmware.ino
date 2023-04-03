/**
 **************************************************
 *
 * @file        attiny_firmware.ino
 * @brief       Firmware for the attiny on the breakout.
 *
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

// Include needed libraries and files
#include "OneButton.h"
#include "Wire.h"
#include "easyC.h"

// Setup a OneButton on pin PA6
OneButton button(PA6, true);

// Rotary Encoder Inputs
#define CLK 9
#define DT  10

int addr = DEFAULT_ADDRESS; // 0x30

volatile long counter = 0; // For counting rotations, +1 if the rotary is rotated clockwise or -1 if the rotary is
                           // rotated in another  direction
volatile byte state = 0;   // For holding a state of the breakout
int currentStateCLK;       // For reading the state of the clock pin
int lastStateCLK;          // For the last state of the clock pin


void setup()
{
    // Set the select address switches as inputs and get the I2C address
    initDefault();
    addr = getI2CAddress();

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    // Set encoder pins as inputs
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);

    // Link the button functions.
    button.attachClick(click1);
    button.attachDoubleClick(doubleclick1);
    button.attachLongPressStop(longPressStop1);
    button.attachDuringLongPress(longPress1);
}

void loop()
{
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
    {

        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK)
        {
            counter--;
            state = 5;
        }
        else
        {
            // Encoder is rotating CW so increment
            counter++;
            state = 6;
        }
    }

    // Remember last CLK state
    lastStateCLK = currentStateCLK;

    // Keep watching the push button
    button.tick();
}

// When the breakout receives the data over I2C, this function is executing
void receiveEvent(int howMany)
{
    byte resetCounter;

    // When Dasduino sends 1 byte, this is for reseting the counter
    if (Wire.available() == 1)
    {
        resetCounter = Wire.read();
    }

    // Dasduino sends 170 for reseting the counter
    if (resetCounter == 170)
    {
        counter = 0;
    }
}

// This function will be executed when Dasduino requests data from the breakout
void requestEvent()
{
    // Here is needed to convert the counter value into bytes appropriate for sending
    uint8_t *counterToSend = (uint8_t *)&counter; // One uint32_t converted to 4 uint8_t
    Wire.write(counterToSend, 4);                 // Send 4 uint8_t (bytes)

    // Send 1 byte which represents the state of the rotary encoder
    Wire.write(state);
    state = 0;
}

// This function will be called when the button was pressed 1 time
void click1()
{
    state = 1;
}

// This function will be called when the button was pressed 2 times in a short timeframe
void doubleclick1()
{
    state = 2;
}


// This function will be called often, while the button is pressed for a long time
void longPress1()
{
    state = 3;
}

// This function will be called once, when the button is released after beeing pressed for a long time
void longPressStop1()
{
    state = 4;
}
