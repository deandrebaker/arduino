#include <Arduino.h>
#include "led.h"

#define SIMULATION_TIME 4000 // 4 seconds

Led brightLed = Led();
Led dimLed = Led(10, 20);

void setup()
{
  brightLed.init();
  dimLed.init();
}

void loop()
{
  const unsigned long elapsedTime = millis();

  // Turns on the bright LED and turns off the dim LED after 2 seconds.
  if ((elapsedTime % SIMULATION_TIME) < SIMULATION_TIME / 2 && brightLed.getState() == LedState::READY)
  {
    brightLed.turnOn();
    dimLed.turnOff();
  }
  // Turns off the bright LED and turns on the dim LED after 4 seconds and restarts the cycle.
  else if ((elapsedTime % SIMULATION_TIME) > SIMULATION_TIME / 2 && dimLed.getState() == LedState::READY)
  {
    brightLed.turnOff();
    dimLed.turnOn();
  }

  brightLed.display();
  dimLed.display();
}
