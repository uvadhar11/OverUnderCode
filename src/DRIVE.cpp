#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>

using namespace vex;
using namespace std;

// FOR DRIVETRAIN MOVEMENTS

// calculate left position of the drive (in inches)
float Drive::get_left_position_in()
{
    return ((LeftFrontMotor.position(deg) + LeftMiddleMotor.position(deg) + LeftBackMotor.position(deg)) * drive_in_to_deg_ratio);
}

// calculate right position of the drive (in inches)
float Drive::get_right_position_in()
{
    return ((RightFrontMotor.position(deg) + RightMiddleMotor.position(deg) + RightBackMotor.position(deg)) * drive_in_to_deg_ratio);
}

// drive with voltage
void Drive::drive_with_voltage(float left_voltage, float right_voltage)
{
    // set the voltage of the left motors
    LeftFrontMotor.spin(fwd, left_voltage, volt);
    LeftMiddleMotor.spin(fwd, left_voltage, volt);
    LeftBackMotor.spin(fwd, left_voltage, volt);

    // set the voltage of the right motors
    RightFrontMotor.spin(fwd, right_voltage, volt);
    RightMiddleMotor.spin(fwd, right_voltage, volt);
    RightBackMotor.spin(fwd, right_voltage, volt);
}

// stop left drive motors - accepts coast, brake, or hold
// ex: stop_left_drive(vex::brakeType::hold)
void Drive::stop_left_drive(vex::brakeType brakeType)
{
    LeftFrontMotor.stop(brakeType);
    LeftMiddleMotor.stop(brakeType);
    LeftBackMotor.stop(brakeType);
}

// stop right drive motors - accepts coast, brake, or hold
// ex. stop_right_drive(vex::brakeType::hold)
void Drive::stop_right_drive(vex::brakeType brakeType)
{
    RightFrontMotor.stop(brakeType);
    RightMiddleMotor.stop(brakeType);
    RightBackMotor.stop(brakeType);
}

// less custom turn to angle method with PID
void Drive::turn_to_angle(float desired_angle, float turn_max_voltage, float turn_settle_time, float turn_timeout)
{
    // call the fully custom turn to angle method
    turn_to_angle(desired_angle, turn_max_voltage, turn_settle_time, this->turn_settle_error, turn_timeout, this->turn_kp, this->turn_ki, this->turn_kd, this->turn_starti);
}

// fully custom turn to angle method with PID
void Drive::turn_to_angle(float desired_angle, float turn_max_voltage, float turn_settle_time, float turn_settle_error, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti)
{
    // set the desired angle.
    // Desired heading carries over the angle from one movement to another. That way, if the robot doesn't finish a turn movement, it will still drive at the angle that was specified in the turn movement. THIS IS AN INSTANCE VARIABLE IN DRIVE CLASS.
    desired_heading = desired_angle;

    // create a PID instance for this turn movement
    PID turnPID(reduce_negative_180_to_180(desired_angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);

    // create the pid while loop with is settled as the condition
    while (turnPID.is_PID_settled() == false)
    {
        // calculate the error
        float error = reduce_negative_180_to_180(desired_angle - get_absolute_heading());

        // calculate the power output
        float output = turnPID.compute_PID_output(error);

        // clamp the output to the max power (volts)
        output = clamp(output, turn_max_voltage, -turn_max_voltage);

        // set the voltage of the motors
        drive_with_voltage(output, -output);
        task::sleep(10);
    }
    // stop the motors
    stop_left_drive(vex::brakeType::hold);
    stop_right_drive(vex::brakeType::hold);
}

// less custom drive distance
void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_time, float drive_timeout)
{
    // call the fully custom drive distance method
    drive_distance(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_time, this->drive_settle_error, drive_timeout, this->drive_kp, this->drive_ki, this->drive_kd, this->drive_starti, this->heading_kp, this->heading_ki, this->heading_kd, this->heading_starti);
};

// fully custom drive distance
void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_time, float drive_settle_error, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti)
{
    // set desired heading to the heading we want to be at for the movement
    desired_heading = heading;

    // make drive pid instance
    PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);

    // make heading pid instance - we are ending this movement based on the drive pid settling, so we don't need a timeout, settle time, or settle error for the heading pid
    PID headingPID(heading, heading_kp, heading_ki, heading_kd, heading_starti);

    // store the start average position of the robot instead of resetting the drive function to 0 each time we write the function and then we determine the error relative to that value.
    float start_average_position = (get_left_position_in() + get_right_position_in()) / 2.0;

    // set current average position to the starting position because we are just starting the loop
    float average_position = start_average_position;

    // pid loop - runs when drive pid is not settled
    while (drivePID.is_PID_settled() == false)
    {
        // update average position
        average_position = (get_left_position_in() + get_right_position_in()) / 2.0;

        // calculate drive error
        float drive_error = distance + start_average_position - average_position; // distance + start_average_position gets the desired value and then we subtract the current position from that. Need to do this because we aren't resetting the motor positions to 0.

        // calculate heading error - finds the shortest path to the desired heading
        float heading_error = reduce_negative_180_to_180(heading - get_absolute_heading());

        // CALCULATING POWER OUTPUT
        // calculate drive power output
        float drive_output = drivePID.compute_PID_output(drive_error);

        // calculate the heading power output
        float heading_output = headingPID.compute_PID_output(heading_error);

        // CLAMPING OUTPUT
        // clamp the drive output to the max power (volts)
        drive_output = clamp(drive_output, drive_max_voltage, -drive_max_voltage);

        // clamp the heading output to the max power (volts)
        heading_output = clamp(heading_output, heading_max_voltage, -heading_max_voltage);

        // DRIVE MOTORS
        drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
        task::sleep(10);
    }
    // stop motors
    stop_left_drive(vex::brakeType::hold);
    stop_right_drive(vex::brakeType::hold);
}