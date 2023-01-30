// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "pin.h"
#include "module_manager.h"
#include "led.h"
#include "angle_sensor.h"
#include "pwm_voltage_converter.h"
#include "radiolink.h"
#include "steering_limiter.h"
#include "spark_max.h"
#include "SerialCommunications.h"

VehicleState *vehicle_state;

ModuleManager *module_manager;
LEDModule *led_module;
SteeringAngleSensor *steering_angle_sensor;
PWMVoltageConverterModule *pwm_to_voltage_converter;
RadioLinkModule *radio_link;
SteeringLimiter *steering_limiter;
SparkMaxModule *spark_max_module;
SerialCommunicator *serial_communicator;

/**
 * @brief  main setup function
 * @note
 * @retval None
 */
void
setup();

/**
 * @brief  main loop
 * @note
 * @retval None
 */
void loop();


void setupModules();

void synchronizeModules();

void actuate();

void p_auto_drive();

void p_manual_drive();