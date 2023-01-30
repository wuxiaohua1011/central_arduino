// Copyright 2023 michael. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "base_module.h"
enum class LEDMode
{
    Blink,
    ON,
    OFF
};

/**
 * @class LEDModule
 * @brief A class that represents the LED module.
 *
 * This class inherits from BaseModule and provides functionality for controlling
 * an LED connected to an Arduino board.
 *
 * @author [Your Name]
 * @date [Today's Date]
 */
class LEDModule : public BaseModule
{
public:
    /**
     * @brief Constructor for the LEDModule class
     *
     * This constructor takes in the pin number for the LED and the blink
     * interval, and initializes the `pin` and `blink_interval` member variables.
     *
     * @param pin Pin number for the LED.
     * @param blink_interval Interval between blinks in milliseconds.
     */
    LEDModule(int pin, uint32_t blink_interval);

    /**
     * @brief Sets up the LED
     *
     * This function sets up the LED by initializing any required hardware
     * and software components.
     *
     * @return A Status indicating success or failure.
     */
    Status setup();

    /**
     * @brief Continuously controls the LED
     *
     * This function continuously reads the current mode and updates the LED
     * accordingly.
     *
     * @return A Status indicating success or failure.
     */
    Status loop();

    /**
     * @brief Cleans up after the LED
     *
     * This function cleans up any resources used by the LED.
     *
     * @return A Status indicating success or failure.
     */
    Status cleanup();

    /**
     * @brief Sets the mode of the LED
     *
     * This function sets the mode of the LED to the desired mode.
     *
     * @param desiredMode The desired mode of the LED.
     *
     * @return A Status indicating success or failure.
     */
    Status setMode(LEDMode desiredMode);

private:
    /**
     * @brief Blinks the LED
     *
     * This function alternates the state of the LED every `blink_interval`
     * milliseconds.
     */
    void blink();
    /**
     * @brief Turns on the LED
     *
     * This function turns on the LED.
     */
    void turnOn();
    /**
     * @brief Turns off the LED
     *
     * This function turns off the LED.
     */
    void turnOff();

    /**
     * @brief A flag that keeps track of the state of the built-in LED before
     * it was modified by the LEDModule.
     */
    bool led_builtin_was_on;

    /**
     * @brief The pin number for the LED.
     */
    int pin;

    /**
     * @brief The interval between blinks in milliseconds.
     */
    uint32_t blink_interval;

    /**
     * @brief The time of the last blink in milliseconds.
     */
    uint32_t last_blink_time;

    /**
     * @brief The current mode of the LED.
     */
    LEDMode mode;
};
