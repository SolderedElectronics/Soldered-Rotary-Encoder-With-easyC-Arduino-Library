/**
 **************************************************
 *
 * @file        BasicRotaryReading.ino
 * @brief       Example for the rotary encoder with easyC.
 *
 *              For this example, you need to connect the rotary encoder with easyC to Dasduino and upload this code.
 *              On the serial monitor, you will see the information on rotation.
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "Rotary-encoder-easyC-SOLDERED.h"

Rotary rotary;

int counter;

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize rotary encoder
    rotary.begin();
}

void loop()
{
    // getState function returns the current state of the rotary encoder
    int state = rotary.getState();
    if(state == 5)
    {
      counter++;
    }

    if(counter > 10)
    {
      rotary.resetCounter();
    }
    

    // If the state is zero, the rotary encoder is not moving
    if (state != 0)
    {
        /*// getCount function returns a counter variable. Counter add 1 if the encoder is rotated clockwise or subtract 1
        // if the encoder is rotated counterclockwise.
        int counter = rotary.getCount();
        if (state == 1)
        {
            // If the state variable is equal to 1, the encoder is rotated clockwise
            // Print the message and counter variable
            Serial.print("Clockwise: ");
            Serial.println(counter);
        }

        if (state == 2)
        {
            // If the state variable is equal to 2, the encoder is rotated counterclockwise
            // Print the message and counter variable
            Serial.print("Counter clockwise: ");
            Serial.println(counter);
        }

        if (state == 3)
        {
            // If the state variable is equal to 3, the push button on the rotary encoder is pressed
            Serial.println("Button press");
        }*/
        Serial.println(state);
    }
    if (state > 10)
    {
      rotary.res
    }
}
