// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "base_module.h"
#include "models.h"

class RadioLinkModule : public BaseModule
{
    static void calcThrottleSignal();
    static void calcSteeringSignal();
    static void calcBrakeSignal();
    static void calcButtonSignal();

public:
    RadioLinkModule(uint32_t throttle_source_pin, uint32_t steering_source_pin, uint32_t brake_source_pin, uint32_t button_source_pin);
    Status setup();
    Status loop();
    Status cleanup();

    Actuation * getRadioLinkActuation();
    bool isAutoFromButton();
    float getSteering();
    float getThrottle();
    float getBrake();

private:
    float pulseTimeToFloat(uint32_t pulse_time);
};