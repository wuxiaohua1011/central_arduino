
#include <CircularBuffer.h>
#include <Arduino.h>
#include <pin.h>

const double WHEEL_DIAMETER = 0.065; // in meter
uint32_t STALE_THRESHOLD = 5 * 1000; // 5 seconds
uint32_t LIGHT_SPEED = 299792458;

uint32_t last_magnet_time;
bool rotation_count_started = false;
const int buffer_size = 10;
CircularBuffer<int, buffer_size> speed_readings;
uint32_t minute_to_milisecond = 60000;
uint32_t magnet_hit_threshold = 100;

/**
 * @brief  Calculate whether magnet has been passed through, put the time from last pass in a circular buffer
 * @note   must be placed in main loop
 * @retval None
 */
void loopSpeedEstimation()
{
  uint32_t val = analogRead(SPEED_SENSOR_INPUT_PIN);

  if (val > 300 && val < 800)
  {
    // speed sensor not connected
    speed_readings.clear();
    last_magnet_time = millis();
    rotation_count_started = false;
    return;
  }

  if (val > magnet_hit_threshold && rotation_count_started == false)
  {
    // if this is the first rotation
    rotation_count_started = true;
    last_magnet_time = millis();
  }
  else if (val > magnet_hit_threshold && rotation_count_started == true)
  {
    // if this is not the first rotation
    uint32_t curr_time = millis();

    if (curr_time - last_magnet_time > magnet_hit_threshold)
    {
      int time_diff = (curr_time - last_magnet_time);
      speed_readings.push(time_diff);
      last_magnet_time = curr_time;
    }
  }
  else if (millis() - last_magnet_time > STALE_THRESHOLD)
  {
    // if stale detected, refresh last_magnet time
    last_magnet_time = millis();
    speed_readings.clear();
  }
}

/**
 * @brief  calculates the Rotation Per Minute given a circular buffer of times where magnet passed through
 * @note   it will not produce any output until the buffer is full. It will output -1.0 if not possible to estimate RPM
 * @retval Rotation per minute estimation
 */
double getCurrentRPMEstimate()
{
  if (speed_readings.size() < buffer_size)
  {
    return -1.0;
  }
  int time_diff_sum = 0;
  int max_diff = 0;
  for (int i = 0; i < speed_readings.size(); i++)
  {
    time_diff_sum += speed_readings[i];
    if (speed_readings[i] > max_diff)
    {
      max_diff = speed_readings[i];
    }
  }
  double time_diff_avg = double(time_diff_sum - max_diff) / (speed_readings.size() - 1);
  double rpm = double(minute_to_milisecond) / double(time_diff_avg);
  return rpm;
}

/**
 * @brief  calculates speed given a circular buffer of times where magnet passed through
 * @note   It will output -1.0 if not possible to estimate speed
 * @retval current speed estimation
 */
float getSpeed()
{
  double rpm = getCurrentRPMEstimate();
  if (rpm == -1.0)
  {
    return -1.0;
  }
  double rotation_per_second = rpm / 60;
  double rad_per_second = rotation_per_second * 2 * 3.14;
  double speed = rad_per_second * (WHEEL_DIAMETER / 2);
  return (float)speed; // meter per second
}