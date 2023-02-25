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
    Serial.print(",");
    Serial.print(state->angular_velocity);
    Serial.println();
}

void SerialCommunicator::parseActionData(char *buf,
                                               uint32_t len,
                                               char start_marker,
                                               char end_marker)
{
    // buf = a,0.5,0.5,0.5
    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(buf,",");      // get the first part - the string


    strtokIndx = strtok(NULL, ","); 
    float curr_throttle_reading = atof(strtokIndx);   

    strtokIndx = strtok(NULL, ","); 
    float curr_steering_read = atof(strtokIndx);   

    strtokIndx = strtok(NULL, ","); 
    float curr_brake_read = atof(strtokIndx);     

    this->actuation_received->throttle = curr_throttle_reading;
    this->actuation_received->steering = curr_steering_read;
    this->actuation_received->brake = curr_brake_read;
}
void SerialCommunicator::parseSerialData(VehicleState *vehicle_state,
                                         char start_marker,
                                         char end_marker,
                                         uint32_t buf_len)
{
    if (receivedChars[0] == 's') {
        writeStateToSerial(vehicle_state, start_marker, end_marker);
        return;
    } 
    else if (receivedChars[0] == 'a')
    {
        parseActionData(receivedChars, this->numChars, start_marker, end_marker);
        return;
    }

    return;
}

void SerialCommunicator::processSerialCommunication(VehicleState *vehicle_state)
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != END_MARKER) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == START_MARKER) {
            recvInProgress = true;
        }
    }

    if (newData == true) {
        this->parseSerialData(vehicle_state, START_MARKER, END_MARKER);
        newData = false;
    }
}