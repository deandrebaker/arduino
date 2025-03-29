#include "periodic_led.h"

/****************************************************
 * PeriodicLed
 ****************************************************/

PeriodicLed::PeriodicLed(byte pin, byte amplitude, unsigned long period)
    : _led(Led(pin, 0)),
      _amplitude(amplitude),
      _period(period),
      _startTime(millis()) {}

const byte PeriodicLed::getAmplitude()
{
    return _amplitude;
}

const unsigned long PeriodicLed::getPeriod()
{
    return _period;
}

const unsigned long PeriodicLed::getStartTime()
{
    return _startTime;
}

const byte PeriodicLed::getOutput(unsigned long time)
{
    return 0;
}

const byte PeriodicLed::getPin()
{
    return _led.getPin();
}

const LedState PeriodicLed::getState()
{
    return _led.getState();
}

void PeriodicLed::init()
{
    _led.init();
}

void PeriodicLed::turnOn()
{
    _led.turnOn();

    if (getState() == LedState::RUNNING)
    {
        _startTime = millis();
    }
}

void PeriodicLed::turnOff()
{
    _led.turnOff();
}

const void PeriodicLed::display()
{
    unsigned long elapsedTime = millis() - getStartTime();
    unsigned long periodTime = elapsedTime % getPeriod();
    _led.setBrightness(getOutput(periodTime));
    _led.display();
}

/****************************************************
 * ConstantLed
 ****************************************************/

ConstantLed::ConstantLed(byte pin, byte amplitude, unsigned long period) : PeriodicLed(pin, amplitude, period) {}

// y(t) = A
const byte ConstantLed::getOutput(unsigned long time)
{
    return getAmplitude();
}

/****************************************************
 * RectangularLed
 ****************************************************/

RectangularLed::RectangularLed(byte pin, byte amplitude, unsigned long period, unsigned long dutyCycle)
    : PeriodicLed(pin, amplitude, period),
      _dutyCycle(dutyCycle) {}

const unsigned long RectangularLed::getDutyCycle()
{
    return _dutyCycle;
}

// y(t) = {A if t < D, 0 otherwise}
const byte RectangularLed::getOutput(unsigned long time)
{
    byte output = time < getDutyCycle() ? getAmplitude() : 0;
    return output;
}

/****************************************************
 * SinusoidalLed
 ****************************************************/

SinusoidalLed::SinusoidalLed(byte pin, byte amplitude, unsigned long period) : PeriodicLed(pin, amplitude, period) {}

// y(t) = 1/2 A (sin(2 pi t / T) + 1)
const byte SinusoidalLed::getOutput(unsigned long time)
{
    byte output = getAmplitude() * (sin(2 * time * PI / getPeriod()) + 1) / 2;
    return output;
}

/****************************************************
 * TriangularLed
 ****************************************************/

TriangularLed::TriangularLed(byte pin, byte amplitude, unsigned long period) : PeriodicLed(pin, amplitude, period) {}

// y(t) = A |t - 1/2 * T| / T
const byte TriangularLed::getOutput(unsigned long time)
{
    return getAmplitude() * abs(time - getPeriod() / 2.0) / getPeriod();
}

/****************************************************
 * SawToothLed
 ****************************************************/

SawToothLed::SawToothLed(byte pin, byte amplitude, unsigned long period) : PeriodicLed(pin, amplitude, period) {}

// y(t) = A t / T
const byte SawToothLed::getOutput(unsigned long time)
{
    byte output = getAmplitude() * time / getPeriod();
    return output;
}
