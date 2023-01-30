// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "base_module.h"
enum class LEDMode
{
    Blink,
    ON,
    OFF
};

class LEDModule : public BaseModule
{
public:
    LEDModule(int pin, uint32_t blink_interval);
    Status setup();
    Status loop();
    Status cleanup();
    Status setMode(LEDMode desiredMode);

private:
    void blink();
    void turnOn();
    void turnOff();
    bool led_builtin_was_on;
    int pin;
    uint32_t blink_interval;
    uint32_t last_blink_time;
    LEDMode mode;

};
