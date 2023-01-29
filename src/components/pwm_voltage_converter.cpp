// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <SAMDUE_PWM.h>

#include "pin.h"
#include "pwm_voltage_converter.h"
SAMDUE_PWM *PWM_Instance;


void actuateFromArduinoPWM(float throttle)
{
    throttle = constrain(throttle, 0, 1);
    float frequency = (throttle - 0) / (1 - 0) * (MAX_HZ - MIN_HZ) + MIN_HZ;
    PWM_Instance->setPWM(THROTTLE_OUTPUT_PIN, frequency, DUTY_CYCLE);
}

/**
 * @brief  setup PWM to voltage converter
 * @note
 * @retval None
 */
void setupPwmVoltageConverter()
{
    // pinMode(THROTTLE_OUTPUT_PIN, OUTPUT);
    PWM_Instance = new SAMDUE_PWM(THROTTLE_OUTPUT_PIN, IDLE_FREQUENCY, 20.0f);
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

float arduinoToROARConvert(int pulse_time)
{
    return (pulse_time - 1000.0) / (2000.0 - 1000) * (1 - -1) + -1;
}