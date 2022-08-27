#include <Arduino.h>
#include <pin.h>
int max_hz = 4000; // ~5v
int min_hz = 40;   // ~0v
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
  int output_hz = map(microseconds, output_throttle_min, output_throttle_max, min_hz, max_hz);
  uint32_t output_duration = uint32_t(1000000 / output_hz);
  output_helper(output_duration, 0.1, 8);
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