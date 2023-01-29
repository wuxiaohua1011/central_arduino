// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pin.h"
#include "utilities.h"


bool isLimiterOn(int pin);

void updateLimiterStates(VehicleState *state);

void setupSteeringLimiters();
