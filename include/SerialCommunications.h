// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "models.h"

const char END_MARKER = '>';
const char START_MARKER = '<';

void writeStateToSerial(VehicleState *state, 
                        char startMarker, 
                        char endMarker);


Actuation *parseActionData(char *buf, 
                           uint32_t len, 
                           char startMarker, 
                           char endMarker);

void parseSerialData(VehicleState *vehicleState, 
                     char startMarker, 
                     char endMarker, 
                     uint32_t buf_len = 20, 
                     bool should_overwrite_state = false);

void processSerialCommunication(VehicleState *vehicleState, 
                                bool should_overwrite_state);