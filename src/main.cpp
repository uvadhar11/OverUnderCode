/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Kings                                                     */
/*    Created:      12/4/2023, 5:15:01 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// IMPORTS
#include "vex.h"
#include "init.h"
#include "linking.h"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
bool side = true; // bool for switching front and back. True: intake, False: wedge

// pneumatics variables
bool rightWingEnabled = false;
bool leftWingEnabled = false;
bool bothWingsEnabled = false;

// degrees calculation function
double revolutions(double inches)
{
  return inches * (48 / 60) * 600 * M_PI * 3.25; // inches * motor ticks * gear ratio * pi * wheel inches <- WRONG
  // inches * 300 * (3/7) * M_PI * 4.05;
  // try: inches / gear ratio * 2 * pi  * wheel diameter * 600 (for blue motor ticks I think) - seems to be correct maybe
}

// // rand ai thing
// double revolutions(double inches, double wheelDiameter, double gearRatio, double ticksPerRevolution)
// {
//   double wheelCircumference = M_PI * wheelDiameter;
//   double wheelRevolutions = inches / wheelCircumference;
//   double motorRevolutions = wheelRevolutions * gearRatio;
//   double motorDegrees = motorRevolutions * ticksPerRevolution;
//   return motorDegrees;
// }

// another rand ai thing
// double calculateMotorDegrees(double distanceInInches, double wheelDiameterInInches)
// {
//     const double PI = 3.14159265358979323846;
//     double circumference = PI * wheelDiameterInInches;
//     double rotations = distanceInInches / circumference;
//     double degrees = rotations * 360.0;
//     return degrees;
// }

// pneumatics functions
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

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // CALIBRATE the gyro and other sensors and stuff (also add as needed)
  Inertial.calibrate();

  // AUTON SCREEN SELECTOR STUFF
  initalizeAutonSelector();         // set the start rectangle conditions
  initalizeAllianceColorSelector(); // set the start alliance color selection conditions

  Brain.Screen.pressed(autonScreenSelector);

  autonSelected = 2;
}

/*--------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  if (autonSelected == 1)
  {
    auton1();
  }
  else if (autonSelected == 2)
  {
    auton2();
  }
  else if (autonSelected == 3)
  {
    auton3();
  }
  else if (autonSelected == 4)
  {
    auton4();
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // DRIVETRAIN CODE
    double turnImportance = 0.8; // for changing the turn speed faster
    double speed = 1;            // changing speed

    double turnVal = Controller1.Axis1.position();
    double forwardVal = Controller1.Axis3.position();
    double turnVolts = (turnVal * 0.12 * speed);
    double forwardVolts = (forwardVal * 0.12 * (1 - (fabs(turnVolts) / 12.0) * turnImportance) * speed);

    if (side)
    {
      LeftFrontMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightFrontMotor.spin(fwd, forwardVolts - turnVolts, volt);
      LeftMiddleMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightMiddleMotor.spin(fwd, forwardVolts - turnVolts, volt);
      LeftBackMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightBackMotor.spin(fwd, forwardVolts - turnVolts, volt);
    }
    else
    {
      LeftFrontMotor.spin(reverse, forwardVolts + turnVolts, volt);
      RightFrontMotor.spin(reverse, forwardVolts - turnVolts, volt);
      LeftMiddleMotor.spin(reverse, forwardVolts + turnVolts, volt);
      RightMiddleMotor.spin(reverse, forwardVolts - turnVolts, volt);
      LeftBackMotor.spin(reverse, forwardVolts + turnVolts, volt);
      RightBackMotor.spin(reverse, forwardVolts - turnVolts, volt);
    }

    // INTAKE/FLYWHEEL
    if (Controller1.ButtonR2.pressing())
    {
      IntakeFlywheelMotor.spin(fwd, 12, volt);
    }
    else if (Controller1.ButtonR1.pressing())
    {
      IntakeFlywheelMotor.spin(fwd, -12, volt);
    }
    else
    {
      IntakeFlywheelMotor.stop();
    }

    // LIFT
    if (Controller1.ButtonL1.pressing())
    {
      LiftMotor.spin(fwd, 12, volt);
    }
    else if (Controller1.ButtonL2.pressing())
    {
      LiftMotor.spin(fwd, -12, volt);
    }
    else
    {
      LiftMotor.stop();
    }

    // KICKER
    if (Controller1.ButtonLeft.pressing())
    {
      KickerMotor.spin(fwd, 12, volt);
    }
    else
    {
      KickerMotor.stop();
    }

    // WINGS
    // if (Controller1.ButtonX.pressing())
    // {
    //   // both wings
    //   if (leftWingEnabled == false) {
    //     LeftWing.on();
    //     leftWingEnabled = true;
    //   } else {
    //     LeftWing.on();
    //     leftWingEnabled = false;
    //   }

    //   //

    // }

    //  WINGS
    // if (Controller1.ButtonY.pressing())
    // {
    //   if (leftWingEnabled == false)
    //   {
    //     LeftWing.off();
    //     leftWingEnabled = true;
    //     wait(0.1, sec);
    //   }
    //   else
    //   {
    //     LeftWing.on();
    //     leftWingEnabled = false;
    //     wait(0.1, sec);
    //   }
    // }
    Controller1.ButtonY.pressed(actuateLeftWing);
    Controller1.ButtonA.pressed(actuateRightWing);
    Controller1.ButtonX.pressed(actuateBothWings);

    // if (Controller1.ButtonA.pressing())
    // {
    //   if (rightWingEnabled == false)
    //   {
    //     RightWing.off();
    //     rightWingEnabled = true;
    //     wait(0.1, sec);
    //   }
    //   else
    //   {
    //     RightWing.on();
    //     rightWingEnabled = false;
    //     wait(0.1, sec);
    //   }
    // }

    // if (Controller1.ButtonA.pressing())
    // {
    //   // right wing
    //   RightWing.on();
    // }

    // SWITCH FRONT/BACK BUTTON
    // if (Controller1.ButtonDown.pressing())
    // {
    //   // switch front and back
    // }

    // JAR TEMPLATE ARCADE CODE
    // void Drive::control_arcade()
    // {
    //   // deadband is a function taking the value and the 2nd parameter is the deadzone width
    //   // calculates lateral movement
    //   float throttle = deadband(controller(primary).Axis3.value(), 5);
    //   // calculates turning
    //   float turn = deadband(controller(primary).Axis1.value(), 5);
    //   DriveL.spin(fwd, to_volt(throttle + turn), volt);
    //   DriveR.spin(fwd, to_volt(throttle - turn), volt);
    // }

    // DEADBAND FUNCTION THAT IS USED ABOVE
    // deadband looks like a deadzone of argument width and input is the input taken in from the controller
    // float deadband(float input, float width)
    // {
    //   // if the input percentage (absolute value to account for negatives) is inside the width of the deadzone, then return 0 (no affect)
    //   if (fabs(input) < width)
    //   {
    //     return (0);
    //   }
    //   // if not in this width then just return the input to be used
    //   return (input);
    // }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
