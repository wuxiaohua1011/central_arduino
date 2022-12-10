#include "pin.h"

const float LEFT_ANGLE = -30.0; // Minimun distance for actuator
const float RIGHT_ANGLE = 30.0; // Maximum safe distance that the actuator can move (inches)
float measureAngle()
{
    float sensorValue = analogRead(STEERING_ANGLE_SENSOR);
    float angle = (sensorValue - 0) / (1023 - 0) * (RIGHT_ANGLE - LEFT_ANGLE) + LEFT_ANGLE;
    return angle;
}
