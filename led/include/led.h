#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define DEFAULT_PERIOD 1000
#define DEFAULT_DUTY_CYCLE 750
#define DEFAULT_AMPLITUDE 255

enum class LedState
{
    UNINITIALIZED,
    READY,
    RUNNING
};

class Led
{
private:
    byte _pin;
    byte _amplitude;
    unsigned long _startTime;
    LedState _state;

public:
    Led(byte pin = LED_BUILTIN, byte amplitude = DEFAULT_AMPLITUDE);
    ~Led();
    byte getPin();
    LedState getState();
    byte getAmplitude();
    unsigned long getStartTime();
    void init();
    void start();
    void stop();
    void reset();
    void display();
    virtual byte getOutput(unsigned long time);
};

class SolidLed : public Led
{
public:
    SolidLed(byte pin = LED_BUILTIN);
    byte getOutput(unsigned long time) override;
};

class CyclicLed : public Led
{
private:
    unsigned long _period;

public:
    CyclicLed(byte pin = LED_BUILTIN, unsigned long period = DEFAULT_PERIOD);
    unsigned long getPeriod();
};

class PulsingLed : public CyclicLed
{
private:
    unsigned long _dutyCycle;

public:
    PulsingLed(byte pin = LED_BUILTIN, unsigned long period = DEFAULT_PERIOD, unsigned long dutyCycle = DEFAULT_DUTY_CYCLE);
    unsigned long getDutyCycle();
    byte getOutput(unsigned long time) override;
};

class SinusoidalLed : public CyclicLed
{
public:
    SinusoidalLed(byte pin = LED_BUILTIN, unsigned long period = DEFAULT_PERIOD);
    byte getOutput(unsigned long time) override;
};

class TriangularLed : public CyclicLed
{
public:
    TriangularLed(byte pin = LED_BUILTIN, unsigned long period = DEFAULT_PERIOD);
    byte getOutput(unsigned long time) override;
};

class SawToothLed : public CyclicLed
{
public:
    SawToothLed(byte pin = LED_BUILTIN, unsigned long period = DEFAULT_PERIOD);
    byte getOutput(unsigned long time) override;
};

#endif