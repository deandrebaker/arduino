#include <Board.h>

bool pin_exists(byte pin)
{
    // Total number of digital pins defined in `pins_arduino.h`.
    return pin < NUM_DIGITAL_PINS;
}

bool pin_has_pwm(byte pin)
{
    // Pins with Pulse Width Modulation support defined in `pins_arduino.h`.
    return digitalPinHasPWM(pin);
}

bool pin_has_analog_input(byte pin)
{
    // Analog pins defined in `pins_arduino.h`.
    return (pin >= PIN_A0 && pin <= PIN_A5) || pin == PIN_A6 || pin == PIN_A7;
}

int scale_analog_write_value_to_read_value(int value)
{
    // Bound `value` to be between `0` and `MAX_ANALOG_WRITE_VALUE` inclusive.
    int bounded_value = min(max(value, 0), MAX_ANALOG_WRITE_VALUE);
    // Cast to `long` to prevent integer overflow.
    return bounded_value * (long)MAX_ANALOG_READ_VALUE / MAX_ANALOG_WRITE_VALUE;
}

// ArduinoBoard implementations

ArduinoBoard::ArduinoBoard() {}

ArduinoBoard::~ArduinoBoard() {}

void ArduinoBoard::set_pin_mode(byte pin, byte mode)
{
    pinMode(pin, mode);
}

int ArduinoBoard::digital_read(byte pin)
{
    return digitalRead(pin);
}

void ArduinoBoard::digital_write(byte pin, byte state)
{
    digitalWrite(pin, state);
}

int ArduinoBoard::analog_read(byte pin)
{
    return analogRead(pin);
}

void ArduinoBoard::analog_write(byte pin, int value)
{
    analogWrite(pin, value);
}

// InMemoryBoard implementations

InMemoryBoard::InMemoryBoard()
{
    for (int i = 0; i < NUM_DIGITAL_PINS; ++i)
    {
        pin_modes[i] = INPUT;
        pin_values[i] = LOW;
    }
}

InMemoryBoard::~InMemoryBoard() {}

byte InMemoryBoard::get_pin_mode(byte pin)
{
    if (!pin_exists(pin))
    {
        return INPUT;
    }

    return pin_modes[pin];
}

void InMemoryBoard::set_pin_mode(byte pin, byte mode)
{
    if (!pin_exists(pin))
    {
        return;
    }

    // Sets the pin values to a default state based on the pin mode.
    switch (mode)
    {
    case INPUT:
        pin_values[pin] = LOW;
        break;
    case INPUT_PULLUP:
        // Internal pullup resistor pulls up the value to HIGH by default.
        pin_values[pin] = HIGH;
        break;
    case OUTPUT:
        pin_values[pin] = LOW;
        break;
    default:
        return;
    }

    pin_modes[pin] = mode;
}

int InMemoryBoard::get_pin_value(byte pin)
{
    if (!pin_exists(pin))
    {
        return 0;
    }

    return pin_values[pin];
}

void InMemoryBoard::set_pin_value(byte pin, int value)
{
    if (!pin_exists(pin))
    {
        return;
    }

    // Bound `value` to be between `0` and `MAX_ANALOG_READ_VALUE` inclusive.
    int bounded_value = min(max(value, 0), MAX_ANALOG_READ_VALUE);
    pin_values[pin] = bounded_value;
}

int InMemoryBoard::digital_read(byte pin)
{
    if (!pin_exists(pin))
    {
        return LOW;
    }

    return pin_values[pin];
}

void InMemoryBoard::digital_write(byte pin, byte state)
{
    if (!pin_exists(pin))
    {
        return;
    }

    pin_values[pin] = min(state, HIGH);
}

int InMemoryBoard::analog_read(byte pin)
{
    if (!pin_exists(pin))
    {
        return 0;
    }

    // Analog input values are not valid if pin mode is not input.
    if (!pin_has_analog_input(pin) || pin_modes[pin] != INPUT)
    {
        return 0;
    }

    return pin_values[pin];
}

void InMemoryBoard::analog_write(byte pin, int value)
{
    if (!pin_exists(pin))
    {
        return;
    }

    if (!pin_has_pwm(pin))
    {
        return;
    }

    pin_modes[pin] = OUTPUT;
    pin_values[pin] = scale_analog_write_value_to_read_value(value);
}
