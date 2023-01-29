#include "spark_max.h"
Servo servoSteering;
int output_steering_pwm = 1500;

void checkServoAttachments()
{
    if (servoSteering.attached() == false)
    {
        Serial.println("Reattaching steering pin");
        servoSteering.attach(STEERING_OUTPUT_PIN);
    }
}

void writeToSteering(float steering)
{
    // convert [-1, 1] to [1000, 2000]
    int steering_pwm = map(steering, -1, 1, OUTPUT_STEERING_MIN, OUTPUT_STEERING_MAX);
    servoSteering.writeMicroseconds(constrain(steering_pwm, OUTPUT_STEERING_MIN, OUTPUT_STEERING_MAX));
}

void setupSparkMax()
{
    servoSteering.attach(STEERING_OUTPUT_PIN);
}
