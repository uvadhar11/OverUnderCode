#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>

using namespace vex;
using namespace std;

// VARIABLES
int selfCorrect = 3;

// drive PID - 2 parameters
void drivePID(int desiredValue, double multiplier)
{
    // Settings - variables initializations
    double kP = 0.115;       // 0.11
    double kI = 0.000000001; // 0.000000000001     2
    double kD = 0.0312;      // 0.009 -> clean 0.02

    // Autonomous Settings
    int error = 0;
    int prevError = 0;
    int derivative;
    int totalError = 0;

    // Reset the motor encoder positions
    LeftFrontMotor.setPosition(0, degrees);
    LeftMiddleMotor.setPosition(0, degrees);
    LeftBackMotor.setPosition(0, degrees);
    RightFrontMotor.setPosition(0, degrees);
    RightMiddleMotor.setPosition(0, degrees);
    RightBackMotor.setPosition(0, degrees);
    double targetGyroPosition = Inertial.yaw(rotationUnits::deg); // get value for self-correction

    Brain.Screen.clearScreen();

    while (true)
    {
        // Get the position of the motors
        int leftFrontMotorPosition = LeftFrontMotor.position(degrees);
        int leftMiddleMotorPosition = LeftMiddleMotor.position(degrees);
        int leftBackMotorPosition = LeftBackMotor.position(degrees);
        int rightFrontMotorPosition = RightFrontMotor.position(degrees);
        int rightMiddleMotorPosition = RightMiddleMotor.position(degrees);
        int rightBackMotorPosition = RightBackMotor.position(degrees);

        // self-correction variables
        double leftValue;
        double rightValue;

        leftValue = 0.0;
        rightValue = 0.0;

        // printing values to brain

        // for self-correction stuff
        int GyroPosition = Inertial.yaw(rotationUnits::deg) - targetGyroPosition;

        if (Inertial.yaw(rotationUnits::deg) < targetGyroPosition)
        {

            rightValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;
        }
        else
        {

            rightValue = 0;
        }

        if (Inertial.yaw(rotationUnits::deg) > targetGyroPosition)
        {

            leftValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;
        }
        else
        {

            leftValue = 0;
        }

        // Lateral Movement PID/Going forward and back

        // Get the average of the motors
        int averagePosition = ((leftFrontMotorPosition + leftBackMotorPosition + leftMiddleMotorPosition + rightFrontMotorPosition + rightMiddleMotorPosition + rightBackMotorPosition) / 6);

        // Potential
        error = desiredValue - averagePosition;

        // Derivative
        derivative = error - prevError;

        // Integral - trying to make sure you don't undershoot. So as time goes on when u don't reach target, it increases speed. Integral wind-up when not reaching target over time so when closer to target it might not slow down all the way, which is the problem
        totalError += error; // this is the integral

        // std::cout <<
        // error
        // << std::endl;

        // printing values
        // error
        Brain.Screen.setCursor(1, 2);
        Brain.Screen.print(error);
        // average positions
        Brain.Screen.setCursor(2, 2);
        Brain.Screen.print(LeftFrontMotor.position(deg));

        Brain.Screen.setCursor(3, 2);
        Brain.Screen.print(LeftMiddleMotor.position(deg));

        Brain.Screen.setCursor(4, 2);
        Brain.Screen.print(LeftBackMotor.position(deg));

        Brain.Screen.setCursor(5, 2);
        Brain.Screen.print(RightFrontMotor.position(deg));

        Brain.Screen.setCursor(6, 2);
        Brain.Screen.print(RightMiddleMotor.position(deg));

        Brain.Screen.setCursor(7, 2);
        Brain.Screen.print(RightBackMotor.position(deg));

        // motor encoder positions
        // std::cout <<
        // leftFrontMotorPosition << " , " <<  leftMiddleMotorPosition << " , "
        // << leftBackMotorPosition << " , " << rightFrontMotorPosition << " , " << rightMiddleMotorPosition << " , " << rightBackMotorPosition
        // << std::endl;

        // error
        std::cout << error << std::endl;

        // other checks like integral
        if (error == 0)
            totalError = 0;

        if (abs(error) <= 15)
        {
            Brain.Screen.print(abs(error));
            break;
        }
        else
        {
            // means the error is greater than stop PID or the value set there.
            totalError = 0; // integral = 0
        }

        // calculate motor power
        double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI)) * multiplier; //* kD and (totalError * kI)

        // move the motors - R was rev
        LeftFrontMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);    //+ turnMotorPower (if turning). L/R for self-correction
        RightFrontMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt);  //- turnMotorPower
        LeftMiddleMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);   //+ turnMotorPower
        RightMiddleMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt); //- turnMotorPower
        LeftBackMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);     //+ turnMotorPower
        RightBackMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt);   //- turnMotorPower

        // Brain.Screen.print(error + ", " + averagePosition);

        prevError = error;
    }

    // stop the wheels after the while loop is done
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
}

