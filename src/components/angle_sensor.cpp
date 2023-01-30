#include <Arduino.h>

#include "pin.h"
#include "angle_sensor.h"

SteeringAngleSensor::SteeringAngleSensor(int pin)
{
    this->pin = pin;
}

Status SteeringAngleSensor::setup()
{
    if (this->pin)
    {
        return Status::SUCCESS;
    }
    return Status::FAILED;
}

Status SteeringAngleSensor::loop()
{
    if (!this->pin)
    {
        return Status::FAILED;
    }
    
    float sensorValue = analogRead(this->pin);
    float angle = (sensorValue - 0) / (1023 - 0) * (this->RIGHT_ANGLE - this->LEFT_ANGLE) + this->LEFT_ANGLE;
    this->currentAngle = angle;
    return Status::SUCCESS;
}

Status SteeringAngleSensor::cleanup()
{
    return Status::SUCCESS;
}

float SteeringAngleSensor::getSteeringAngle()
{
    return this->currentAngle;
}
float SteeringAngleSensor::getAngularVelocity()
{
    return 0.0;
}