/**
 **************************************************
 *
 * @file        Template.ino
 * @brief       Example template for easyC sensors
 *
 *
 *
 * @authors     @ soldered.com
 ***************************************************/

#include "Rotary-encoder-easyC-SOLDERED.h"

Rotary rotary;

void setup()
{
    Serial.begin(115200);
    rotary.begin();
}

void loop()
{
    int state = rotary.getState();

    if (state != 0)
    {
        int counter = rotary.getCount();
        if (state == 1)
        {
            Serial.print("Clockwise: ");
            Serial.println(counter);
        }
        
        if(state == 2)
        {
            Serial.print("Counter clockwise: ");
            Serial.println(counter);
        }
        
        if(state == 3)
        {
            Serial.println("Button press");
        }
    }
}