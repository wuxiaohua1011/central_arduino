#include <pin.h>

bool isLimiterOn(int pin)
{
    if (digitalRead(pin) == HIGH)
    {
        // nothing is pressing against limiter
        return false;
    }
    return true;
}

void updateLimiterStates(VehicleState *state)
{
    state->isSteeringLeftLimiterOn = isLimiterOn(STEERING_LEFT_LIMITER);
    state->isSteeringRightLimiterOn = isLimiterOn(STEERING_RIGHT_LIMITER);
}

void setupSteeringLimiters()
{
    pinMode(STEERING_LEFT_LIMITER, INPUT_PULLUP);
    pinMode(STEERING_RIGHT_LIMITER, INPUT_PULLUP);
}
