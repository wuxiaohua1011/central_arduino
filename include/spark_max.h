// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Servo.h>
#include <pin.h>
#include <Arduino.h>
Servo servoSteering;
const int NEUTRAL_STEERING_PWM = 1500;
int output_steering_pwm = 1500;
int output_brake_pwm = 1500;
int output_steering_max = 1700;
int output_steering_min = 1300;

void checkServoAttachments()
{
  if (servoSteering.attached() == false)
  {
    Serial.println("Reattaching steering pin");
    servoSteering.attach(STEERING_OUTPUT_PIN);
  }
}

void writeToSteering(float steering)
{
  // convert [-1, 1] to [1000, 2000]
  int steering_pwm = map(steering, -1, 1, output_steering_min, output_steering_max);
  servoSteering.writeMicroseconds(constrain(steering_pwm, output_steering_min, output_steering_max));
}

void changeSteeringToNeutral()
{
  output_steering_pwm = 1500;
}

void changeBrakeToNeutral()
{
  output_brake_pwm = 1000;
}

void setupSparkMax()
{
  servoSteering.attach(STEERING_OUTPUT_PIN);
}
