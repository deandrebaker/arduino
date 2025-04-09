#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>

#define MAX_ANALOG_READ_VALUE 1023
#define MAX_ANALOG_WRITE_VALUE 255

bool pin_exists(byte pin);
bool pin_has_pwm(byte pin);
bool pin_has_analog_input(byte pin);

// An interface for connecting to an Arduino board.
class Board
{
public:
    virtual ~Board() = default;
    // Sets the pin mode for the specified pin.
    virtual void set_pin_mode(byte pin, byte mode) = 0;
    // Reads the digital value from the specified pin.
    // Value will be either HIGH or LOW.
    virtual int digital_read(byte pin) = 0;
    // Writes the digital value to the specified pin.
    // `state` can be either HIGH or LOW.
    virtual void digital_write(byte pin, byte state) = 0;
    // Reads the analog value from the specified pin.
    // Value will be between 0 and 1023 inclusive.
    virtual int analog_read(byte pin) = 0;
    // Writes the analog value to the specified pin.
    // `value` can be between 0 and 255 inclusive.
    virtual void analog_write(byte pin, int value) = 0;
};

class ArduinoBoard : public Board
{
public:
    ArduinoBoard();
    ~ArduinoBoard() override;
    void set_pin_mode(byte pin, byte mode) override;
    int digital_read(byte pin) override;
    void digital_write(byte pin, byte state) override;
    int analog_read(byte pin) override;
    void analog_write(byte pin, int value) override;
};

class InMemoryBoard : public Board
{
private:
    byte pin_modes[NUM_DIGITAL_PINS];
    int pin_values[NUM_DIGITAL_PINS];

public:
    InMemoryBoard();
    ~InMemoryBoard() override;
    byte get_pin_mode(byte pin);
    void set_pin_mode(byte pin, byte mode) override;
    int get_pin_value(byte pin);
    void set_pin_value(byte pin, int value);
    int digital_read(byte pin) override;
    void digital_write(byte pin, byte state) override;
    int analog_read(byte pin) override;
    void analog_write(byte pin, int value) override;
};

#endif // BOARD_H
