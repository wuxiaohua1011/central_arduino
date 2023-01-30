// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "steering_limiter.h"

SteeringLimiter::SteeringLimiter(uint32_t left_pin, uint32_t right_pin)
{
    this->left_limiter_pin = left_pin;
    this->right_limiter_pin = right_pin;
}

Status 
SteeringLimiter::setup()
{
    pinMode(this->left_limiter_pin, INPUT_PULLUP);
    pinMode(this->right_limiter_pin, INPUT_PULLUP);
    return Status::SUCCESS;
}

Status 
SteeringLimiter::loop()
{
    return Status::SUCCESS;
}

Status 
SteeringLimiter::cleanup()
{
    return Status::SUCCESS;
}

bool
SteeringLimiter::isLimiterOn(uint32_t pin)
{
    if (digitalRead(pin) == HIGH)
    {
        // nothing is pressing against limiter
        return false;
    }
    return true;
}
bool
SteeringLimiter::isLeftLimiterON()
{
    return this->isLimiterOn(this->left_limiter_pin);
}

bool SteeringLimiter::isRightLimiterON()
{
    return this->isLimiterOn(this->right_limiter_pin);
}