void drivePID(int desiredValue, double multiplier, bool intakeWhile)
{
    // Settings - variables initializations
    double kP = 0.115;       // 0.11
    double kI = 0.000000001; // 0.000000000001     2
    double kD = 0.0312;      // 0.009 -> clean 0.02

    // Autonomous Settings
    int error = 0;
    int prevError = 0;
    int derivative;
    int totalError = 0;

    // Reset the motor encoder positions
    LeftFrontMotor.setPosition(0, degrees);
    LeftMiddleMotor.setPosition(0, degrees);
    LeftBackMotor.setPosition(0, degrees);
    RightFrontMotor.setPosition(0, degrees);
    RightMiddleMotor.setPosition(0, degrees);
    RightBackMotor.setPosition(0, degrees);
    double targetGyroPosition = Inertial.yaw(rotationUnits::deg); // get value for self correction

    Brain.Screen.clearScreen();

    while (true)
    {
        // Get the position of the motors
        int leftFrontMotorPosition = LeftFrontMotor.position(degrees);
        int leftMiddleMotorPosition = LeftMiddleMotor.position(degrees);
        int leftBackMotorPosition = LeftBackMotor.position(degrees);
        int rightFrontMotorPosition = RightFrontMotor.position(degrees);
        int rightMiddleMotorPosition = RightMiddleMotor.position(degrees);
        int rightBackMotorPosition = RightBackMotor.position(degrees);

        // self-correction variables
        double leftValue;
        double rightValue;

        leftValue = 0.0;
        rightValue = 0.0;

        // printing values to brain

        // for self-correction stuff
        int GyroPosition = Inertial.yaw(rotationUnits::deg) - targetGyroPosition;

        if (Inertial.yaw(rotationUnits::deg) < targetGyroPosition)
        {

            rightValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;
        }
        else
        {

            rightValue = 0;
        }

        if (Inertial.yaw(rotationUnits::deg) > targetGyroPosition)
        {

            leftValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;
        }
        else
        {

            leftValue = 0;
        }

        // Lateral Movement PID/Going forward and back

        // Get the average of the motors
        int averagePosition = ((leftFrontMotorPosition + leftBackMotorPosition + leftMiddleMotorPosition + rightFrontMotorPosition + rightMiddleMotorPosition + rightBackMotorPosition) / 6);

        // Potential
        error = desiredValue - averagePosition;

        // Derivative
        derivative = error - prevError;

        // Integral - trying to make sure you don't undershoot. So as time goes on when u don't reach target, it increases speed. Integral wind-up when not reaching target over time so when closer to target it might not slow down all the way, which is the problem
        totalError += error; // this is the integral

        // std::cout <<
        // error
        // << std::endl;

        // printing values
        // error
        Brain.Screen.setCursor(1, 2);
        Brain.Screen.print(error);
        // average positions
        Brain.Screen.setCursor(2, 2);
        Brain.Screen.print(LeftFrontMotor.position(deg));

        Brain.Screen.setCursor(3, 2);
        Brain.Screen.print(LeftMiddleMotor.position(deg));

        Brain.Screen.setCursor(4, 2);
        Brain.Screen.print(LeftBackMotor.position(deg));

        Brain.Screen.setCursor(5, 2);
        Brain.Screen.print(RightFrontMotor.position(deg));

        Brain.Screen.setCursor(6, 2);
        Brain.Screen.print(RightMiddleMotor.position(deg));

        Brain.Screen.setCursor(7, 2);
        Brain.Screen.print(RightBackMotor.position(deg));

        // motor encoder positions
        // std::cout <<
        // leftFrontMotorPosition << " , " <<  leftMiddleMotorPosition << " , "
        // << leftBackMotorPosition << " , " << rightFrontMotorPosition << " , " << rightMiddleMotorPosition << " , " << rightBackMotorPosition
        // << std::endl;

        // error
        std::cout << error << std::endl;

        // other checks like integral
        if (error == 0)
            totalError = 0;

        if (abs(error) <= 15)
        {
            Brain.Screen.print(abs(error));
            break;
        }
        else
        {
            // means the error is greater than stop PID or the value set there.
            totalError = 0; // integral = 0
        }

        // calculate motor power
        double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI)) * multiplier; //* kD and (totalError * kI)

        // move the motors - R was rev
        LeftFrontMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);    //+ turnMotorPower (if turning). L/R for self-correction
        RightFrontMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt);  //- turnMotorPower
        LeftMiddleMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);   //+ turnMotorPower
        RightMiddleMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt); //- turnMotorPower
        LeftBackMotor.spin(fwd, lateralMotorPower + leftValue, voltageUnits::volt);     //+ turnMotorPower
        RightBackMotor.spin(fwd, lateralMotorPower + rightValue, voltageUnits::volt);   //- turnMotorPower

        if (intakeWhile)
        {
            IntakeFlywheelMotor.spin(fwd, 12, volt);
        }

        // Brain.Screen.print(error + ", " + averagePosition);

        prevError = error;
    }

    // stop the wheels after the while loop is done
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
}

