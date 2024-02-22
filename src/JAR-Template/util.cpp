#include "vex.h"
#include "globals.h"

// There is probably a more efficient way to reduce angles than the ones specified below,
// but these work without question, and you really only have to reduce them once or twice at
// a max.

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

// moving the angle into the range of -180 to 180 degrees
// need to do this stuff cuz its crucial for angle wrapping for inertial
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

// moving the angle into the range of -90 to 90 degrees
float reduce_negative_90_to_90(float angle)
{
  while (!(angle >= -90 && angle < 90))
  {
    if (angle < -90)
    {
      angle += 180;
    }
    if (angle >= 90)
    {
      angle -= 180;
    }
  }
  return (angle);
}

// converting from degrees to radians
float to_rad(float angle_deg)
{
  return (angle_deg / (180.0 / M_PI));
}

// converting from radians to degrees
float to_deg(float angle_rad)
{
  return (angle_rad * (180.0 / M_PI));
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

// identifies whether a motor is reversed or not based on sign of the port number
bool is_reversed(double input)
{
  if (input < 0)
    return (true);
  return (false);
}

// converting percentage to volts
float to_volt(float percent)
{
  return (percent * 12.0 / 100.0); // makes sense more to me: percent / 100.0 * 12.0 -> gets the fraction then scale that up (using unit fraction) based in 12 as 100
}

// for some template stuff
int to_port(int port)
{
  if (port > 8)
  {
    return (0);
  }
  return (port - 1);
} // To_port just keeps a number over 7 from being passed as a threewire port.

// deadband looks like a deadzone of argument width and input is the input taken in from the controller
float deadband(float input, float width)
{
  // if the input percentage (absolute value to account for negatives) is inside the width of the deadzone, then return 0 (no affect)
  if (fabs(input) < width)
  {
    return (0);
  }
  // if not in this width then just return the input to be used
  return (input);
}

// DRIVER CONTROL FUNCTIONS
void actuateLeftWing()
{
  if (leftWingEnabled == false)
  {
    LeftWing.off();
    leftWingEnabled = true;
    // wait(0.1, sec);
  }
  else
  {
    LeftWing.on();
    leftWingEnabled = false;
    // wait(0.1, sec);
  }
}

void actuateRightWing()
{
  if (rightWingEnabled == false)
  {
    RightWing.off();
    rightWingEnabled = true;
    // wait(0.1, sec);
  }
  else
  {
    RightWing.on();
    rightWingEnabled = false;
    // wait(0.1, sec);
  }
}

void actuateBothWings()
{
  if (bothWingsEnabled == false)
  {
    RightWing.off();
    LeftWing.off();
    bothWingsEnabled = true;
  }
  else
  {
    RightWing.on();
    LeftWing.on();
    bothWingsEnabled = false;
  }
}