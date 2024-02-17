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
// void goodPID(int desiredValue, double multiplier);
void goodPID(int desiredValue, double multiplier, int param_settleTime, int param_timeout);
// void goodTurnPID(int desiredValue, double multiplier);
void goodTurnPID(int desiredValue, double multiplier, int param_settleTime, int param_timeout);

// PID CLASS FUNCTIONS
// the point of having this in a class allows us to make a PID object for each movement. PID class is used for computations and checking settled ONLY - SO for turning and driving default tuning values and other variables, we need to put that in drive when we go and call the pid.
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
    // float multiplier = 1;         // multiplier for the output

    // CONSTRUCTORS
    // for fully custom movement
    PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

    // for movements without custom tuning constants
    // PID(float error, float starti, float settle_error, float settle_time, float timeout);

    // for less cusmovements
    // PID(float error, float settle_time, float timeout);

    // for movements with only heading pid
    PID(float error, float kp, float ki, float kd, float starti);

    // METHODS
    // computes the output of the pid loop
    float compute_PID_output(float error);

    // checks if pid loop has settled
    bool is_PID_settled();
};

// DRIVE CLASS
class Drive
{
private:
    // diameter of the drive wheels
    float wheel_diameter = 3.25;

    // ratio of the drive wheels - input gear / output gear or motor gear/wheel gear. If direct, its 1. Ex. 48/60 = 0.8
    float wheel_ratio = 0.8;

    // ratio to convert degrees to inches
    float drive_in_to_deg_ratio = (wheel_ratio / 360.0 * wheel_diameter * M_PI);

public:
    // INSTANCE VARIABLES
    float desired_heading; // Desired heading carries over the angle from one movement to another. That way, if the robot doesn't finish a turn movement, it will still drive at the angle that was specified in the turn movement.

    // TURNING PID
    float max_turn_voltage = 12;
    float turn_kp = 0.1;
    float turn_ki = 0.0;
    float turn_kd = 0.4;
    float turn_starti = 0.01;
    float turn_settle_error = 0.5; // of an angle
    float turn_settle_time = 200;  // ms
    float turn_timeout = 2000;     // ms

    // DRIVING PID
    float drive_max_voltage = 12;
    float drive_kp = 0.13;
    float drive_ki = 0.0;
    float drive_kd = 0.3;
    float drive_starti = 2.27;       // (inches) or 100 degrees
    float drive_settle_error = 0.11; // (inches) or 5 degrees
    float drive_settle_time = 200;   // ms
    float drive_timeout = 2000;      // ms

    // HEADING PID (for drive correction)
    // NOTE: we only want the heading pid to end when the drive pid ends, so we don't need timeout, settle time, and settle error for heading pid.
    float heading_max_voltage = 6;
    float heading_kp = 0.13;
    float heading_ki = 0.0;
    float heading_kd = 0.3;
    float heading_starti = 2.27;

    // DRIVE CONSTRUCTOR - blank for now until I have time to refactor everything - devices and stuff should go in here instead of setting defaults, etc.
    Drive();

    // get left position of drive in inches
    float get_left_position_in();

    // get right position of drive in inches
    float get_right_position_in();

    // drive with voltage
    void drive_with_voltage(float left_voltage, float right_voltage);

    // stop left drive motors
    void stop_left_drive(vex::brakeType brakeType);

    // stop right drive motors
    void stop_right_drive(vex::brakeType brakeType);

    // DRIVING DISTANCE
    void drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_time, float drive_timeout);

    // fully custom drive distance
    void drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_time, float drive_settle_error, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);

    // TURN TO ANGLE

    // less custom turn to angle method with PID
    void turn_to_angle(float desired_angle, float turn_max_voltage, float turn_settle_time, float turn_timeout);

    // fully custom turn to angle method with PID
    void turn_to_angle(float desired_angle, float turn_max_voltage, float turn_settle_time, float turn_settle_error, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);
};

// HELPER FUNCTIONS

// reducing angle to -180 to 180
float reduce_negative_180_to_180(float angle);

// moving the angle into the range of 0-360 degrees
float reduce_0_to_360(float angle);

// getting the absolute heading for the inertial
// the 1 at the end is for the gyro scale.
float get_absolute_heading();

// clamping values
float clamp(float value, float min, float max);