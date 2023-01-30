// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pin.h"
#include "base_module.h"

const float LEFT_ANGLE = -30.0; // Minimun distance for actuator
const float RIGHT_ANGLE = 30.0; // Maximum safe distance that the actuator can move (inches)
float measureAngle();
class AngleSensor : public BaseModule
{
    

public:
    AngleSensor(int pin);
    Status setup();
    Status loop();
    Status cleanup();

private : 
    float currentAngle;
    int pin;
    const float LEFT_ANGLE = -30.0; 
    const float RIGHT_ANGLE = 30.0; 
};