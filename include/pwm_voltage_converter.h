#include <Arduino.h>
#include <pin.h>
int max_hz = 3500; // ~5v
int min_hz = 50;   // ~0v
int output_throttle_pwm = 1500;
int output_throttle_max = 2000;
int output_throttle_neu = 1500;
int output_throttle_min = 1500;
double percent_duty_cycle = 0.1;

void output_helper(uint32_t duration, double percent_duty_cycle, uint32_t pinout)
{
  uint32_t time_high = uint32_t(duration * percent_duty_cycle);
  uint32_t time_low = duration - time_high;
  digitalWrite(pinout, HIGH);
  delayMicroseconds(time_high); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(pinout, LOW);
  delayMicroseconds(time_low);
}

void actuateFromArduinoPWM(int microseconds)
{
  int output_hz = constrain(map(microseconds, output_throttle_min, output_throttle_max, min_hz, max_hz), 125, 3500);
  uint32_t output_duration = uint32_t(1000000 / output_hz);
  uint32_t time_high = uint32_t(output_duration * percent_duty_cycle);
  uint32_t time_low = output_duration - time_high;
  digitalWrite(THROTTLE_OUTPUT_PIN, HIGH);
  delayMicroseconds(time_high); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(THROTTLE_OUTPUT_PIN, LOW);
  delayMicroseconds(time_low);
}

/**
 * @brief  setup PWM to voltage converter
 * @note
 * @retval None
 */
void setupPwmVoltageConverter()
{
  pinMode(THROTTLE_OUTPUT_PIN, OUTPUT);
}

/**
 * @brief  write to throttle
 * @note
 * @retval None
 */
void writeToThrottle(int throttle)
{
  actuateFromArduinoPWM(throttle);
}