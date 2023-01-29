// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <pin.h>
#include <SAMDUE_PWM.h>
const int MAX_HZ = 3500; // ~5v
const int MIN_HZ = 50;    // ~0v
const int OUTPUT_THROTTLE_MAX = 2000;
const int OUTPUT_THROTTLE_NEU = 1500;
const int OUTPUT_THROTTLE_MIN = 1500;
const float IDLE_FREQUENCY = 50.0f;
const float DUTY_CYCLE = 50.0f;

void actuateFromArduinoPWM(float throttle);

/**
 * @brief  setup PWM to voltage converter
 * @note
 * @retval None
 */
void setupPwmVoltageConverter();

/**
 * @brief  write to throttle
 * @note
 * @retval None
 */
void writeToThrottle(float throttle);

float arduinoToROARConvert(int pulse_time);