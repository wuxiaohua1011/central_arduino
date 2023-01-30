#include "spark_max.h"
int output_steering_pwm = 1500;
SparkMaxModule::SparkMaxModule(uint32_t pin)
{
    this->pin = pin;
}

Status SparkMaxModule::setup()
{
    servoSteering.attach(this->pin);
    return Status::SUCCESS;
}
Status SparkMaxModule::loop()
{
    this->checkServoAttachments();
    return Status::SUCCESS;
}
Status SparkMaxModule::cleanup()
{
    return Status::SUCCESS;
}

void SparkMaxModule::checkServoAttachments()
{
    if (servoSteering.attached() == false)
    {
        servoSteering.attach(this->pin);
    }
}

void SparkMaxModule::writeToSteering(float steering)
{
    // convert [-1, 1] to [1000, 2000]
    int steering_pwm = map(steering, -1, 1, OUTPUT_STEERING_MIN, OUTPUT_STEERING_MAX);
    servoSteering.writeMicroseconds(constrain(steering_pwm, OUTPUT_STEERING_MIN, OUTPUT_STEERING_MAX));
}
