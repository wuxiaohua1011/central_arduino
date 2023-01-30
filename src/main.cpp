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
#include <assert.h>

void setup()
{
  Serial.begin(115200);
  setupModules();
  
}

void loop()
{
  module_manager->loop();
}

void setupModules()
{
  module_manager = new ModuleManager(1);
  
  led_module = new LEDModule(LED_BUILTIN, 500);
  module_manager->setupModule(led_module);

  steering_angle_sensor = new SteeringAngleSensor(STEERING_ANGLE_SENSOR);
  module_manager->setupModule(steering_angle_sensor);

  pwm_to_voltage_converter = new PWMVoltageConverterModule(THROTTLE_OUTPUT_PIN);
  module_manager->setupModule(pwm_to_voltage_converter);
}

void updateModules()
{
  
}