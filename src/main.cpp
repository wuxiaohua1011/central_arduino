/**
 * By Michael Wu on July 9, 2022.
 * reference from https://www.camelsoftware.com/2015/12/25/reading-pwm-signals-from-an-rc-receiver-with-arduino/
 *
 * Please wire up your PWM Inputs on Digital Pins and revise the *_SOURCE fields to the corresponding pin numbers.
 * only arduino ble nano 33 and arduino due are tested
 *
 **/
#include <main.h>

void setup()
{
  Serial.begin(9600);
  // setupPwmVoltageConverter();
  // setupLED();
  // setupSparkMax();
  // setupRadioLink();

  pinMode(8, OUTPUT);
}

void loop()
{
  // update state
  loopSpeedEstimation();
  vehicleState->speed = getSpeed();

  // actuation
  onAutoDrive();

  // if (button_pulse_time > 1600)
  // {
  //   onAutoDrive();
  // }
  // else
  // {
  //   onManualDrive();
  // }
  // vehicleState->act->throttle = 1700;
  actuate(vehicleState->act);
}

void onAutoDrive()
{
  // turn steering, throttle, and brake to neutral in case auto mode failed.
  digitalWrite(LED_BUILTIN, HIGH);
  processSerialCommunication(vehicleState, true);
}

void onManualDrive()
{

  digitalWrite(LED_BUILTIN, LOW);
  processSerialCommunication(vehicleState, false);

  // if button is not pressed, serial input is ignored, use controller input
  vehicleState->act->throttle = throttle_pulse_time;
  vehicleState->act->steering = steering_pulse_time;
  vehicleState->act->brake = brake_pulse_time;
}

void actuate(Actuation *act)
{
  writeToSteering(act->steering);
  writeToBrake(act->brake);
  writeToThrottle(act->throttle);
}
