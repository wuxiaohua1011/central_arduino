// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <pin.h>
#include <SAMDUE_PWM.h>
int max_hz = 3500; // ~5v
int min_hz = 50;   // ~0v
int output_throttle_pwm = 1500;
int output_throttle_max = 2000;
int output_throttle_neu = 1500;
int output_throttle_min = 1500;
double percent_duty_cycle = 0.1;

float idle_frequency = 50.0f;
float duty_cycle = 0.0f;
SAMDUE_PWM *PWM_Instance;


void output_helper(uint32_t duration, double percent_duty_cycle, uint32_t pinout)
{
  uint32_t time_high = uint32_t(duration * percent_duty_cycle);
  uint32_t time_low = duration - time_high;
  digitalWrite(pinout, HIGH);
  delayMicroseconds(time_high); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(pinout, LOW);
  delayMicroseconds(time_low);
}

void actuateFromArduinoPWM(float throttle)
{
  throttle = constrain(throttle, 0, 1);
  float frequency = map(throttle, 0, 1, min_hz, max_hz);
  PWM_Instance->setPWM(THROTTLE_OUTPUT_PIN, frequency, duty_cycle);
}

/**
 * @brief  setup PWM to voltage converter
 * @note
 * @retval None
 */
void setupPwmVoltageConverter()
{
  // pinMode(THROTTLE_OUTPUT_PIN, OUTPUT);
  PWM_Instance = new SAMDUE_PWM(THROTTLE_OUTPUT_PIN, idle_frequency, 20.0f);
}

/**
 * @brief  write to throttle
 * @note
 * @retval None
 */
void writeToThrottle(float throttle)
{
  actuateFromArduinoPWM(throttle);
}