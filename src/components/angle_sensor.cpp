#include <Arduino.h>

#include "pin.h"
#include "angle_sensor.h"

float measureAngle()
{
    float sensorValue = analogRead(STEERING_ANGLE_SENSOR);
    float angle = (sensorValue - 0) / (1023 - 0) * (RIGHT_ANGLE - LEFT_ANGLE) + LEFT_ANGLE;
    return angle;
}
