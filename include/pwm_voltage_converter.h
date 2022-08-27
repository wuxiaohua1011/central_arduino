#include <Arduino.h>
#include <pin.h>
int max_hz = 3000; // ~5v
int min_hz = 40;   // ~0v
int output_throttle_pwm = 1500;
int output_throttle_max = 2000;
int output_throttle_neu = 1500;
int output_throttle_min = 1500;
double percent_duty_cycle = 0.1;

/**
 * @brief  map arduino Servo's Microsecond to pwm duration
 * @note
 * @param  microseconds: Servo's microsecond
 * @retval duration equivalent of arduino's microsecond
 */
int arduino_pwm_to_actual_pwm_duration(int microseconds)
{
  // input is between 1000 to 2000
  int output_hz = map(microseconds, output_throttle_min, output_throttle_max, 40, 3000);
  int output_duration = 1000000 / output_hz;
  return output_duration;
}

/**
 * @brief  fake a pwm signal using digital pin
 * @note
 * @param  duration: duration of the HIGH
 * @param  percent_duty_cycle: duty cycle of HIGH
 * @param  pin_out: digital pin to simulate PWM
 * @retval None
 */
void p_pwmOutHelper(int duration, double percent_duty_cycle, int pin_out)
{
  int time_high = int(duration * percent_duty_cycle);
  int time_low = duration - time_high;
  digitalWrite(pin_out, HIGH);
  delayMicroseconds(time_high);
  digitalWrite(pin_out, LOW);
  delayMicroseconds(time_low);
}

/**
 * @brief  given a Arduino Servo microsecond, convert that into PWM khz on THROTTLE_OUTPUT_PIN
 * @note
 * @param  microseconds: arduino's Servo Microsecond
 * @retval None
 */
void pwm_out_from_arduino(int microseconds)
{
  p_pwmOutHelper(arduino_pwm_to_actual_pwm_duration(microseconds), percent_duty_cycle, THROTTLE_OUTPUT_PIN);
}

/**
 * @brief  change throttle to neutral
 * @note
 * @retval None
 */
void changeThrottleToNeutral()
{
  pwm_out_from_arduino(output_throttle_neu);
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
  int output = constrain(throttle, output_throttle_min, output_throttle_max);
  pwm_out_from_arduino(output);
}