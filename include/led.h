#include <Arduino.h>

bool led_builtin_was_on = false;

void blink_builtin_led()
{
  if (led_builtin_was_on == true)
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    led_builtin_was_on = false;
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    led_builtin_was_on = true;
  }
}

void setupLED() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loopLED() {
    // placeholder for code consistency
}