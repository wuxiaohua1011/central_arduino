// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Servo.h>
#include <pin.h>
#include <Arduino.h>
const int NEUTRAL_STEERING_PWM = 1500;
const int OUTPUT_STEERING_MAX = 2000;
const int OUTPUT_STEERING_MIN = 1000;

extern int output_steering_pwm;

void checkServoAttachments();

void writeToSteering(float steering);

void setupSparkMax();