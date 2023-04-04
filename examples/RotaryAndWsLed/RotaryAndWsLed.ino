/**
 **************************************************
 *
 * @file        RotaryAndWsLed.ino
 * @brief       Example for the rotary encoder with easyC.
 *
 *              For this example you will need any Dasduino board, a USB-c cable, Rotary encoder with easyC, and easyC cable.
 *              Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
 *              Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 * 
 *              For this example you need to install WS2812 library:
 *              https://github.com/SolderedElectronics/Soldered-WS2812-Smart-Leds-Arduino-Library
 *
 *              This example will show you how you can use rotary encoder functionalities to control the built-in WS LED.
 *              Upload the code to the Dasduino, rotate the encoder and see what's happening :)
 *              On rotating clockwise or counter-clockwise you will change the brightness.
 *              With a single button press, you will change the colors between red, green, and blue.
 *              With a double button press, you will turn on and off the LED.
 *              On the long press button, you will change colors increasing the hue value.
 * 
 *              NOTE: If you want to use an external WS2812 LED, or if your board doesn't have a built-in WS2812 LED, 
 *                    change the LED_BUILTIN pin to the pin attached to your LED
 *
 * @link        solde.red/333188
 * 
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

// Include Soldered library for the rotary encoder with easyC
#include "Rotary-encoder-easyC-SOLDERED.h"

// Include library fot WS2812 Bulit-in LED
#include "WS2812-SOLDERED.h"

// Create an objest for the rotary encoder
Rotary rotary;

// Create object for ws2812 pixel
WS2812 pixel(1, LEDWS_BUILTIN);

int brightness = 50; // For brightness
int colorIndex;      // Index for RGB colors in the array declared below
bool wsOff;          // Flag for turning on and off LED
bool RGBColors = 1;  // Flag for using rgb colors from array or hue
uint32_t hue;        // Color hue

// Color array
uint32_t colors[3] = {
    pixel.Color(255, 0, 0), // Red
    pixel.Color(0, 255, 0), // Green
    pixel.Color(0, 0, 255)  // Blue
};

void setup()
{
    // Start I2C communication on default address (0x30)
    rotary.begin();

    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // rotary.begin(0x31);

    // Init the WS2812 pixel and set the default brightness and color
    pixel.begin();
    pixel.setPixelColor(0, colors[colorIndex]);
    pixel.setBrightness(brightness);
    pixel.show();
}

void loop()
{
    // getState() function returns the current state of the rotary encoder
    // It MUST BE in the loop() and run constantly to get proper readings
    int state = rotary.getState();

    // If the state is zero or ROTARY_IDLE constant, the rotary encoder is not moving
    if (state != ROTARY_IDLE)
    {
        // Clear the pixel
        pixel.clear();

        // Check rotary encoder state
        switch (state)
        {
        case ROTARY_CW:
            // If the rotary is rotated in the clockwise direction, increase the brightness
            brightness += 10;

            // Max brightness value is 255
            if (brightness > 255)
            {
                brightness = 255;
            }

            // Set brightness to the LED
            pixel.setBrightness(brightness);
            break;
        case ROTARY_CCW:
            // If the rotary is rotated in the counter-clockwise direction, decrease the brightness
            brightness -= 10;

            // min brightness value is 0
            if (brightness < 0)
            {
                brightness = 0;
            }

            // Set brightness to the LED
            pixel.setBrightness(brightness);
            break;
        case BTN_CLICK:
            // If the button is pressed once, change RGB color
            colorIndex++;

            // There are only 3 colors so reset the index when it reaches 2
            if (colorIndex > 2)
            {
                colorIndex = 0;
            }

            // Set the flag to show RGB color
            RGBColors = 1;
            break;
        case BTN_DOUBLE_CLICK:
            // If the button is double-pressed, turn the LED on or off
            wsOff = !wsOff;
            break;
        case BTN_LONG_PRESS:
            // If the button is long pressed, increase the color hue and show that color
            hue += 10;

            // Set the flag to show a color depending on the hue value
            RGBColors = 0;
            break;
        }

        // Now, if the RGB flag is set, show the RGB color from the colors array
        if (RGBColors)
        {
            pixel.setPixelColor(0, colors[colorIndex]);
        }
        else
        {
            // Make a color variable with custom hue
            uint32_t color = pixel.ColorHSV(hue);

            // Set the pixel color to the color passed in the function
            pixel.setPixelColor(0, color);
        }

        // If the LED must be turned off, clear the pixel
        if (wsOff)
        {
            pixel.clear();
        }

        // Show the final state of the LED
        pixel.show();
    }
}
