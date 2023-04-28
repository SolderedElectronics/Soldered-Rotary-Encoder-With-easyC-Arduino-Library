/**
 **************************************************
 *
 * @file        RotaryCounter.ino
 * @brief       Example for the rotary encoder with easyC.
 *
 *              For this example you will need any Dasduino board, a USB-C cable, Rotary encoder with easyC, and easyC cable. 
 *              Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
 *              Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 *
 *              This example will show you how to use a rotary encoder with easyC and its internal counter.
 *              Upload the code to the Dasduino and open the Serial Monitor at 115200 baud rate to see what's happening.
 *              If you rotate the encoder, the counter will be increased or decreased depending on direction. When pressing 
 *              the button, the counter will reset and count from 0.
 * 
 *              NOTE: It takes some time to detect a single click because it waits to see 
 *                    if it will be pressed again so that it becomes a double click.
 * 
 * @link        solde.red/333188
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
    // NOTE: You have to restart breakout to apply the address change by unplugging and plugging
    // the easyC or USB-C from the Dasduino    
    // rotary.begin(0x31);

    // Reset the internal counter
    rotary.resetCounter();
}

void loop()
{
    // getState() function returns the current state of the rotary encoder
    // It MUST BE in the loop() and run constantly to get proper readings
    int state = rotary.getState();

    // If the state is zero or ROTARY_IDLE constant, the rotary encoder is not moving
    if (state != ROTARY_IDLE)
    {
        if (state == ROTARY_CW)
        {
            // If the state variable is equal to ROTARY_CW constant (6), the encoder is rotated clockwise
            // Print the message and internal counter variable
            Serial.print("Clockwise: ");

            // getCount function returns a counter variable. Counter add 1 if the encoder is rotated clockwise or
            // subtract 1 if the encoder is rotated counterclockwise.
            Serial.println(rotary.getCount());
        }

        if (state == ROTARY_CCW)
        {
            // If the state variable is equal to ROTARY_CCW constant (5), the encoder is rotated counterclockwise
            // Print the message and counter variable
            Serial.print("Counter clockwise: ");
            Serial.println(rotary.getCount());
        }

        if (state == BTN_CLICK)
        {
            // If the state variable is equal to BTN_CLICK constant (1), the push button on the rotary encoder is
            // pressed

            // Reset the internal counter and print a message
            rotary.resetCounter();
            Serial.println("Button press, the counter was reset");
        }
    }
}
