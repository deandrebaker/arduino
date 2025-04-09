#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <Component.h>

// An interface for a single digital input.
class DigitalInput : public Component
{
public:
    virtual ~DigitalInput() = default;
    // Returns true if the voltage is HIGH, false if the voltage is LOW.
    virtual const bool get_value() = 0;
};

// An interface for a single digital output.
class DigitalOutput : public Component
{
public:
    virtual ~DigitalOutput() = default;
    // Sets the voltage to HIGH if `value` is true, LOW if `value` is false.
    virtual void set_value(const bool value) = 0;
};

// An interface for a single analog input.
class AnalogInput : public Component
{
public:
    virtual ~AnalogInput() = default;
    // Returns the ratio of the voltage to 5V.
    virtual const float get_value() = 0;
};

// An interface for a single analog output.
class AnalogOutput : public Component
{
public:
    virtual ~AnalogOutput() = default;
    // Sets the voltage to `value` * 5V.
    virtual void set_value(const float value) = 0;
};

#endif // INPUT_OUTPUT_H
