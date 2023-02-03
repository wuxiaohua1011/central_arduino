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
#include "actuator.h"

VehicleState *vehicle_state;

ModuleManager *module_manager;
LEDModule *led_module;
SteeringAngleSensor *steering_angle_sensor;
PWMVoltageConverterModule *pwm_to_voltage_converter;
RadioLinkModule *radio_link;
SteeringLimiter *steering_limiter;
SparkMaxModule *spark_max_module;
SerialCommunicator *serial_communicator;
ActuationModule *actuation_module;

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

/**
 * @brief This function sets up all the modules in the system.
 */
void setupModules();

/**
 * @brief This function synchronizes the state of all modules in the system. 
 * @note this function should run BEFORE moduleManager.loop()
 */
void synchronizeModules();
