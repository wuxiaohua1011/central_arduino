#include <Arduino.h>
#include <Servo.h>
#include <led.h>
#include "radiolink.h"
#include <spark_max.h>
#include <pwm_voltage_converter.h>
#include <speed_estimation.h>

/**
 * @brief  main setup function
 * @note   
 * @retval None
 */
void setup();

/**
 * @brief  main loop
 * @note   
 * @retval None
 */
void loop();

/**
 * @brief  send steering actuation
 * @note   
 * @retval None
 */
void actuateSteering();

/**
 * @brief  send brake actuation
 * @note   
 * @retval None
 */
void actuateBrake();

/**
 * @brief  send throttle actuation
 * @note   
 * @retval None
 */
void actuateThrottle();

/**
 * @brief  wrapper function for a series of actions on manual mode
 * @note   
 * @retval None
 */
void onManualDrive();

/**
 * @brief  wrapper function for a series of actions on auto mode
 * @note   
 * @retval None
 */
void onAutoDrive();