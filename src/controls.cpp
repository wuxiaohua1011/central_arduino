#include <controls.h>
#include <CircularBuffer.h>

CircularBuffer<float, 3> spd_buffer;

float run_speed_PID(float curr_spd, float target_spd, float ke, float kd, float ki)
{
    // calculate error
    float e = target_spd - curr_spd;
    spd_buffer.push(e);

    // calculate ie 
    float ie = 0;
    for (size_t i = 0; i < spd_buffer.size(); i++)
    {
        ie += spd_buffer[i];
    }

    // calculate de 
    float de = ie / spd_buffer.size();

    float output = ke * e + kd *de + ki * ie;
    return output;
}




float run_steering_PID(float curr_angle, float target_angle, float ke, float kd, float ki)
{
    // TODO: @James cheney
    return 0;
}