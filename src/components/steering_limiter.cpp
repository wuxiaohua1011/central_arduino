// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "steering_limiter.h"

bool isLimiterOn(int pin)
{
    if (digitalRead(pin) == HIGH)
    {
        // nothing is pressing against limiter
        return false;
    }
    return true;
}

void updateLimiterStates(VehicleState *state)
{
    state->isSteeringLeftLimiterOn = isLimiterOn(STEERING_LEFT_LIMITER);
    state->isSteeringRightLimiterOn = isLimiterOn(STEERING_RIGHT_LIMITER);
}

void setupSteeringLimiters()
{
    pinMode(STEERING_LEFT_LIMITER, INPUT_PULLUP);
    pinMode(STEERING_RIGHT_LIMITER, INPUT_PULLUP);
}
