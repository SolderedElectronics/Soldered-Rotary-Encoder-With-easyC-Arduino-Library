/**
 **************************************************
 *
 * @file        Rotary-encoder-easyC-SOLDERED.h
 * @brief       Header file for the rotary encoder with easyC.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __ROTARY__
#define __ROTARY__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

// Define states of the rotary encoder and button
#define ROTARY_IDLE      0
#define BTN_CLICK        1
#define BTN_DOUBLE_CLICK 2
#define BTN_LONG_PRESS   3
#define BTN_LONG_RELEASE 4
#define ROTARY_CCW       5
#define ROTARY_CW        6

class Rotary : public EasyC
{
  public:
    Rotary();
    long getCount();
    byte getState();
    void resetCounter();


  protected:
    void initializeNative();

  private:
    void getData();
    long rotaryCounter;
    byte rotaryState;
};

#endif
