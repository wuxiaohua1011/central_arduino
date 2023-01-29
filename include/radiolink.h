// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <pin.h>


extern volatile int throttle_pulse_time;
extern volatile int steering_pulse_time;
extern volatile int brake_pulse_time;
extern volatile int button_pulse_time;

void calcThrottleSignal();

void calcSteeringSignal();

void calcBrakeSignal();

void calcButtonSignal();

void setupRadioLink();