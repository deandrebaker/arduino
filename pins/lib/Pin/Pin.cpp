#include <Pin.h>

// DigitalOutputPin Implementation

DigitalInputPin::DigitalInputPin(Board *board, const byte pin, const bool pullup)
    : board(board), pin(pin), initialized(false), _pullup(pullup) {}

DigitalInputPin::~DigitalInputPin() {}

const byte DigitalInputPin::get_pin()
{
    return pin;
}

const bool DigitalInputPin::get_is_initialized()
{
    return initialized;
}

bool DigitalInputPin::initialize()
{
    if (!pin_exists(pin))
    {
        return false;
    }

    // The built-in LED pin cannot be set to INPUT_PULLUP.
    if (pin == LED_BUILTIN && _pullup)
    {
        return false;
    }

    board->set_pin_mode(pin, _pullup ? INPUT_PULLUP : INPUT);
    initialized = true;
    return initialized;
}

const bool DigitalInputPin::get_value()
{
    if (!initialized)
    {
        return false;
    }

    return board->digital_read(pin);
}

// DigitalOutputPin Implementation

DigitalOutputPin::DigitalOutputPin(Board *board, const byte pin) : board(board), pin(pin), initialized(false) {}

DigitalOutputPin::~DigitalOutputPin()
{
    if (!initialized)
    {
        return;
    }

    board->digital_write(pin, LOW);
}

const byte DigitalOutputPin::get_pin()
{
    return pin;
}

const bool DigitalOutputPin::get_is_initialized()
{
    return initialized;
}

bool DigitalOutputPin::initialize()
{
    if (!pin_exists(pin))
    {
        return false;
    }

    board->set_pin_mode(pin, OUTPUT);
    initialized = true;
    return initialized;
}

void DigitalOutputPin::set_value(const bool value)
{
    if (!initialized)
    {
        return;
    }

    board->digital_write(pin, value ? HIGH : LOW);
}

// AnalogInputPin Implementation

AnalogInputPin::AnalogInputPin(Board *board, const byte pin) : board(board), pin(pin), initialized(false) {}

AnalogInputPin::~AnalogInputPin() {}

const byte AnalogInputPin::get_pin()
{
    return pin;
}

const bool AnalogInputPin::get_is_initialized()
{
    return initialized;
}

bool AnalogInputPin::initialize()
{
    if (!pin_exists(pin))
    {
        return false;
    }

    if (!pin_has_analog_input(pin))
    {
        return false;
    }

    board->set_pin_mode(pin, INPUT);
    initialized = true;
    return initialized;
}

const float AnalogInputPin::get_value()
{
    if (!initialized)
    {
        return 0;
    }

    float scaled_value = board->analog_read(pin) / (float)MAX_ANALOG_READ_VALUE;
    return scaled_value;
}

// AnalogOutputPin Implementation

AnalogOutputPin::AnalogOutputPin(Board *board, const byte pin) : board(board), pin(pin), initialized(false) {}

AnalogOutputPin::~AnalogOutputPin() {}

const byte AnalogOutputPin::get_pin()
{
    return pin;
}

const bool AnalogOutputPin::get_is_initialized()
{
    return initialized;
}

bool AnalogOutputPin::initialize()
{
    if (!pin_exists(pin))
    {
        return false;
    }

    if (!pin_has_pwm(pin))
    {
        return false;
    }

    board->set_pin_mode(pin, OUTPUT);
    initialized = true;
    return initialized;
}

void AnalogOutputPin::set_value(const float value)
{
    if (!initialized)
    {
        return;
    }

    float bounded_value = min(max(value, 0), 1);
    float scaled_value = bounded_value * MAX_ANALOG_WRITE_VALUE;
    board->analog_write(pin, scaled_value);
}
