#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>

using namespace vex;
using namespace std;

// THIS FILE IS FOR HELPER FUNCTIONS USED THROUGHOUT THE CODEBASE

// Moving the angle into the range of -180 to 180 degrees. Need to do this stuff cuz its crucial for angle wrapping for inertial. Helps pick the shortest path to the target.
float reduce_negative_180_to_180(float angle)
{
    while (!(angle >= -180 && angle < 180))
    {
        if (angle < -180)
        {
            angle += 360;
        }
        if (angle >= 180)
        {
            angle -= 360;
        }
    }
    return (angle);
}

// moving the angle into the range of 0-360 degrees
float reduce_0_to_360(float angle)
{
    while (!(angle >= 0 && angle < 360))
    {
        if (angle < 0)
        {
            angle += 360;
        }
        if (angle >= 360)
        {
            angle -= 360;
        }
    }
    return (angle);
}

// getting the absolute heading for the inertial
// the 1 at the end is for the gyro scale.
float get_absolute_heading()
{
    return (reduce_0_to_360(Inertial.rotation() * 360.0 / 1));
}

// clamp is just clamping the value inside a certain range
float clamp(float input, float min, float max)
{
    if (input > max)
    {
        return (max);
    }
    if (input < min)
    {
        return (min);
    }
    return (input);
}