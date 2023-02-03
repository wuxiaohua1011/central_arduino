// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
#ifndef _SPARK_MAX_MODULE_h
#define _SPARK_MAX_MODULE_h
#include <Servo.h>
#include <Arduino.h>

#include "base_module.h"
class SparkMaxModule : public BaseModule
{
const int OUTPUT_STEERING_MAX = 2000;
const int OUTPUT_STEERING_MIN = 1000;

public:
    SparkMaxModule(uint32_t pin);
    Status setup();
    Status loop();
    Status cleanup();
    void writeToSteering(float steering);

private:
    uint32_t pin;
    void checkServoAttachments();
    void setupSparkMax();
    Servo servoSteering;
};

#endif // _SPARK_MAX_MODULE_h