#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
private:
    byte _pin;
    boolean _initialized;

public:
    Button(byte pin = 12);
    byte getPin();
    boolean isInitialized();
    void init();
    boolean isPressed();
};

#endif