// TURN PID
// DEFINE VARIABLES

// TURN PID FUNCTION
void turnPID(int desiredValue, double multiplier)
{
    // Settings - variables initializations
    double kP = .5;             // .2
    double kI = 0.000000000000; // last digit was 1
    double kD = 0.3;            // 0.0001

    // Autonomous Settings
    double error = 0;
    double prevError = 0;
    int derivative;
    double totalError = 0;

    int turnTime = 0; // to keep track of the current turn time (ticks I think). To check if > 15000 or not.
    int ticks = 1500; // for faster turn speed. So doesn't break everything else if turn doesn't work.

    // Reset the positions
    LeftFrontMotor.setPosition(0, degrees);
    LeftMiddleMotor.setPosition(0, degrees);
    LeftBackMotor.setPosition(0, degrees);
    RightFrontMotor.setPosition(0, degrees);
    RightMiddleMotor.setPosition(0, degrees);
    RightBackMotor.setPosition(0, degrees);

    while (true)
    {
        // Get the position of the motors (maybe more accuracy could add this in with the gyro reading)

        // int leftFrontMotorPosition = LeftFrontMotor.position(degrees);
        // int leftBackMotorPosition = LeftBackMotor.position(degrees);
        // int rightFrontMotorPosition = RightFrontMotor.position(degrees);
        // int rightMidMotorPosition = RightMidMotor.position(degrees);
        // int rightBackMotorPosition = RightBackMotor.position(degrees);

        // Get the average of the motors (just using the gyro here but maybe we could try using the motor pos + gyro for more accuracy)
        double averagePosition = Inertial.yaw(rotationUnits::deg);

        Brain.Screen.setCursor(2, 2);
        Brain.Screen.print(Inertial.angle());

        // Potential
        error = averagePosition - desiredValue;

        // Derivative
        derivative = error - prevError;

        // Integral - keep out for drivetrain
        totalError += error;

        // other checks like integral
        if (error == 0)
            totalError = 0;

        if (fabs(error) < 0.1)
        {
            Brain.Screen.print(fabs(error));
            break;
        }
        else
        {
            // means the error is greater than stop PID or the value set there.
            totalError = 0; // integral = 0
        }

        // turn time breaking
        if (turnTime > ticks)
        {
            break;
        }

        // printing the error
        Brain.Screen.setCursor(4, 2);
        Brain.Screen.print(error);

        // calculate the actual PID (take out the last part (kI) fo drivetrain cuz it makes small changes that messes it up)
        // If you were to have integral: add "+ totalError * kI" at the end then the semicolon
        double lateralMotorPower = (error * kP) + (derivative * kD) + (totalError * kI); //* kD

        // Spin the motors
        LeftFrontMotor.spin(reverse, lateralMotorPower * multiplier, voltageUnits::volt);  //+ turnMotorPower
        RightFrontMotor.spin(fwd, (lateralMotorPower)*multiplier, voltageUnits::volt);     //- turnMotorPower
        LeftMiddleMotor.spin(reverse, lateralMotorPower * multiplier, voltageUnits::volt); //+ turnMotorPower
        RightMiddleMotor.spin(fwd, (lateralMotorPower)*multiplier, voltageUnits::volt);    //- turnMotorPower
        LeftBackMotor.spin(reverse, lateralMotorPower * multiplier, voltageUnits::volt);   //+ turnMotorPower
        RightBackMotor.spin(fwd, (lateralMotorPower)*multiplier, voltageUnits::volt);      //- turnMotorPower

        // if (abs(error) < 0.1) {

        //   break;
        // }

        turnTime = turnTime + 10; // update current turn time.

        // if (turnTime > ticks) {
        //   break;
        // }

        prevError = error;

        vex::task::sleep(10);
    }

    // stop the wheels after the while loop is done
    LeftFrontMotor.stop(hold);
    RightFrontMotor.stop(hold);
    LeftMiddleMotor.stop(hold);
    RightMiddleMotor.stop(hold);
    LeftBackMotor.stop(hold);
    RightBackMotor.stop(hold);
}

