#include "button.h"

Button::Button(byte pin) : _pin(pin), _initialized(false) {}

byte Button::getPin()
{
    return _pin;
}

boolean Button::isInitialized()
{
    return _initialized;
}

void Button::init()
{
    pinMode(getPin(), INPUT_PULLUP);
    _initialized = true;
}

boolean Button::isPressed()
{
    if (!isInitialized())
        return false;

    return !digitalRead(getPin());
}