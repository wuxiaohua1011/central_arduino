// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <utilities.h>
#include <ArduinoJson.h>

const char END_MARKER = '>';
const char START_MARKER = '<';
StaticJsonDocument<512> stateJSON;

void writeStateToSerial(VehicleState *state, char startMarker, char endMarker){
    // stateJSON["speed"] = state->speed;
    // // stateJSON["is_auto"] = state->is_auto;
    // // stateJSON["angle"] = state->angle;
    // // stateJSON["actuation.throttle"] = state->act->throttle;
    // // stateJSON["actuation.steering"] = state->act->steering;
    // // stateJSON["actuation.brake"] = state->act->brake;
    // // stateJSON["target.brake"] = state->target->brake;
    // // stateJSON["target.steering"] = state->target->steering;
    // // stateJSON["target.speed"]=state->target->speed;
    // serializeMsgPack(stateJSON, Serial);
    Serial.print(state->target->speed);
    Serial.print(",");
    Serial.print(state->target->steering);
    Serial.print(",");
    Serial.print(state->target->brake);
    Serial.print(",");

    Serial.print(state->act->throttle);
    Serial.print(",");
    Serial.print(state->act->steering);
    Serial.print(",");
    Serial.print(state->act->brake);
    Serial.print(",");

    Serial.print(state->speed, 2);
    Serial.print(",");
    Serial.print(state->is_auto);
    Serial.print(",");
    Serial.print(state->angle);

    Serial.println();
} TargetActions *parseActionData(char *buf, uint32_t len, char startMarker, char endMarker)
{
    char *token = strtok(buf, ",");
    TargetActions *act = new TargetActions();
    float curr_speed_reading = 0.0;
    float curr_steering_read = 0.0;
    float curr_brake_read = 0.0;
    if (token[0] == startMarker)
    {
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_speed_reading = atof(token);
            if (curr_speed_reading <= -1 || 1 <= curr_speed_reading)
                return act;
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_steering_read = atof(token);
            if (curr_steering_read <= -1 || 1 <= curr_steering_read) return act;
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            curr_brake_read = atof(token);
            if (curr_brake_read <= -1 || 1 <= curr_brake_read) return act;
        }
        act->speed = curr_speed_reading;
        act->steering = curr_steering_read;
        act->brake = curr_brake_read;
        return act;
    }
    return act;
}
void parseSerialData(VehicleState *vehicleState, char startMarker, char endMarker, uint32_t buf_len = 20, bool should_overwrite_state = false)
{
    char buf[buf_len];
    size_t num_read = Serial.readBytesUntil(endMarker, buf, buf_len);
    if (num_read > 1)
    {
        if (buf[1] == 's')
        {
            // if <'s'>
            writeStateToSerial(vehicleState, startMarker, endMarker);
            return;
        }
        else if (buf[1] == 'a')
        {
            TargetActions *new_target = parseActionData(buf, buf_len, startMarker, endMarker);
            if (should_overwrite_state)
            {
                vehicleState->target = new_target;
            }
            return;
        }
    }

    return;
}

void processSerialCommunication(VehicleState *vehicleState, bool should_overwrite_state)
{
    if (Serial.available() > 0)
    {
        if (Serial.peek() == START_MARKER)
        {
            parseSerialData(vehicleState, START_MARKER, END_MARKER, 20, should_overwrite_state);
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