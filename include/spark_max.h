#include <Servo.h>
#include <pin.h>
#include <Arduino.h>
Servo servoSteering;
Servo servoBrake;


int output_steering_pwm = 1500;
int output_brake_pwm = 1500;
int output_steering_max = 1700;
int output_steering_min = 1300;
int output_brake_max = 1800;
int output_brake_min = 1500;
void checkServoAttachments()
{
  if (servoSteering.attached() == false)
  {
    Serial.println("Reattaching steering pin");
    servoSteering.attach(STEERING_OUTPUT_PIN);
  }
  if (servoBrake.attached() == false)
  {
    Serial.println("Reattaching brake pin");
    servoBrake.attach(BRAKE_OUTPUT_PIN);
  }
}

void writeToSteering() {
  servoSteering.writeMicroseconds(constrain(output_steering_pwm, output_steering_min, output_steering_max));

}
void writeToBrake() {
  servoBrake.writeMicroseconds(constrain(output_brake_pwm, output_brake_min, output_brake_max));

}

void changeSteeringToNeutral()
{
  output_steering_pwm = 1500;
}

void changeBrakeToNeutral()
{
  output_brake_pwm = 1000;
}

void setupSparkMax() {
    servoSteering.attach(STEERING_OUTPUT_PIN);
    servoBrake.attach(BRAKE_OUTPUT_PIN);
}
