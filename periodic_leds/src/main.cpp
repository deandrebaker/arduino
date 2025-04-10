#include <periodic_led.h>
#include <Pin/Pin.h>

#define LED_COUNT 5
#define ON_TIME 9000
#define TOTAL_TIME 10000

ArduinoBoard board = ArduinoBoard();
boolean started = false;
PeriodicLed *periodicLeds[LED_COUNT];
AnalogOutputPin pin_11 = AnalogOutputPin(&board, 11);
AnalogOutputPin pin_10 = AnalogOutputPin(&board, 10);
AnalogOutputPin pin_9 = AnalogOutputPin(&board, 9);
AnalogOutputPin pin_6 = AnalogOutputPin(&board, 6);
AnalogOutputPin pin_5 = AnalogOutputPin(&board, 5);
ConstantLed constantLed = ConstantLed(&pin_11);
RectangularLed pulsingLed = RectangularLed(&pin_10);
SinusoidalLed sinusoidalLed = SinusoidalLed(&pin_9);
TriangularLed triangularLed = TriangularLed(&pin_6);
SawToothLed sawToothLed = SawToothLed(&pin_5);

void init_leds();
void turn_on_leds();
void turn_off_leds();
void display_leds();

void setup()
{
  periodicLeds[0] = &constantLed;
  periodicLeds[1] = &pulsingLed;
  periodicLeds[2] = &sinusoidalLed;
  periodicLeds[3] = &triangularLed;
  periodicLeds[4] = &sawToothLed;

  init_leds();
}

void loop()
{
  unsigned long time = millis();

  if (time % TOTAL_TIME < ON_TIME && !started)
  {
    turn_on_leds();
    started = true;
  }
  else if (time % TOTAL_TIME >= ON_TIME && started)
  {
    turn_off_leds();
    started = false;
  }

  display_leds();
}

void init_leds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->init();
  }
}

void turn_on_leds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->turn_on();
  }
}

void turn_off_leds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->turn_off();
  }
}

void display_leds()
{
  for (byte i = 0; i < LED_COUNT; i++)
  {
    periodicLeds[i]->display();
  }
}
