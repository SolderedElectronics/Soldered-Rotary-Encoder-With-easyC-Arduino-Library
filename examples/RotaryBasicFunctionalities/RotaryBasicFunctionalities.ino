/**
 **************************************************
 *
 * @file        RotaryBasicFunctionalities.ino
 * @brief       Example for the rotary encoder with easyC.
 *
 *              For this example you will need any Dasduino board, a USB-c cable, Rotary encoder with easyC, and easyC cable. 
 *              Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
 *              Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 *
 *              This example will show you how you can use rotary encoder functionalities.
 *              Upload the code to the Dasduino and open the Serial Monitor at 115200 baud rate to see what's happening.
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

// Include Soldered library for the rotary encoder with easyC
#include "Rotary-encoder-easyC-SOLDERED.h"

// Create an objest for the rotary encoder
Rotary rotary;

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);

    // Start I2C communication on default address (0x30)
    rotary.begin();

    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // rotary.begin(0x31);
}

void loop()
{
    // getState() function returns the current state of the rotary encoder
    // It MUST BE in the loop() and run constantly to get proper readings
    int state = rotary.getState();

    // If the state is zero or ROTARY_IDLE constant, the rotary encoder is not moving
    if (state != ROTARY_IDLE)
    {
        switch (state)
        {
        case ROTARY_CW:
            // The rotary is rotated in the clockwise direction
            Serial.println("Rotated clockwise");
            break;
        case ROTARY_CCW:
            // The rotary is rotated in the counter-clockwise direction
            Serial.println("Rotated counter clockwise");
            break;
        case BTN_CLICK:
            // If the button is pressed once
            Serial.println("Button single click");
            break;
        case BTN_DOUBLE_CLICK:
            // If the button is double-pressed
            Serial.println("Button double click");
            break;
        case BTN_LONG_PRESS:
            // If the button is long pressed
            Serial.println("Button long click");
            break;
        case BTN_LONG_RELEASE:
            // When the long-pressed button is released
            Serial.println("Button long click release");
            break;
        }
    }
}
