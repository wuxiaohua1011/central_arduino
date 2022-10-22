#include <pin.h>

void updateLimiterStates(VehicleState *state)
{
    state->isSteeringLeftLimiterOn = isLimiterOn(STEERING_LEFT_LIMITER);
    state->isSteeringLeftLimiterOn = isLimiterOn(STEERING_RIGHT_LIMITER);
}

bool isLimiterOn(int pin)
{
    if (digitalRead(pin) == HIGH)
    {
        return true;
    }
    return false;
}