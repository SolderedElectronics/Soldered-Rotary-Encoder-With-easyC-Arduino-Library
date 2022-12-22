/**
 **************************************************
 *
 * @file        attiny_firmware.ino
 * @brief       Firmware for the attiny on the breakout.
 *
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS;

volatile long counter = 0;
volatile byte state = 0;
int currentStateClock;
int lastStateClock;
unsigned long lastButtonPress = 0;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    attachInterrupt(PA2, isr, RISING);
    pinMode(PA3, INPUT_PULLUP); // Data pin connected to PA3
    pinMode(PA6, INPUT_PULLUP); // Push button pin connected to PA6
}

void loop()
{
    // Read the button state
    int btnState = digitalRead(PA6);

    // If we detect LOW signal, button is pressed
    if (btnState == LOW)
    {
        // if 50ms have passed since last LOW pulse, it means that the
        // button has been pressed, released and pressed again
        if (millis() - lastButtonPress > 50)
        {
            state = 3;
        }

        // Remember last button press event
        lastButtonPress = millis();
    }

    // Put in a slight delay to help debounce the reading
    delay(1);
}

void isr ()
{
  if (digitalRead(PA3)) {
      counter ++;
      state = 1;
    } else {
      counter --;
      state = 2;
    }
}

void receiveEvent(int howMany)
{

}

void requestEvent() 
{   
    uint8_t *counterToSend = (uint8_t*)&counter;
    Wire.write(counterToSend, 4);
    
    Wire.write(state);
    state = 0;
}
