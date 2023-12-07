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
#include "test.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // DRIVETRAIN CODE
    double turnImportance = 1; // for changing the turn speed faster
    double speed = 1; // changing speed
    bool side = true; // bool for switching front and back. True: intake, False: wedge

    double turnVal = Controller1.Axis1.position();
    double forwardVal = Controller1.Axis3.position();
    double turnVolts = (turnVal * 0.12 * speed); // multiplying the -1 so it goes the other way since it was inverted.
    double forwardVolts = (forwardVal * 0.12 * (1 - (fabs(turnVolts)/12.0) * turnImportance) * speed);

    if (side) {
      LeftFrontMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightFrontMotor.spin(fwd, forwardVolts - turnVolts, volt);
      LeftMiddleMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightMiddleMotor.spin(fwd, forwardVolts - turnVolts, volt);
      LeftBackMotor.spin(fwd, forwardVolts + turnVolts, volt);
      RightBackMotor.spin(fwd, forwardVolts - turnVolts, volt);
    } else {
      LeftFrontMotor.spin(fwd, forwardVolts - turnVolts, volt);
      RightFrontMotor.spin(fwd, forwardVolts + turnVolts, volt);
      LeftMiddleMotor.spin(fwd, forwardVolts - turnVolts, volt);
      RightMiddleMotor.spin(fwd, forwardVolts + turnVolts, volt);
      LeftBackMotor.spin(fwd, forwardVolts - turnVolts, volt);
      RightBackMotor.spin(fwd, forwardVolts + turnVolts, volt);
    }

    // INTAKE/FLYWHEEL
    if (Controller1.ButtonR1.pressing()) {
      IntakeFlywheelMotor.spin(fwd, 12, volt);
    } else if (Controller1.ButtonR2.pressing()) {
      IntakeFlywheelMotor.spin(fwd, -12, volt);
    } else {
      IntakeFlywheelMotor.stop();
    }

    // LIFT
    if (Controller1.ButtonL1.pressing()) {
      LiftMotor.spin(fwd, 12, volt);
    } else if (Controller1.ButtonL2.pressing()) {
      LiftMotor.spin(fwd, -12, volt);
    } else {
      LiftMotor.stop();
    }

    // WINGS
    if (Controller1.ButtonB.pressing()) {
      // both wings

    } else if (Controller1.ButtonY.pressing()) {
      // right wing

    } else if (Controller1.ButtonRight.pressing()) {
      // left wing
    }

    // SWITCH FRONT/BACK BUTTON
    if (Controller1.ButtonDown.pressing()) {
      // switch front and back
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
