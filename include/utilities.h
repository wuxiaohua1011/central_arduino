#include <Arduino.h>
#include <Servo.h>
#include "radiolink.h"
#include "pin.h"
#include <spark_max.h>
#include <led.h>

void printRawStatus()
{
  Serial.print("RAW --> THROTTLE: ");
  Serial.print(throttle_pulse_time);

  Serial.print(" | STEERING: ");
  Serial.print(steering_pulse_time);

  Serial.print(" | BRAKE: ");
  Serial.print(brake_pulse_time);

  Serial.print(" | BUTTON: ");
  Serial.println(button_pulse_time);
}

void printOuputValues()
{
  Serial.print("OUTPUT --> THROTTLE: ");
  Serial.print(output_throttle_pwm);

  Serial.print(" | STEERING: ");
  Serial.print(output_steering_pwm);

  Serial.print(" | BRAKE: ");
  Serial.println(output_brake_pwm);
}