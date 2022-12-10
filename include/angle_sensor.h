#include "pin.h"

const float LEFT_ANGLE = -30.0; // Minimun distance for actuator
const float RIGHT_ANGLE = 30.0; // Maximum safe distance that the actuator can move (inches)
int measureAngle()
{
    // read the input on analog pin 0:
    int sensorValue = analogRead(STEERING_ANGLE_SENSOR);
    float angle = map(sensorValue, 0, 1023, LEFT_ANGLE, RIGHT_ANGLE);
    return angle;
}
