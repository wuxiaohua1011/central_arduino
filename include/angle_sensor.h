/**
 * @class SteeringAngleSensor
 * @brief A class that represents the Steering Angle Sensor.
 *
 * This class inherits from BaseModule and provides functionality for reading
 * the steering angle and angular velocity from the sensor.
 *
 * @author Michael Wu
 * @date 1/29/2023
 */

#include "pin.h"
#include "base_module.h"
#include <CircularBuffer.h>

const uint32_t STEERING_ANGLE_BUFFER_LEN = 5;

struct SteeringReading
{
    float reading;
    uint32_t timestamp;
};

class SteeringAngleSensor : public BaseModule
{
public:
    /**
     * @brief Constructor for the SteeringAngleSensor class
     *
     * This constructor takes in the pin number for the sensor and initializes
     * the `pin` member variable.
     *
     * @param pin Pin number for the sensor.
     */
    SteeringAngleSensor(int pin);

    /**
     * @brief Sets up the sensor
     *
     * This function sets up the sensor by initializing any required hardware
     * and software components.
     *
     * @return A Status indicating success or failure.
     */
    Status setup();

    /**
     * @brief Continuously reads data from the sensor
     *
     * This function continuously reads data from the sensor and updates the
     * `currentAngle` member variable.
     *
     * @return A Status indicating success or failure.
     */
    Status loop();

    /**
     * @brief Cleans up after the sensor
     *
     * This function cleans up any resources used by the sensor.
     *
     * @return A Status indicating success or failure.
     */
    Status cleanup();

    /**
     * @brief Gets the current steering angle
     *
     * This function returns the current steering angle read from the sensor.
     *
     * @return The current steering angle.
     */
    float getSteeringAngle();

    /**
     * @brief Gets the current angular velocity
     *
     * This function returns the current angular velocity calculated from the
     * sensor data.
     *
     * @return The current angular velocity.
     */
    float getAngularVelocity();

private:
    /**
     * @brief The current steering angle
     */
    float currentAngle;

    float currentAngularVelocity;
    /**
     * @brief Pin number for the sensor
     */
    int pin;

    /**
     * @brief The left angle limit
     */
    const float LEFT_ANGLE = -30.0;

    /**
     * @brief The right angle limit
     */
    const float RIGHT_ANGLE = 30.0;
    /**
     * @brief add new reading to the buffer
    */
    void addReading(float reading);

    /**
     * @brief calculates the angular velocity
     * @note if there is < STEERING_ANGLE_BUFFER_LEN data in the buffer, this function will return 0
     * 
     */
    float calcVelocity();
    CircularBuffer<float, STEERING_ANGLE_BUFFER_LEN> reading_buffer;
    CircularBuffer<uint32_t, STEERING_ANGLE_BUFFER_LEN> timestamp_buffer;
};