// can also make a turn pid function for doing stuff while the pid is running since this isn't a task.

// JAR TEMPLATE PID IMPLEMENTATION NOTES

// // method to compute the pid output.
// float PID::compute(float error)
// {
//   // if the absolute value of the error is less than the starti (the error that we want to start accumulating the integral term), then add the error to the accumulated error
//   // the use of start i helps to prevent integral windup
//   // so ONLY when we are in the range (close to the target) do we start accumulating the integral term, and if we are far, then integral term doesn't have any effect
//   if (fabs(error) < starti)
//   {
//     accumulated_error += error;
//   }

//   // if the error has crossed 0, then reset the accumulated error to 0
//   // we do this because if we are moving towards the target, and we overshoot it, then we want to reset the integral term so that it doesn't keep accumulating and make us overshoot the target again. Integral is used to speed up the movement when close so we don't want it to take effect when we overshoot.
//   // here we are checking whether it has crossed 0 by checking if the error and previous error have different signs - we aren't using abs value so we need to account for if error was negative and previous error was positive, or vice versa to check whether it crossed 0.
//   if ((error > 0 && previous_error < 0) || (error < 0 && previous_error > 0))
//   {
//     accumulated_error = 0;
//   }

//   // calculate pid output
//   output = kp * error + ki * accumulated_error + kd * (error - previous_error);

//   // set previous error equal to the error of the most previous iteration (current error)
//   previous_error = error;

//   // if we are in the range considered acceptable to stop the movement, then increment the time spent settled by 10ms (the delay we have for each iteration)
//   if (fabs(error) < settle_error)
//   {
//     time_spent_settled += 10;
//   }
//   // if we are not in this range where it is acceptable to stop the movement, then set the time spent settled to 0 (keep it there, or reset it if something happened and we went back)
//   else
//   {
//     time_spent_settled = 0;
//   }

//   // increment time spent running by 10ms (the delay we have for each iteration), used for timeout
//   time_spent_running += 10;

//   // return the power to give the motors because this function is for COMPUTATION.
//   return output;
// }

// // settled error is a function that is called to check whether to stop the movement (settling = when to stop the movement)
// bool PID::is_settled()
// {
//   // if the time spent running is greater than the timeout (max time for the move), then its settled (end the move)
//   // need to add the timeout != 0 check because if we don't want a timeout for the movement, then we set it to 0, resulting in this condition to always be true, and movement doesn't run
//   // SO in the case that we set the timeout to 0, we still want it to run, which is why we want this check
//   if (time_spent_running > timeout && timeout != 0)
//   {
//     return (true);
//   }
//   // if the time spent settled (the time spent inside the error range that considered acceptable to stop the movement in) is greater than the amount of time we have set to spend in this settled position (prolly used to give ample time for bot to come to complete stop), then return that its settled (stop the movement)
//   if (time_spent_settled > settle_time)
//   {
//     return (true);
//   }
//   // if none of the above conditions are true, return false to keep running the movement.
//   return (false);
// }

// // some global variables that are important and stuff
// int starti = 100;
// double settleError = 5;   // doing 5 for fun
// int settleTime = 200;     // in ms
// int timeSpentSettled = 0; // in ms
// int timeSpentRunning = 0; // in ms
// int timeout = 2000;       // in ms

