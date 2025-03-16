#include <Arduino.h>
#include "button.h"
#include "led.h"

boolean started = false;
Button button = Button(12);
PulsingLed led = PulsingLed(11);

void setup()
{
  button.init();
  led.init();
}

void loop()
{
  if (button.isPressed() && !started)
  {
    led.start();
    started = true;
  }
  else if (!button.isPressed() && started)
  {
    led.stop();
    started = false;
  }

  led.display();
}
