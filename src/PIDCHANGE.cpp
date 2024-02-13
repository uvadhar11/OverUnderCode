#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>

using namespace vex;
using namespace std;

// THIS FILE IS AN ATTEMPT TO MAKE THE CODEBASE ACTUALLY GOOD

// CONSTRUCTORS FOR PID CLASS
// Note: The stuff past the ":" is the initializer list. It's used to initialize variables in the class without having to do it in the constructor body with this->variable = variable. It sets the instance variables to the parameters passed in the constructor.
// for fully custom movement
PID::PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout, float multiplier) : error(error), kp(kp), ki(ki), kd(kd), starti(starti), settle_error(settle_error), settle_time(settle_time), timeout(timeout), multiplier(multiplier){};

// for movements without custom tuning constants
PID::PID(float error, float starti, float settle_error, float settle_time, float timeout, float multiplier) : error(error), starti(starti), settle_error(settle_error), settle_time(settle_time), timeout(timeout), multiplier(multiplier){};

// for less custom movements
PID::PID(float error, float settle_time, float timeout, float multiplier) : error(error), settle_time(settle_time), timeout(timeout), multiplier(multiplier){};

// for movements with base presets
PID::PID(float error, float multiplier) : error(error), multiplier(multiplier){};

// METHODS FOR PID CLASS
float PID::compute_PID_output(float error, float multiplier)
{
    // methods
}