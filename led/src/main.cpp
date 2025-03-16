#include <Arduino.h>
#include "led.h"

#define LED_COUNT 5
#define ON_TIME 9000
#define TOTAL_TIME 10000

boolean started = false;
Led *leds[LED_COUNT];
SolidLed solidLed = SolidLed(11);
PulsingLed pulsingLed = PulsingLed(10, 1000, 500);
SinusoidalLed sinusoidalLed = SinusoidalLed(9);
TriangularLed triangularLed = TriangularLed(6);
SawToothLed sawToothLed = SawToothLed(5);

void initLeds();
void startLeds();
void stopLeds();
void displayLeds();

void setup()
{
  leds[0] = &solidLed;
  leds[1] = &pulsingLed;
  leds[2] = &sinusoidalLed;
  leds[3] = &triangularLed;
  leds[4] = &sawToothLed;

  initLeds();
}

void loop()
{
  unsigned long time = millis();

  if (time % TOTAL_TIME < ON_TIME && !started)
  {
    startLeds();
    started = true;
  }
  else if (time % TOTAL_TIME >= ON_TIME && started)
  {
    stopLeds();
    started = false;
  }

  displayLeds();
}

void initLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    leds[i]->init();
  }
}

void startLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    leds[i]->start();
  }
}

void stopLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    leds[i]->stop();
  }
}

void displayLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    leds[i]->display();
  }
}