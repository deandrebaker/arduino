#include <Arduino.h>
#include "periodic_led.h"

#define LED_COUNT 5
#define ON_TIME 9000
#define TOTAL_TIME 10000

boolean started = false;
PeriodicLed *periodicLeds[LED_COUNT];
ConstantLed constantLed = ConstantLed(11);
RectangularLed pulsingLed = RectangularLed(10);
SinusoidalLed sinusoidalLed = SinusoidalLed(9);
TriangularLed triangularLed = TriangularLed(6);
SawToothLed sawToothLed = SawToothLed(5);

void initLeds();
void turnOnLeds();
void turnOffLeds();
void displayLeds();

void setup()
{
  periodicLeds[0] = &constantLed;
  periodicLeds[1] = &pulsingLed;
  periodicLeds[2] = &sinusoidalLed;
  periodicLeds[3] = &triangularLed;
  periodicLeds[4] = &sawToothLed;

  initLeds();
}

void loop()
{
  unsigned long time = millis();

  if (time % TOTAL_TIME < ON_TIME && !started)
  {
    turnOnLeds();
    started = true;
  }
  else if (time % TOTAL_TIME >= ON_TIME && started)
  {
    turnOffLeds();
    started = false;
  }

  displayLeds();
}

void initLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->init();
  }
}

void turnOnLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->turnOn();
  }
}

void turnOffLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->turnOff();
  }
}

void displayLeds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->display();
  }
}
