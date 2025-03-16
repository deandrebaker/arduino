#include "led.h"

/****************************************************
 * Led
 ****************************************************/

Led::Led(byte pin, byte amplitude) : _pin(pin), _amplitude(amplitude), _startTime(0), _state(LedState::UNINITIALIZED) {}

Led::~Led()
{
    if (getState() == LedState::UNINITIALIZED)
        return;

    analogWrite(getPin(), 0);
}

byte Led::getPin()
{
    return _pin;
}

LedState Led::getState()
{
    return _state;
}

byte Led::getAmplitude()
{
    return _amplitude;
}

unsigned long Led::getStartTime()
{
    return _startTime;
}

void Led::init()
{
    pinMode(getPin(), OUTPUT);
    analogWrite(getPin(), 0);
    _state = LedState::READY;
}

void Led::start()
{
    if (getState() == LedState::UNINITIALIZED)
        return;

    _startTime = millis();
    _state = LedState::RUNNING;
}

void Led::stop()
{
    if (getState() == LedState::UNINITIALIZED)
        return;

    _state = LedState::READY;
}

void Led::reset()
{
    stop();
    start();
}

void Led::display()
{
    unsigned long time = millis() - getStartTime();

    switch (getState())
    {
    case LedState::READY:
        analogWrite(getPin(), 0);
        break;
    case LedState::RUNNING:
        analogWrite(getPin(), getOutput(time));
        break;
    case LedState::UNINITIALIZED:
    default:
        break;
    }
}

byte Led::getOutput(unsigned long time)
{
    return 0;
}

/****************************************************
 * SolidLed
 ****************************************************/

SolidLed::SolidLed(byte pin) : Led(pin) {}

// y(t) = A
byte SolidLed::getOutput(unsigned long time)
{
    byte output = getAmplitude();
    return output;
}

/****************************************************
 * CyclicLed
 ****************************************************/

CyclicLed::CyclicLed(byte pin, unsigned long period) : Led(pin), _period(period) {}

unsigned long CyclicLed::getPeriod()
{
    return _period;
}

/****************************************************
 * PulsingLed
 ****************************************************/

PulsingLed::PulsingLed(byte pin, unsigned long period, unsigned long dutyCycle) : CyclicLed(pin, period), _dutyCycle(dutyCycle) {}

unsigned long PulsingLed::getDutyCycle()
{
    return _dutyCycle;
}

// y(t) = {A if t < D, 0 otherwise}
byte PulsingLed::getOutput(unsigned long time)
{
    byte output = time % getPeriod() < getDutyCycle() ? getAmplitude() : 0;
    return output;
}

/****************************************************
 * SinusoidalLed
 ****************************************************/

SinusoidalLed::SinusoidalLed(byte pin, unsigned long period) : CyclicLed(pin, period) {}

// y(t) = 1/2 A (sin(2 pi t / T) + 1)
byte SinusoidalLed::getOutput(unsigned long time)
{
    byte output = getAmplitude() * (sin(2 * (time % getPeriod()) * PI / getPeriod()) + 1) / 2;
    return output;
}

/****************************************************
 * TriangularLed
 ****************************************************/

TriangularLed::TriangularLed(byte pin, unsigned long period) : CyclicLed(pin, period) {}

// y(t) = A |t - 1/2 * T| / T
byte TriangularLed::getOutput(unsigned long time)
{
    byte output = getAmplitude() * abs((time % getPeriod()) - getPeriod() / 2) / getPeriod();
    return output;
}

/****************************************************
 * SawToothLed
 ****************************************************/

SawToothLed::SawToothLed(byte pin, unsigned long period) : CyclicLed(pin, period) {}

// y(t) = A t / T
byte SawToothLed::getOutput(unsigned long time)
{
    byte output = getAmplitude() * (time % getPeriod()) / getPeriod();
    return output;
}
