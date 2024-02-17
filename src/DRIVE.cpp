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
float Drive::get_left_position_in()
{
    return ((RightFrontMotor.position(deg) + RightMiddleMotor.position(deg) + RightBackMotor.position(deg)) * drive_in_to_deg_ratio);
}

// drive with voltage
void drive_with_voltage(float left_voltage, float right_voltage)
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
void stop_left_drive(vex::brakeType brakeType)
{
    LeftFrontMotor.stop(brakeType);
    LeftMiddleMotor.stop(brakeType);
    LeftBackMotor.stop(brakeType);
}

// stop right drive motors - accepts coast, brake, or hold
// ex. stop_right_drive(vex::brakeType::hold)
void stop_right_drive(vex::brakeType brakeType)
{
    RightFrontMotor.stop(brakeType);
    RightMiddleMotor.stop(brakeType);
    RightBackMotor.stop(brakeType);
}

// turn to angle method with PID
void Drive::turn_to_angle(float desired_angle, float max_voltage, float settle_time, float timeout)
{
    // set the desired angle.
    // Desired heading carries over the angle from one movement to another. That way, if the robot doesn't finish a turn movement, it will still drive at the angle that was specified in the turn movement. THIS IS AN INSTANCE VARIABLE IN DRIVE CLASS.
    desired_heading = desired_angle;

    // create a PID instance for this turn movement
    PID turnPID(reduce_negative_180_to_180(desired_angle - get_absolute_heading()), settle_time, timeout);

    // create the pid while loop with is settled as the condition
    while (turnPID.is_PID_settled() == false)
    {
        // calculate the error
        float error = reduce_negative_180_to_180(desired_angle - get_absolute_heading());

        // calculate the power output
        float output = turnPID.compute_PID_output(error);

        // clamp the output to the max power (volts)
        output = clamp(output, max_voltage, -max_voltage);

        // set the voltage of the motors
        drive_with_voltage(output, -output);
        task::sleep(10);
    }
    // stop the motors
    stop_left_drive(vex::brakeType::hold);
    stop_right_drive(vex::brakeType::hold);
}

// drive distance
void Drive::drive_distance(float distance, float heading, float max_voltage, float settle_time, float timeout)
{
    // set desired heading to the heading we want to be at for the movement
    desired_heading = heading;

    // make drive pid instance
    PID drivePID(distance, settle_time, timeout);

    // make heading pid instance
    PID headingPID(heading, settle_time, timeout);

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
        drive_output = clamp(drive_output, max_voltage, -max_voltage);

        // clamp the heading output to the max power (volts)
        heading_output = clamp(heading_output, max_voltage, -max_voltage);

        // DRIVE MOTORS
        drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
        task::sleep(10);
    }
    // stop motors
    stop_left_drive(vex::brakeType::hold);
    stop_right_drive(vex::brakeType::hold);
}