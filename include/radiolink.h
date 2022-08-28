#include <Arduino.h>
#include <pin.h>
volatile unsigned long throttle_timer_start;
volatile unsigned long steering_timer_start;
volatile unsigned long brake_timer_start;
volatile unsigned long button_timer_start;

volatile int throttle_last_interrupt_time;
volatile int steering_last_interrupt_time;
volatile int brake_last_interrupt_time;
volatile int button_last_interrupt_time;

volatile int throttle_pulse_time = 1500;
volatile int steering_pulse_time = 1500;
volatile int brake_pulse_time = 1500;
volatile int button_pulse_time = 1500;

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
      throttle_pulse_time = constrain(((volatile int)micros() - throttle_timer_start), 1000, 2000);
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
      steering_pulse_time = constrain(((volatile int)micros() - steering_timer_start), 1000, 2000);
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
      brake_pulse_time = constrain(((volatile int)micros() - brake_timer_start), 1000, 2000);
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

void setupRadioLink()
{
  throttle_timer_start = 0;
  steering_timer_start = 0;
  brake_timer_start = 0;
  button_timer_start = 0;
  attachInterrupt(THROTTLE_SOURCE, calcThrottleSignal, CHANGE);
  attachInterrupt(STEERING_SOURCE, calcSteeringSignal, CHANGE);
  attachInterrupt(BRAKE_SOURCE, calcBrakeSignal, CHANGE);
  attachInterrupt(BUTTON_SOURCE, calcButtonSignal, CHANGE);
}