// // good pid (refactor the program later) - make into a task probably and make some of the pid values public like with the public interface and stuff so you can use the error values and stuff to determine when to do things like intake, actuate pistons, etc.
void goodPID(int desiredValue, double multiplier, int param_settleTime, int param_timeout)
{
    // Settings - variables initializations
    double kP = 0.13; // 0.115
    double kI = 0.0;  // 0.000000001
    double kD = .3;   // 0.0312

    // Autonomous Settings
    double error = 0;
    double prevError = 0;
    int derivative;
    double totalError = 0;

    // Reset the motor encoder positions
    LeftFrontMotor.setPosition(0, degrees);
    LeftMiddleMotor.setPosition(0, degrees);
    LeftBackMotor.setPosition(0, degrees);
    RightFrontMotor.setPosition(0, degrees);
    RightMiddleMotor.setPosition(0, degrees);
    RightBackMotor.setPosition(0, degrees);

    // some global variables that are important and stuff
    int starti = 100;                  // range from target to start accumulating integral (it will start accumulating when error is less than this value)
    double settleError = 5;            // doing 5 for fun
    int settleTime = param_settleTime; // in ms // 0
    int timeSpentSettled = 0;          // in ms
    int timeSpentRunning = 0;          // in ms
    int timeout = param_timeout;       // in ms // 2000

    while (true)
    {
        // CHECKING STOPPING CONDITIONS (you can also do this in the condition of the while loop) -> and then u call a function and use return statements like in jar.
        if (timeSpentRunning > timeout && timeout != 0)
        {
            // break;
            Brain.Screen.setCursor(3, 1);
            Brain.Screen.print("TIMEOUT drive");
            break;
        }
        // if the time spent settled (the time spent inside the error range that considered acceptable to stop the movement in) is greater than the amount of time we have set to spend in this settled position (prolly used to give ample time for bot to come to complete stop), then return that its settled (stop the movement)
        if (timeSpentSettled > settleTime)
        {
            break;
        }
        // if none of the above conditions are true, keep running the movement

        // Get the position of the motors
        int leftFrontMotorPosition = LeftFrontMotor.position(degrees);
        int leftMiddleMotorPosition = LeftMiddleMotor.position(degrees);
        int leftBackMotorPosition = LeftBackMotor.position(degrees);
        int rightFrontMotorPosition = RightFrontMotor.position(degrees);
        int rightMiddleMotorPosition = RightMiddleMotor.position(degrees);
        int rightBackMotorPosition = RightBackMotor.position(degrees);

        // Lateral Movement PID/Going forward and back

        // Get the average of the motors
        int averagePosition = ((leftFrontMotorPosition + leftBackMotorPosition + leftMiddleMotorPosition + rightFrontMotorPosition + rightMiddleMotorPosition + rightBackMotorPosition) / 6);

        // Potential
        error = desiredValue - averagePosition;

        // Derivative
        derivative = error - prevError;

        // Integral
        // if in range we want to accumulate integral (close to target), then accumulate integral
        if (fabs(error) < starti)
        {
            totalError += error;
        }
        // if crossing 0 then set total error to 0 (accumulated integral) - checking the sign change
        if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0))
        {
            totalError = 0;
        }

        // calculate motor power
        double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI)) * multiplier;

        // update prev error
        prevError = error;

        // UPDATING STOPPING VALUES
        // if in range acceptable to stop the movement then increment time spent settled
        if (fabs(error) < settleError)
        {
            timeSpentSettled += 10;
        }
        // if not in this range, then settled time needs to be 0
        else
        {
            timeSpentSettled = 0;
        }

        timeSpentRunning += 10; // assuming a 10 second delay everytime you call this

        // MOVE THE DRIVE MOTORS - R was rev
        LeftFrontMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);   //+ turnMotorPower (if turning). L/R for self-correction
        RightFrontMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);  //- turnMotorPower
        LeftMiddleMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);  //+ turnMotorPower
        RightMiddleMotor.spin(fwd, lateralMotorPower, voltageUnits::volt); //- turnMotorPower
        LeftBackMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);    //+ turnMotorPower
        RightBackMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);   //- turnMotorPower

        vex::task::sleep(10); // delay for 10ms
    }
    // stop the wheels after the while loop is done
    LeftFrontMotor.stop(hold);
    RightFrontMotor.stop(hold);
    LeftMiddleMotor.stop(hold);
    RightMiddleMotor.stop(hold);
    LeftBackMotor.stop(hold);
    RightBackMotor.stop(hold);

    Brain.Screen.print("DRIVE MOVEMENT DONE");
}

