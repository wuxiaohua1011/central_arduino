#include <Arduino.h>
#include <arduino-timer.h>
#include <pin.h>
int max_hz = 3000; // ~5v
int min_hz = 40; // ~0v
int output_throttle_pwm = 1500;
int output_throttle_max = 2000;
int output_throttle_min = 1000;
double percent_duty_cycle = 0.1;

Timer<1, micros, const char *> pwm_voltage_timer_u;


int arduino_pwm_to_actual_pwm_duration(int microseconds) {
  // input is between 1000 to 2000
  int output_hz = map(microseconds, output_throttle_min,output_throttle_max, 40,3000);
  int output_duration = 1000000 / output_hz; 
  return output_duration;
}
void p_pwmOutHelper(int duration, double percent_duty_cycle, int pin_out)
{
  int time_high = int(duration * percent_duty_cycle);
  int time_low = duration - time_high;
  digitalWrite(pin_out, HIGH);
  delayMicroseconds(time_high);
  digitalWrite(pin_out, LOW);
  delayMicroseconds(time_low);
}

void pwm_out_from_arduino(int microseconds) {
  p_pwmOutHelper(arduino_pwm_to_actual_pwm_duration(microseconds), percent_duty_cycle, THROTTLE_OUTPUT_PIN);
}

void changeThrottleToNeutral() {
  pwm_out_from_arduino(1000);
}

void setupPwmVoltageConverter() {
  pinMode(THROTTLE_OUTPUT_PIN, OUTPUT);
}


void writeToThrottle() {
  int output = constrain(output_throttle_pwm, output_throttle_min, output_throttle_max);
  pwm_out_from_arduino(output);
}