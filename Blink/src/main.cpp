#include <Arduino.h>

/**
 * Blink
 *
 * This program blinks an LED connected to pin `LED_PIN` with a period of `PERIOD_MS` in ms.
 */

/*
Calculate resistor's resistance
v_supply = 5V
v_led = 2V
i_led = 18mA
      = 0.0018A
v_res = v_supply - v_led
      = 5V - 2V
      = 3V
i_res = i_led
      = 0.0018A
r_res = v_res / i_res
      = 3V * 0.018A
      = 166.67 Ohm
*/

const byte LED_PIN = 12;
const int PERIOD_MS = 1000;

void setup()
{
  pinMode(LED_PIN, HIGH);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD_MS / 2);
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD_MS / 2);
}