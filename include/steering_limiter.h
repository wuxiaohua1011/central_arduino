// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
#ifndef _STEERING_LIMITOR_h
#define _STEERING_LIMITOR_h

#include "models.h"
#include "base_module.h"
    class SteeringLimiter : public BaseModule
{
public:
    SteeringLimiter(uint32_t left_pin, uint32_t right_pin);
    Status setup();
    Status loop();
    Status cleanup();

    bool isLeftLimiterON();
    bool isRightLimiterON();

private:
    bool isLimiterOn(uint32_t pin);

    uint32_t left_limiter_pin;
    uint32_t right_limiter_pin;
};

#endif //_STEERING_LIMITOR_h