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

    this->addReading(this->currentAngle);
    this->currentAngularVelocity = this->calcVelocity();

    return Status::SUCCESS;
}

void SteeringAngleSensor::addReading(float reading)
{
    reading_buffer.push(reading);
    timestamp_buffer.push(millis());
}

float SteeringAngleSensor::calcVelocity()
{
    if (reading_buffer.size() != STEERING_ANGLE_BUFFER_LEN || timestamp_buffer.size() != STEERING_ANGLE_BUFFER_LEN) {
        return 0.0;
    }
    // find the earliest timestamp
    uint32_t min_timestamp_index = -1;
    uint32_t min_timestamp = millis();
    for (uint32_t i = 0; i < timestamp_buffer.size(); i ++)
    {
        if (timestamp_buffer[i] < min_timestamp) {
            min_timestamp_index = i;
        }   
    }
    // find average velocity between each pair
    float total = 0;
    for (size_t i = 0; i < STEERING_ANGLE_BUFFER_LEN - 1; i++)
    {
        size_t curr_index = (min_timestamp_index + i) % STEERING_ANGLE_BUFFER_LEN;
        size_t next_index = (min_timestamp + i + 1) % STEERING_ANGLE_BUFFER_LEN;

        float curr_reading = reading_buffer[curr_index];
        float next_reading = reading_buffer[next_index];

        float velocity = next_reading - curr_reading;
        total += velocity;
    }

    float avg_velocity = total / STEERING_ANGLE_BUFFER_LEN;

    return avg_velocity;
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
    return this->currentAngularVelocity;
}