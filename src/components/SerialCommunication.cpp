// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
#include <Arduino.h>
#include "SerialCommunications.h"

SerialCommunicator::SerialCommunicator()
{
    
}
Status SerialCommunicator::setup()
{
    this->latest_vehicle_state = new VehicleState();
    this->actuation_received = new Actuation();
    return Status::SUCCESS;
}
Status SerialCommunicator::loop()
{
    this->processSerialCommunication(this->latest_vehicle_state);
    return Status::SUCCESS;
}
Status SerialCommunicator::cleanup()
{
    return Status::SUCCESS;
}

Actuation *SerialCommunicator::getAction()
{
    
    return this->actuation_received;
}
void SerialCommunicator::setVehicleState(VehicleState *vehicle_state)
{
    this->latest_vehicle_state = vehicle_state;
}

void SerialCommunicator::writeStateToSerial(VehicleState *state,
                                            char start_marker,
                                            char end_marker)
{

    Serial.print(state->current_actuation->throttle);
    Serial.print(",");
    Serial.print(state->current_actuation->steering);
    Serial.print(",");
    Serial.print(state->current_actuation->brake);
    Serial.print(",");
    Serial.print(state->is_auto);
    Serial.print(",");
    Serial.print(state->angle);

    Serial.println();
}

Actuation *SerialCommunicator::parseActionData(char *buf,
                                               uint32_t len,
                                               char start_marker,
                                               char end_marker)
{
    char *token = strtok(buf, ",");
    Actuation *act = new Actuation();
    float curr_throttle_reading = 0.0;
    float curr_steering_read = 0.0;
    float curr_brake_read = 0.0;
    if (token[0] == start_marker)
    {
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_throttle_reading = atof(token);
            if (curr_throttle_reading <= 0 || 1 <= curr_throttle_reading)
                return act;
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_steering_read = atof(token);
            if (curr_steering_read <= -1 || 1 <= curr_steering_read)
                return act;
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_brake_read = atof(token);
            if (curr_brake_read <= -1 || 1 <= curr_brake_read)
                return act;
        }
        act->throttle = curr_throttle_reading;
        act->steering = curr_steering_read;
        act->brake = curr_brake_read;
        return act;
    }
    return act;
}
void SerialCommunicator::parseSerialData(VehicleState *vehicle_state,
                                         char start_marker,
                                         char end_marker,
                                         uint32_t buf_len)
{
    char buf[buf_len];
    size_t num_read = Serial.readBytesUntil(end_marker, buf, buf_len);
    if (num_read > 1)
    {
        if (buf[1] == 's')
        {
            // if <'s'>
            writeStateToSerial(vehicle_state, start_marker, end_marker);
            return;
        }
        else if (buf[1] == 'a')
        {
            Actuation *new_act = parseActionData(buf, buf_len, start_marker, end_marker);
            this->actuation_received = new_act;
            return;
        }
    }

    return;
}

void SerialCommunicator::processSerialCommunication(VehicleState *vehicle_state)
{
    if (Serial.available() > 0)
    {
        if (Serial.peek() == START_MARKER)
        {
            parseSerialData(vehicle_state, START_MARKER, END_MARKER, 20);
        }
        else
        {
            // byte misalignment, discard
            while (Serial.available() && Serial.peek() != START_MARKER)
            {
                Serial.read();
            }
        }
    }
}