void goodTurnPID(int desiredValue, double multiplier, int param_settleTime, int param_timeout)
{
    // Settings - variables initializations
    double kP = 0.13; // 0.115
    double kI = 0.0;  // 0.000000001
    double kD = .3;   // 0.0312

    // Autonomous Settings
    double error = 0;
    double prevError = 0;
    int derivative;
    double totalError = 0;

    // Reset the motor encoder positions
    // LeftFrontMotor.setPosition(0, degrees);
    // LeftMiddleMotor.setPosition(0, degrees);
    // LeftBackMotor.setPosition(0, degrees);
    // RightFrontMotor.setPosition(0, degrees);
    // RightMiddleMotor.setPosition(0, degrees);
    // RightBackMotor.setPosition(0, degrees);

    // some global variables that are important and stuff
    int starti = 100;                  // range from target to start accumulating integral (it will start accumulating when error is less than this value)
    double settleError = 1;            // doing 5 for fun
    int settleTime = param_settleTime; // in ms // 0
    int timeSpentSettled = 0;          // in ms
    int timeSpentRunning = 0;          // in ms
    int timeout = param_timeout;       // in ms // 2000

    while (true)
    {
        // CHECKING STOPPING CONDITIONS (you can also do this in the condition of the while loop) -> and then u call a function and use return statements like in jar.
        if (timeSpentRunning > timeout && timeout != 0)
        {
            // break;
            Brain.Screen.setCursor(3, 1);
            Brain.Screen.print("TIMEOUT drive");
            break;
        }
        // if the time spent settled (the time spent inside the error range that considered acceptable to stop the movement in) is greater than the amount of time we have set to spend in this settled position (prolly used to give ample time for bot to come to complete stop), then return that its settled (stop the movement)
        if (timeSpentSettled > settleTime)
        {
            break;
        }
        // if none of the above conditions are true, keep running the movement

        // Get the position of the motors
        // int leftFrontMotorPosition = LeftFrontMotor.position(degrees);
        // int leftMiddleMotorPosition = LeftMiddleMotor.position(degrees);
        // int leftBackMotorPosition = LeftBackMotor.position(degrees);
        // int rightFrontMotorPosition = RightFrontMotor.position(degrees);
        // int rightMiddleMotorPosition = RightMiddleMotor.position(degrees);
        // int rightBackMotorPosition = RightBackMotor.position(degrees);

        // Lateral Movement PID/Going forward and back

        // Get the average of the motors
        int averagePosition = Inertial.heading();
        // ((leftFrontMotorPosition + leftBackMotorPosition + leftMiddleMotorPosition + rightFrontMotorPosition + rightMiddleMotorPosition + rightBackMotorPosition) / 6);

        // Potential
        error = reduce_negative_180_to_180(desiredValue - averagePosition);

        // Derivative
        derivative = error - prevError;

        // Integral
        // if in range we want to accumulate integral (close to target), then accumulate integral
        if (fabs(error) < starti)
        {
            totalError += error;
        }
        // if crossing 0 then set total error to 0 (accumulated integral) - checking the sign change
        if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0))
        {
            totalError = 0;
        }

        // calculate motor power
        double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI)) * multiplier;

        // update prev error
        prevError = error;

        // UPDATING STOPPING VALUES
        // if in range acceptable to stop the movement then increment time spent settled
        if (fabs(error) < settleError)
        {
            timeSpentSettled += 10;
        }
        // if not in this range, then settled time needs to be 0
        else
        {
            timeSpentSettled = 0;
        }

        timeSpentRunning += 10; // assuming a 10 second delay everytime you call this

        // MOVE THE DRIVE MOTORS - R was rev
        LeftFrontMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);    //+ turnMotorPower (if turning). L/R for self-correction
        RightFrontMotor.spin(fwd, -lateralMotorPower, voltageUnits::volt);  //- turnMotorPower
        LeftMiddleMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);   //+ turnMotorPower
        RightMiddleMotor.spin(fwd, -lateralMotorPower, voltageUnits::volt); //- turnMotorPower
        LeftBackMotor.spin(fwd, lateralMotorPower, voltageUnits::volt);     //+ turnMotorPower
        RightBackMotor.spin(fwd, -lateralMotorPower, voltageUnits::volt);   //- turnMotorPower

        vex::task::sleep(10); // delay for 10ms
    }
    // stop the wheels after the while loop is done
    LeftFrontMotor.stop(hold);
    RightFrontMotor.stop(hold);
    LeftMiddleMotor.stop(hold);
    RightMiddleMotor.stop(hold);
    LeftBackMotor.stop(hold);
    RightBackMotor.stop(hold);

    Brain.Screen.print("DRIVE MOVEMENT DONE");
}