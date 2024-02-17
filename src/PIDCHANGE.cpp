#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>

using namespace vex;
using namespace std;

// THIS FILE IS AN ATTEMPT TO MAKE THE CODEBASE ACTUALLY GOOD

// CONSTRUCTORS FOR PID CLASS
// Note: The stuff past the ":" is the initializer list. It's used to initialize variables in the class without having to do it in the constructor body with this->variable = variable. It sets the instance variables to the parameters passed in the constructor.
// used to have multiplier, but we can just cap the voltage so there's no need for it
// for fully custom movement
PID::PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout) : error(error), kp(kp), ki(ki), kd(kd), starti(starti), settle_error(settle_error), settle_time(settle_time), timeout(timeout){};

// // for movements without custom tuning constants
// PID::PID(float error, float starti, float settle_error, float settle_time, float timeout) : error(error), starti(starti), settle_error(settle_error), settle_time(settle_time), timeout(timeout){};

// // for base custom movements
// PID::PID(float error, float settle_time, float timeout) : error(error), settle_time(settle_time), timeout(timeout){};

// for heading pid movements
PID::PID(float error, float kp, float ki, float kd, float starti) : error(error), kp(kp), ki(ki), kd(kd), starti(starti){};

// METHODS FOR PID CLASS
float PID::compute_PID_output(float error)
{
    // methods
    // if the absolute value of the error is less than the starti (the error that we want to start accumulating the integral term), then add the error to the accumulated error
    // the use of start i helps to prevent integral windup
    // so ONLY when we are in the range (close to the target) do we start accumulating the integral term, and if we are far, then integral term doesn't have any effect
    if (fabs(error) < starti)
    {
        accumulated_error += error;
    }

    // if the error has crossed 0, then reset the accumulated error to 0
    // we do this because if we are moving towards the target, and we overshoot it, then we want to reset the integral term so that it doesn't keep accumulating and make us overshoot the target again. Integral is used to speed up the movement when close so we don't want it to take effect when we overshoot.
    // here we are checking whether it has crossed 0 by checking if the error and previous error have different signs - we aren't using abs value so we need to account for if error was negative and previous error was positive, or vice versa to check whether it crossed 0.
    if ((error > 0 && previous_error < 0) || (error < 0 && previous_error > 0))
    {
        accumulated_error = 0;
    }

    // calculate pid output
    output = (kp * error + ki * accumulated_error + kd * (error - previous_error));

    // set previous error equal to the error of the most previous iteration (current error)
    previous_error = error;

    // if we are in the range considered acceptable to stop the movement, then increment the time spent settled by 10ms (the delay we have for each iteration)
    if (fabs(error) < settle_error)
    {
        time_spent_settled += 10;
    }
    // if we are not in this range where it is acceptable to stop the movement, then set the time spent settled to 0 (keep it there, or reset it if something happened and we went back)
    else
    {
        time_spent_settled = 0;
    }

    // increment time spent running by 10ms (the delay we have for each iteration), used for timeout
    time_spent_running += 10;

    // return the power to give the motors because this function is for COMPUTATION.
    return output;
}

// settled is a function that is called to check whether to stop the movement (settling = when to stop the movement)
bool PID::is_PID_settled()
{
    // if the time spent running is greater than the timeout (max time for the move), then its settled (end the move)
    // need to add the timeout != 0 check because if we don't want a timeout for the movement, then we set it to 0, resulting in this condition to always be true, and movement doesn't run
    // SO in the case that we set the timeout to 0, we still want it to run, which is why we want this check
    if (time_spent_running > timeout && timeout != 0)
    {
        return (true);
    }
    // if the time spent settled (the time spent inside the error range that considered acceptable to stop the movement in) is greater than the amount of time we have set to spend in this settled position (prolly used to give ample time for bot to come to complete stop), then return that its settled (stop the movement)
    if (time_spent_settled > settle_time)
    {
        return (true);
    }
    // if none of the above conditions are true, return false to keep running the movement.
    return (false);
}