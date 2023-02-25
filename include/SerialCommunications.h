// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "models.h"

#include "base_module.h"
class SerialCommunicator : public BaseModule
{

const char END_MARKER = '>';
const char START_MARKER = '<';
const byte numChars = 32;

public:
    SerialCommunicator();
    Status setup();
    Status loop();
    Status cleanup();

    Actuation* getAction();
    void setVehicleState(VehicleState *vehicle_state);

private:
    void writeStateToSerial(VehicleState *state,
                            char start_marker,
                            char end_marker);
    Actuation *parseActionData(char *buf,
                               uint32_t len,
                               char start_marker,
                               char end_marker);
    void parseSerialData(VehicleState *vehicle_state,
                         char start_marker,
                         char end_marker,
                         uint32_t buf_len = 20);

    void processSerialCommunication(VehicleState *vehicle_state);

    VehicleState * latest_vehicle_state;
    Actuation * actuation_received;

    char receivedChars[32]; // make sure this is the same as numChars
    boolean newData = false;


};









