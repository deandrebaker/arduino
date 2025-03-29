#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define DEFAULT_PIN 11
#define DEFAULT_BRIGHTNESS 255

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

/**
 * An LED component with the ability to set its brightness using PWM (Pulse Width Modulation).
 */
class Led
{
private:
    byte _pin;
    LedState _state;
    byte _brightness;

public:
    Led(byte pin = DEFAULT_PIN, byte brightness = DEFAULT_BRIGHTNESS);
    ~Led();

    /* Getters */

    const byte getPin();
    const LedState getState();
    const byte getBrightness();

    /* Setters */

    void setState(LedState state);
    void setBrightness(byte _brightness);
    
    /* Other methods */

    void init();
    void turnOn();
    void turnOff();
    const void display();
};

#endif
