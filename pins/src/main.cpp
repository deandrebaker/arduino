#include <Arduino.h>

#include <Pin.h>

ArduinoBoard board = ArduinoBoard();
DigitalOutputPin bright_led = DigitalOutputPin(&board, 13);
DigitalInputPin button = DigitalInputPin(&board, 12, true);
AnalogOutputPin dim_led = AnalogOutputPin(&board, 11);
AnalogInputPin potentiometer = AnalogInputPin(&board, A5);

void setup()
{
  bright_led.initialize();
  button.initialize();
  dim_led.initialize();
  potentiometer.initialize();
}

void loop()
{
  const bool is_pressed = !button.get_value();
  const float volts = potentiometer.get_value() * 5;
  bright_led.set_value(is_pressed);
  dim_led.set_value(volts / 5.0);
  delay(1);
}
