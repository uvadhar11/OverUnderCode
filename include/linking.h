// WILL INCLUDE THE SIGNATURES FOR FUNCTIONS AND STUFF
#pragma once

// AUTONOMOUS SELECTION FUNCTIONS
void initalizeAutonSelector();
void initalizeAllianceColorSelector();
void autonScreenSelector();

// AUTONOMOUS FUNCTIONS
void auton1();
void auton2();
void auton3();
void auton4();

// DRIVE PID FUNCTIONS
void drivePID(int desiredValue, double multiplier);
void drivePID(int desiredValue, double multiplier, bool intakeWhile);
void turnPID(int desiredValue, double multiplier);
void goodPID(int desiredValue, double multiplier);
// void goodTurnPID(int desiredValue, double multiplier);
void goodTurnPID(int desiredValue, double multiplier, int param_settleTime, int param_timeout);

// PID CLASS FUNCTIONS
// the point of having this in a class allows us to make a PID object for each movement. PID class is used for computations and checking settled ONLY.
// drive class is used for the actual movement of the robot.
class PID
{
public:
    // instance variables
    float error = 0;              // error for pid
    float kp = 0;                 // proportional tuning constant
    float ki = 0;                 // integral tuning constant
    float kd = 0;                 // derivative tuning constant
    float starti = 0;             // range from target to start accumulating integral (it will start accumulating when error is less than this value)
    float settle_error = 0;       // range from target to consider the robot settled
    float settle_time = 0;        // time to stay in the settled error range to consider the robot settled (ms)
    float timeout = 0;            // maximum time to run the pid loop (ms)
    float accumulated_error = 0;  // same thing as total error, error accumulated throughout and is used for integral windup
    float previous_error = 0;     // previous error for derivative calculation
    float output = 0;             // calculated output/power from the pid loop
    float time_spent_settled = 0; // tracks time spent in settled error range (For settle_time)
    float time_spent_running = 0; // tracks time spent running the pid loop (For timeout)
    float multiplier = 1;         // multiplier for the output

    // CONSTRUCTORS
    // for fully custom movement
    PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout, float multiplier);

    // for movements without custom tuning constants
    PID(float error, float starti, float settle_error, float settle_time, float timeout, float multiplier);

    // for less cusmovements
    PID(float error, float settle_time, float timeout, float multiplier);

    // for movements with base presets
    PID(float error, float multiplier);

    // METHODS
    // computes the output of the pid loop
    float compute_PID_output(float error, float multiplier);

    // checks if pid loop has settled
    bool is_PID_settled();
};

// DRIVE CLASS
class Drive
{
private:
    float wheel_diameter; // diameter of the wheel
public:
    // INSTANCE VARIABLES
    float desired_heading; // Desired heading carries over the angle from one movement to another. That way, if the robot doesn't finish a turn movement, it will still drive at the angle that was specified in the turn movement.
};

// HELPER FUNCTIONS

// reducing angle to -180 to 180
float reduce_negative_180_to_180(float angle);

// moving the angle into the range of 0-360 degrees
float reduce_0_to_360(float angle);

// getting the absolute heading for the inertial
// the 1 at the end is for the gyro scale.
float get_absolute_heading()
{
    return (reduce_0_to_360(Inertial.rotation() * 360.0 / 1));
}