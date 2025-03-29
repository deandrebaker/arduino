#ifndef PERIODIC_LED_H
#define PERIODIC_LED_H

#include <Arduino.h>
#include "led.h"

#define DEFAULT_PERIOD 1000
#define DEFAULT_DUTY_CYCLE 750
#define DEFAULT_AMPLITUDE 255

class PeriodicLed : public Led
{
private:
    Led _led;
    const byte _amplitude;
    const unsigned long _period;
    unsigned long _startTime;

public:
    PeriodicLed(byte pin = DEFAULT_PIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD);
    const byte getAmplitude();
    const unsigned long getPeriod();
    const unsigned long getStartTime();
    virtual const byte getOutput(unsigned long time);
    const byte getPin();
    const LedState getState();
    void init();
    void turnOn();
    void turnOff();
    const void display();
};

class ConstantLed : public PeriodicLed
{
public:
    ConstantLed(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD);
    const byte getOutput(unsigned long time) override;
};

class RectangularLed : public PeriodicLed
{
private:
    unsigned long _dutyCycle;

public:
    RectangularLed(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD, unsigned long dutyCycle = DEFAULT_DUTY_CYCLE);
    const unsigned long getDutyCycle();
    const byte getOutput(unsigned long time) override;
};

class SinusoidalLed : public PeriodicLed
{
public:
    SinusoidalLed(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD);
    const byte getOutput(unsigned long time) override;
};

class TriangularLed : public PeriodicLed
{
public:
    TriangularLed(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD);
    const byte getOutput(unsigned long time) override;
};

class SawToothLed : public PeriodicLed
{
public:
    SawToothLed(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_BRIGHTNESS, unsigned long period = DEFAULT_PERIOD);
    const byte getOutput(unsigned long time) override;
};

#endif
