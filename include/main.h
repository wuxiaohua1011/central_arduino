#include <Arduino.h>
#include <Servo.h>
#include <led.h>
#include "radiolink.h"
#include <spark_max.h>
#include <pwm_voltage_converter.h>
#include <speed_estimation.h>
#include <SerialCommunications.h>

bool readInProgress = false;
bool newDataFromPC = false;

VehicleState *vehicleState = new VehicleState();
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

void actuate(Actuation *act);

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

bool determine_auto()
{
    if (button_pulse_time > 1600)
    {
        return true;
    }
    else
    {
        return false;
    }
}
