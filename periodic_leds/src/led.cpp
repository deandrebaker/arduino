#include "led.h"

Led::Led(byte pin, byte brightness)
    : _pin(pin),
      _state(LedState::UNINITIALIZED),
      _brightness(brightness) {}

Led::~Led()
{
    const LedState state = getState();
    const byte pin = getPin();

    if (state == LedState::UNINITIALIZED)
        return;

    // Sets the LED output to 0.
    analogWrite(pin, 0);
}

const byte Led::getPin()
{
    return _pin;
}

const LedState Led::getState()
{
    return _state;
}

const byte Led::getBrightness()
{
    return _brightness;
}

void Led::setState(LedState state)
{
    _state = state;
}

void Led::setBrightness(byte brightness)
{
    _brightness = brightness;
}

void Led::init()
{
    const byte pin = getPin();

    // Configures the pin to use PWM and set the LED output to 0.
    pinMode(pin, OUTPUT);
    analogWrite(pin, 0);

    setState(LedState::READY);
}

void Led::turnOn()
{
    const LedState state = getState();

    if (state == LedState::UNINITIALIZED)
        return;

    setState(LedState::RUNNING);
}

void Led::turnOff()
{
    const LedState state = getState();

    if (state == LedState::UNINITIALIZED)
        return;

    setState(LedState::READY);
}

const void Led::display()
{
    const LedState state = getState();
    const byte pin = getPin();
    const byte brightness = getBrightness();

    // Sets the LED output to `brightness` if RUNNING, or to 0 if READY. No-ops otherwise.
    switch (state)
    {
    case LedState::READY:
        analogWrite(pin, 0);
        break;
    case LedState::RUNNING:
        analogWrite(pin, brightness);
        break;
    case LedState::UNINITIALIZED:
    default:
        break;
    }
}
