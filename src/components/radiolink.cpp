// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "radiolink.h"

static uint32_t throttle_source_pin;
static uint32_t steering_source_pin;
static uint32_t brake_source_pin;
static uint32_t button_source_pin;

static volatile unsigned long throttle_timer_start;
static volatile unsigned long steering_timer_start;
static volatile unsigned long brake_timer_start;
static volatile unsigned long button_timer_start;

static volatile int throttle_last_interrupt_time;
static volatile int steering_last_interrupt_time;
static volatile int brake_last_interrupt_time;
static volatile int button_last_interrupt_time;

static volatile int throttle_pulse_time;
static volatile int steering_pulse_time;
static volatile int brake_pulse_time;
static volatile int button_pulse_time;

RadioLinkModule::RadioLinkModule(uint32_t throttle_pin, uint32_t steering_pin, uint32_t brake_pin, uint32_t button_pin)
{
    throttle_source_pin = throttle_pin;
    throttle_source_pin = throttle_pin;
    throttle_source_pin = throttle_pin;
    steering_source_pin = steering_pin;
    brake_source_pin = brake_pin;
    button_source_pin = button_pin;

    throttle_pulse_time = 1500;
    steering_pulse_time = 1500;
    brake_pulse_time = 1500;
    button_pulse_time = 1500;
}
Status RadioLinkModule::setup()
{
    throttle_timer_start = 0;
    steering_timer_start = 0;
    brake_timer_start = 0;
    button_timer_start = 0;
    attachInterrupt(throttle_source_pin, calcThrottleSignal, CHANGE);
    attachInterrupt(steering_source_pin, calcSteeringSignal, CHANGE);
    attachInterrupt(brake_source_pin, calcBrakeSignal, CHANGE);
    attachInterrupt(button_source_pin, calcButtonSignal, CHANGE);
    return Status::SUCCESS;
}
Status RadioLinkModule::loop()
{
    return Status::SUCCESS;
}
Status RadioLinkModule::cleanup()
{
    return Status::SUCCESS;
}
float RadioLinkModule::getSteering()
{
    int flagValue = 0;
    flagValue = steering_pulse_time;
    return pulseTimeToFloat(flagValue);
}

float RadioLinkModule::getThrottle()
{
    int flagValue = 0;
    flagValue = throttle_pulse_time;
    return pulseTimeToFloat(flagValue);
}

float RadioLinkModule::getBrake()
{
    int flagValue = 0;
    flagValue = brake_pulse_time;
    return pulseTimeToFloat(flagValue);
}
void RadioLinkModule::calcThrottleSignal()
{

    // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
    throttle_last_interrupt_time = micros();
    // if the pin has gone HIGH, record the microseconds since the Arduino started up
    if (digitalRead(throttle_source_pin) == HIGH)
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

void RadioLinkModule::calcSteeringSignal()
{

    // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
    steering_last_interrupt_time = micros();
    // if the pin has gone HIGH, record the microseconds since the Arduino started up
    if (digitalRead(steering_source_pin) == HIGH)
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

void RadioLinkModule::calcBrakeSignal()
{

    // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
    brake_last_interrupt_time = micros();
    // if the pin has gone HIGH, record the microseconds since the Arduino started up
    if (digitalRead(brake_source_pin) == HIGH)
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

void RadioLinkModule::calcButtonSignal()
{
    // record the interrupt time so that we can tell if the receiver has a signal from the transmitter
    button_last_interrupt_time = micros();
    // if the pin has gone HIGH, record the microseconds since the Arduino started up
    if (digitalRead(button_source_pin) == HIGH)
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

Actuation * RadioLinkModule::getRadioLinkActuation() 
{    
    Actuation * act = new Actuation();
    act->throttle = this->pulseTimeToFloat(throttle_pulse_time);
    act->steering = this->pulseTimeToFloat(steering_pulse_time);
    act->brake = this->pulseTimeToFloat(brake_pulse_time);
    act->reverse = false;
    return act;
}

bool RadioLinkModule::isAutoFromButton()
{
    return button_pulse_time >= 1600;
}

float
RadioLinkModule::pulseTimeToFloat(uint32_t pulse_time)
{
    float val = constrain(pulse_time, 1000, 2000);
    val = (val - 1000.0) / (2000.0 - 1000.0) * (1 - -1) + -1;
    return val;
}
