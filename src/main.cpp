/**
 * By Michael Wu on July 9, 2022.
 * reference from https://www.camelsoftware.com/2015/12/25/reading-pwm-signals-from-an-rc-receiver-with-arduino/
 *
 * Please wire up your PWM Inputs on Digital Pins and revise the *_SOURCE fields to the corresponding pin numbers.
 * only arduino ble nano 33 and arduino due are tested
 *
 **/
#include <Arduino.h>
#include <Servo.h>

#define STEERING_SOURCE 2
#define THROTTLE_SOURCE 3
#define BRAKE_SOURCE 4
#define BUTTON_SOURCE 5
#define STEERING_OUTPUT_PIN 6
#define BRAKE_OUTPUT_PIN 7

volatile unsigned long throttle_timer_start;
volatile unsigned long steering_timer_start;
volatile unsigned long brake_timer_start;
volatile unsigned long button_timer_start;

volatile int throttle_last_interrupt_time;
volatile int steering_last_interrupt_time;
volatile int brake_last_interrupt_time;
volatile int button_last_interrupt_time;

volatile int throttle_pulse_time;
volatile int steering_pulse_time;
volatile int brake_pulse_time;
volatile int button_pulse_time;

int output_throttle_pwm = 1500;
int output_steering_pwm = 1500;
int output_brake_pwm = 1500;

int output_throttle_max = 2000;
int output_throttle_min = 1000;
int output_steering_max = 1700;
int output_steering_min = 1300;
int output_brake_max = 1800;
int output_brake_min = 1500;

Servo servoSteering;
Servo servoBrake;

bool led_builtin_was_on = false;
void calcThrottleSignal()
{
  // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
  throttle_last_interrupt_time = micros();
  // if the pin has gone HIGH, record the microseconds since the Arduino started up
  if (digitalRead(THROTTLE_SOURCE) == HIGH)
  {
    throttle_timer_start = micros();
  }
  // otherwise, the pin has gone LOW
  else
  {
    // only worry about this if the timer has actually started
    if (throttle_timer_start != 0)
    {
      // record the pulse time
      throttle_pulse_time = ((volatile int)micros() - throttle_timer_start);
      // restart the timer
      throttle_timer_start = 0;
    }
  }
}

void calcSteeringSignal()
{
  // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
  steering_last_interrupt_time = micros();
  // if the pin has gone HIGH, record the microseconds since the Arduino started up
  if (digitalRead(STEERING_SOURCE) == HIGH)
  {
    steering_timer_start = micros();
  }
  // otherwise, the pin has gone LOW
  else
  {
    // only worry about this if the timer has actually started
    if (steering_timer_start != 0)
    {
      // record the pulse time
      steering_pulse_time = ((volatile int)micros() - steering_timer_start);
      // restart the timer
      steering_timer_start = 0;
    }
  }
}

void calcBrakeSignal()
{
  // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
  brake_last_interrupt_time = micros();
  // if the pin has gone HIGH, record the microseconds since the Arduino started up
  if (digitalRead(BRAKE_SOURCE) == HIGH)
  {
    brake_timer_start = micros();
  }
  // otherwise, the pin has gone LOW
  else
  {
    // only worry about this if the timer has actually started
    if (brake_timer_start != 0)
    {
      // record the pulse time
      brake_pulse_time = ((volatile int)micros() - brake_timer_start);
      // restart the timer
      brake_timer_start = 0;
    }
  }
}

void calcButtonSignal()
{
  // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
  button_last_interrupt_time = micros();
  // if the pin has gone HIGH, record the microseconds since the Arduino started up
  if (digitalRead(BUTTON_SOURCE) == HIGH)
  {
    button_timer_start = micros();
  }
  // otherwise, the pin has gone LOW
  else
  {
    // only worry about this if the timer has actually started
    if (button_timer_start != 0)
    {
      // record the pulse time
      button_pulse_time = ((volatile int)micros() - button_timer_start);
      // restart the timer
      button_timer_start = 0;
    }
  }
}

void printRawStatus()
{
  Serial.print("RAW --> THROTTLE: ");
  Serial.print(throttle_pulse_time);

  Serial.print(" | STEERING: ");
  Serial.print(steering_pulse_time);

  Serial.print(" | BRAKE: ");
  Serial.print(brake_pulse_time);

  Serial.print(" | BUTTON: ");
  Serial.println(button_pulse_time);
}

void printOuputValues()
{
  Serial.print("OUTPUT --> THROTTLE: ");
  Serial.print(output_throttle_pwm);

  Serial.print(" | STEERING: ");
  Serial.print(output_steering_pwm);

  Serial.print(" | BRAKE: ");
  Serial.println(output_brake_pwm);
}
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

void writeToServo()
{
  servoSteering.writeMicroseconds(output_steering_pwm);
  servoBrake.writeMicroseconds(output_brake_pwm);
}

void constrain_outputs()
{
  output_brake_pwm = constrain(output_brake_pwm, output_brake_min, output_brake_max);
  output_steering_pwm = constrain(output_steering_pwm, output_steering_min, output_steering_max);
  output_throttle_pwm = constrain(output_throttle_pwm, output_throttle_min, output_throttle_max);
}
void blink_builtin_led()
{
  if (led_builtin_was_on == true)
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    led_builtin_was_on = false;
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    led_builtin_was_on = true;
  }
}

void changeToNeutral()
{
  output_steering_pwm = 1500;
  output_throttle_pwm = 1500;
}
void setup()
{
  // Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  servoSteering.attach(STEERING_OUTPUT_PIN);
  servoBrake.attach(BRAKE_OUTPUT_PIN);
  throttle_timer_start = 0;
  steering_timer_start = 0;
  brake_timer_start = 0;
  button_timer_start = 0;
  attachInterrupt(THROTTLE_SOURCE, calcThrottleSignal, CHANGE);
  attachInterrupt(STEERING_SOURCE, calcSteeringSignal, CHANGE);
  attachInterrupt(BRAKE_SOURCE, calcBrakeSignal, CHANGE);
  attachInterrupt(BUTTON_SOURCE, calcButtonSignal, CHANGE);
}

void loop()
{

  // printRawStatus();
  // if button is pressed, use serial inputs
  if (button_pulse_time > 1500)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    changeToNeutral();
    // TODO: parse serial inputs
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    // if button is not pressed, serial input is ignored, use controller input
    output_throttle_pwm = throttle_pulse_time;
    output_steering_pwm = steering_pulse_time;
    output_brake_pwm = brake_pulse_time;
  }

  constrain_outputs();
  writeToServo();
  // printOuputValues();
  // Serial.println();
}
