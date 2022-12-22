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

class Rotary : public EasyC
{
  public:
    Rotary();
    long getCount();
    byte getState();


  protected:
    void initializeNative();

  private:
    void getData();
    long rotaryCounter;
    byte rotaryState;
};

#endif
