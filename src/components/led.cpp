// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "led.h"

LEDModule::LEDModule(int pin, uint32_t blink_interval=500) 
{
    this->pin = pin;
    this->led_builtin_was_on = false;
    this->blink_interval=500;
    this->last_blink_time = millis();
    this->mode = LEDMode::Blink;
}

Status LEDModule::setup()
{
    pinMode(pin, OUTPUT);
    return Status::SUCCESS;
}

Status LEDModule::loop()
{
    switch (this->mode)
    {
    case LEDMode::Blink:
        this->blink();
        break;
    case LEDMode::ON:
        this->blink();
        break;
    default:
        this->turnOff();
        break;
    }
    return Status::SUCCESS;
}

Status LEDModule::cleanup()
{
    this->turnOff();
    return Status::SUCCESS;
}

Status LEDModule::setMode(LEDMode desiredMode)
{
    this->mode = desiredMode;
    return Status::SUCCESS;
}
void LEDModule::turnOn()
{
    digitalWrite(this->pin, HIGH); // turn the LED on (HIGH is the voltage level)
    this->led_builtin_was_on = true;
}
void LEDModule::turnOff()
{
    digitalWrite(this->pin, LOW); // turn the LED off by making the voltage LOW
    this->led_builtin_was_on = false;
}
void LEDModule::blink()
{
    if (millis() - this->last_blink_time > this->blink_interval)
    {
        if (this->led_builtin_was_on)
        {
            this->turnOff();
        }
        else
        {
            this->turnOn();
        }
        this->last_blink_time = millis();
    }
}
