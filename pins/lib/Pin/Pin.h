#ifndef PIN_H
#define PIN_H

#include <InputOutput.h>
#include <Board.h>

class DigitalInputPin : public DigitalInput
{
private:
    Board *board;
    byte pin;
    bool initialized;
    bool _pullup;

public:
    DigitalInputPin(Board *board, const byte pin, const bool pullup);
    ~DigitalInputPin() override;
    const byte get_pin();
    const bool get_is_initialized() override;
    bool initialize() override;
    const bool get_value() override;
};

class DigitalOutputPin : public DigitalOutput
{
private:
    Board *board;
    byte pin;
    bool initialized;

public:
    DigitalOutputPin(Board *board, const byte pin);
    ~DigitalOutputPin() override;
    const byte get_pin();
    const bool get_is_initialized() override;
    bool initialize() override;
    void set_value(const bool value) override;
};

class AnalogInputPin : public AnalogInput
{
private:
    Board *board;
    byte pin;
    bool initialized;

public:
    AnalogInputPin(Board *board, const byte pin);
    ~AnalogInputPin() override;
    const byte get_pin();
    const bool get_is_initialized() override;
    bool initialize() override;
    const float get_value() override;
};

class AnalogOutputPin : public AnalogOutput
{
private:
    Board *board;
    byte pin;
    bool initialized;

public:
    AnalogOutputPin(Board *board, const byte pin);
    ~AnalogOutputPin() override;
    const byte get_pin();
    const bool get_is_initialized() override;
    bool initialize() override;
    void set_value(const float value) override;
};

#endif // PIN_H
