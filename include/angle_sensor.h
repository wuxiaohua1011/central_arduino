// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pin.h"
#include "base_module.h"
class SteeringAngleSensor : public BaseModule
{
public:
    SteeringAngleSensor(int pin);
    Status setup();
    Status loop();
    Status cleanup();

    float getSteeringAngle();
    float getAngularVelocity();

private : 
    float currentAngle;
    int pin;
    const float LEFT_ANGLE = -30.0; 
    const float RIGHT_ANGLE = 30.0; 
};