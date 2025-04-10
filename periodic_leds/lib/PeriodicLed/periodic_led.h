#ifndef PERIODIC_LED_H
#define PERIODIC_LED_H

#include <InputOutput/InputOutput.h>

#define DEFAULT_PERIOD 1000
#define DEFAULT_DUTY_CYCLE 750
#define DEFAULT_AMPLITUDE 1

/**
 * The operational state of an LED. All LEDs start UNINITIALIZED.
 * From UNINITIALIZED, it can transition to READY.
 * From READY, it can transition RUNNING.
 * From RUNNING, it can transition to READY.
 */
enum class LedState
{
    UNINITIALIZED,
    READY,
    RUNNING
};

class PeriodicLed
{
private:
    AnalogOutput *output;
    LedState state;
    const float amplitude;
    const unsigned long period;
    unsigned long start_time;

public:
    PeriodicLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD);
    const float get_amplitude();
    const unsigned long get_period();
    const unsigned long get_start_time();
    virtual const float get_output(unsigned long time);
    const LedState get_state();
    void init();
    void turn_on();
    void turn_off();
    const void display();
};

class ConstantLed : public PeriodicLed
{
public:
    ConstantLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD);
    const float get_output(unsigned long time) override;
};

class RectangularLed : public PeriodicLed
{
private:
    unsigned long _dutyCycle;

public:
    RectangularLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD, unsigned long dutyCycle = DEFAULT_DUTY_CYCLE);
    const unsigned long getDutyCycle();
    const float get_output(unsigned long time) override;
};

class SinusoidalLed : public PeriodicLed
{
public:
    SinusoidalLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD);
    const float get_output(unsigned long time) override;
};

class TriangularLed : public PeriodicLed
{
public:
    TriangularLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD);
    const float get_output(unsigned long time) override;
};

class SawToothLed : public PeriodicLed
{
public:
    SawToothLed(AnalogOutput *output, float amplitude = DEFAULT_AMPLITUDE, unsigned long period = DEFAULT_PERIOD);
    const float get_output(unsigned long time) override;
};

#endif
