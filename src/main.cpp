// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/**
 * By Michael Wu on July 9, 2022.
 * reference from https://www.camelsoftware.com/2015/12/25/reading-pwm-signals-from-an-rc-receiver-with-arduino/
 *
 * Please wire up your PWM Inputs on Digital Pins and revise the *_SOURCE fields to the corresponding pin numbers.
 * only arduino ble nano 33 and arduino due are tested
 *
 **/
#include <main.h>

void setup()
{
  Serial.begin(115200);
  setupPwmVoltageConverter();
  setupLED();
  setupSparkMax();
  setupRadioLink();
  setupSteeringLimiters();
  // setupBrake(); // this is a blocking call
}

void loop()
{
  // update state
  loopSpeedEstimation();
  vehicleState->speed = getSpeed();
  vehicleState->is_auto = determine_auto();
  vehicleState->angle = measureAngle();
  updateLimiterStates(vehicleState);

  // Serial.println(vehicleState->speed);
  // actuation
  // if (vehicleState->is_auto)
  // {
  // onAutoDrive();
  // }
  // else
  // {
  onManualDrive();
  // }
  // onManualDrive();
  applyVehicleSafetyPolicy(vehicleState);
  actuate(vehicleState->act);
}

void onAutoDrive()
{
  digitalWrite(LED_BUILTIN, HIGH);
  // processSerialCommunication(vehicleState, true);
  vehicleState->act->throttle = vehicleState->target_actuation->throttle;
  vehicleState->act->steering = vehicleState->target_actuation->steering;
}

void onManualDrive()
{

  digitalWrite(LED_BUILTIN, LOW);
  // if button is not pressed, serial input is ignored, use controller input
  vehicleState->act->throttle = constrain(arduinoToROARConvert(throttle_pulse_time), 0, 1);
  vehicleState->act->steering = arduinoToROARConvert(steering_pulse_time);
  vehicleState->act->brake = arduinoToROARConvert(brake_pulse_time);
  processSerialCommunication(vehicleState, false);
}

void actuate(Actuation *act)
{
  writeToSteering(act->steering);
  // writeToBrake(act->brake);
  writeToThrottle(act->throttle);
}
