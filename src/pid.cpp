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
    // double targetGyroPosition = Inertial.yaw(rotationUnits::deg); // get value for self-correction

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
        // int GyroPosition = Inertial.yaw(rotationUnits::deg) - targetGyroPosition;

        // if (Inertial.yaw(rotationUnits::deg) < targetGyroPosition) {

        //   rightValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;

        // } else {

        //   rightValue = 0;
        // }

        // if (Inertial.yaw(rotationUnits::deg) > targetGyroPosition) {

        //   leftValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;

        // } else {

        //   leftValue = 0;
        // }

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
    // double targetGyroPosition = Inertial.yaw(rotationUnits::deg); // get value for self correction

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
        // int GyroPosition = Inertial.yaw(rotationUnits::deg) - targetGyroPosition;

        // if (Inertial.yaw(rotationUnits::deg) < targetGyroPosition) {

        //   rightValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;

        // } else {

        //   rightValue = 0;
        // }

        // if (Inertial.yaw(rotationUnits::deg) > targetGyroPosition) {

        //   leftValue = abs(GyroPosition) * abs(GyroPosition) / selfCorrect;

        // } else {

        //   leftValue = 0;
        // }

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
int ticks = 15000; // for faster turn speed. So doesn't break everything else if turn doesn't work.

// TURN PID FUNCTION
void turnPID(int desiredValue, double multiplier)
{
    // Settings - variables initializations
    double kP = 0.2;
    double kI = 0.000000000000; // last digit was 1
    double kD = 0.0001;

    // Autonomous Settings
    double error = 0;
    double prevError = 0;
    int derivative;
    double totalError = 0;

    int turnTime = 0; // to keep track of the current turn time (ticks I think). To check if > 15000 or not.

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

        turnTime = turnTime + 1; // update current turn time.

        // if (turnTime > ticks) {
        //   break;
        // }

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

// can also make a turn pid function for doing stuff while the pid is running since this isn't a task.