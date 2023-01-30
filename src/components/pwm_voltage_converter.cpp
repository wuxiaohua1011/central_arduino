// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <SAMDUE_PWM.h>

#include "pin.h"
#include "pwm_voltage_converter.h"


PWMVoltageConverterModule::PWMVoltageConverterModule(int pin)
{
    this->pin = pin;
    this->throttle = 0.0;
}
Status PWMVoltageConverterModule::setup()
{
    PWM_Instance = new SAMDUE_PWM(this->pin, IDLE_FREQUENCY, 20.0f);
    return Status::SUCCESS;
}
Status PWMVoltageConverterModule::loop()
{
    this->writeToThrottle(this->throttle);
    return Status::SUCCESS;

}
Status PWMVoltageConverterModule::cleanup()
{
    this->writeToThrottle(0.0);
    return Status::SUCCESS;
}

void PWMVoltageConverterModule::actuateFromArduinoPWM(float throttle)
{
    throttle = constrain(throttle, 0, 1);
    float frequency = (throttle - 0) / (1 - 0) * (MAX_HZ - MIN_HZ) + MIN_HZ;
    PWM_Instance->setPWM(THROTTLE_OUTPUT_PIN, frequency, DUTY_CYCLE);
}

/**
 * @brief  write to throttle
 * @note
 * @retval None
 */
void PWMVoltageConverterModule::writeToThrottle(float throttle)
{
    actuateFromArduinoPWM(throttle);
}

float PWMVoltageConverterModule::arduinoToROARConvert(int pulse_time)
{
    return (pulse_time - 1000.0) / (2000.0 - 1000) * (1 - -1) + -1;
}

