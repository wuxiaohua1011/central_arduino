#include <utilities.h>
const char END_MARKER = '>';
const char START_MARKER = '<';
void writeStateToSerial(VehicleState *state, char startMarker, char endMarker)
{
    String output = String(startMarker);
    output += String(state->speed) + String(",");
    output += String(state->is_auto) + String(",");
    output += String(state->act->throttle) + String(",");
    output += String(state->act->steering) + String(",");
    output += String(state->act->brake);
    output += String(endMarker);
    Serial.println(output);
}
Actuation *parseActionData(char *buf, uint32_t len, char startMarker, char endMarker)
{
    char *token = strtok(buf, ",");
    Actuation *act = new Actuation();

    if (token[0] == startMarker)
    {
        if (token != NULL)
        { // the "a" in <a, THROTTLE, STEERING, BRAKE>
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            unsigned int curr_throttle_read = atoi(token);
            // TODO, remove hardcoding of 1500, 2000 here
            if (curr_throttle_read >= 1500 && curr_throttle_read <= 2000)
            {
                act->throttle = curr_throttle_read;
            }
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            unsigned int curr_steering_read = atoi(token);
            if (curr_steering_read >= 1000 && curr_steering_read <= 2000)
            {
                act->steering = curr_steering_read;
            }
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            unsigned int curr_brake_reading = atoi(token);
            if (curr_brake_reading >= 1000 && curr_brake_reading <= 2000)
            {
                act->brake = curr_brake_reading;
            }
        }
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
            Actuation *new_act = parseActionData(buf, buf_len, startMarker, endMarker);
            if (should_overwrite_state)
            {
                vehicleState->act = new_act;
                // vehicleState->act->throttle = new_act->throttle;
                // vehicleState->act->steering = new_act->steering;
                // vehicleState->act->brake = new_act->brake;
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