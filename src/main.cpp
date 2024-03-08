#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/
// NOTE: MUST ADD IN ROBOT CONFIG

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

    // Specify your drive setup below. There are eight options:
    // ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
    // For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
    ZERO_TRACKER_NO_ODOM,

    // Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
    // You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

    // Left Motors:
    motor_group(LeftFrontMotor, LeftMiddleMotor, LeftBackMotor),

    // Right Motors:
    motor_group(RightFrontMotor, RightMiddleMotor, RightBackMotor),

    // Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
    PORT7,

    // Input your wheel diameter. (4" omnis are actually closer to 4.125"):
    3.25,

    // External ratio, must be in decimal, in the format of input teeth/output teeth.
    // If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
    // If the motor drives the wheel directly, this value is 1:
    0.75, // 0.8

    // Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
    // For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
    360,

    /*---------------------------------------------------------------------------*/
    /*                                  PAUSE!                                   */
    /*                                                                           */
    /*  The rest of the drive constructor is for robots using POSITION TRACKING. */
    /*  If you are not using position tracking, leave the rest of the values as  */
    /*  they are.                                                                */
    /*---------------------------------------------------------------------------*/

    // If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

    // FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
    // LF:      //RF:
    PORT1, -PORT2,

    // LB:      //RB:
    PORT3, -PORT4,

    // If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
    // If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
    // If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
    3,

    // Input the Forward Tracker diameter (reverse it to make the direction switch):
    2.75,

    // Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
    // For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
    // This distance is in inches:
    -2,

    // Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
    1,

    // Sideways tracker diameter (reverse to make the direction switch):
    -2.75,

    // Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
    5.5

);

int current_auton_selection = 0;
bool auto_started = false;

bool rightWingEnabled = false;
bool leftWingEnabled = false;
bool bothWingsEnabled = false;
bool intakePistonEnabled = false;
bool balancePistonEnabled = false;

// DRIVER CONTROL FUNCTIONS
void actuateLeftWing()
{
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Left Wing");
  Controller1.Screen.print("L BOZO");
  if (leftWingEnabled == false)
  {
    LeftWing.off();
    leftWingEnabled = true;
    wait(0.2, sec);
  }
  else
  {
    LeftWing.on();
    leftWingEnabled = false;
    wait(0.3, sec);
  }
}

void actuateRightWing()
{
  // Brain.Screen.setCursor(1, 1);
  // Brain.Screen.print("RIGHT Wing");
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

void actuateIntakePiston()
{
  if (intakePistonEnabled == false)
  {
    IntakePiston.on();
    intakePistonEnabled = true;
  }
  else
  {
    IntakePiston.off();
    intakePistonEnabled = false;
  }
}

void actuateBalancePiston()
{
  if (balancePistonEnabled == false)
  {
    BalancePiston.on();
    balancePistonEnabled = true;
  }
  else
  {
    BalancePiston.off();
    balancePistonEnabled = false;
  }
}

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants(); // sets the default constants for the chassis.

  // CALIBRATE INERTIAL
  Inertial.calibrate();

  while (auto_started == false)
  {                             // Changing the names below will only change their names on the
    Brain.Screen.clearScreen(); // brain screen for auton selection.
    // Brain.Screen.setFont(mono60);
    // Brain.Screen.setPenWidth(1.5);

    switch (current_auton_selection)
    { // Tap the brain screen to cycle through autons.
    case 0:
      Brain.Screen.printAt(50, 50, "NO AUTON");
      break;
    case 1:
      Brain.Screen.printAt(50, 50, "Drive Test");
      break;
    case 2:
      Brain.Screen.printAt(50, 50, "WINPOINT AUTON");
      break;
    case 3:
      Brain.Screen.printAt(50, 50, "Swing Test");
      break;
    case 4:
      Brain.Screen.printAt(50, 50, "Full Test");
      break;
    case 5:
      Brain.Screen.printAt(50, 50, "Odom Test");
      break;
    case 6:
      Brain.Screen.printAt(50, 50, "Tank Odom Test");
      break;
    case 7:
      Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
      break;
    }
    if (Brain.Screen.pressing())
    {
      while (Brain.Screen.pressing())
      {
      }
      current_auton_selection++;
    }
    else if (current_auton_selection == 8)
    {
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void)
{
  auto_started = true;
  switch (current_auton_selection)
  {
  case 0:
    // NOTHING IS RUN IF YOU DONT SELECT AN AUTON
    // drive_test(); // This is the default auton, if you don't select from the brain.
    // holonomic_odom_test();
    holonomic_odom_test();
    break; // Change these to be your own auton functions in order to use the auton selector.
  case 1:  // Tap the screen to cycle through autons.
    drive_test();
    break;
  case 2:
    winpoint_auton();
    break;
  case 3:
    swing_test();
    break;
  case 4:
    full_test();
    break;
  case 5:
    odom_test();
    break;
  case 6:
    tank_odom_test();
    break;
  case 7:
    holonomic_odom_test();
    break;
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

    // Replace this line with chassis.control_tank(); for tank drive
    // or chassis.control_holonomic(); for holo drive.

    // DRIVING
    // chassis.control_arcade();
    // DRIVETRAIN CODE
    double turnImportance = 0.6; // for changing the turn speed faster
    double speed = 1;            // changing speed

    double turnVal = Controller1.Axis1.position();
    double forwardVal = Controller1.Axis3.position();
    double turnVolts = (turnVal * 0.12 * speed);
    double forwardVolts = (forwardVal * 0.12 * (1 - (fabs(turnVolts) / 12.0) * turnImportance) * speed);

    LeftFrontMotor.spin(fwd, forwardVolts + turnVolts, volt);
    RightFrontMotor.spin(fwd, forwardVolts - turnVolts, volt);
    LeftMiddleMotor.spin(fwd, forwardVolts + turnVolts, volt);
    RightMiddleMotor.spin(fwd, forwardVolts - turnVolts, volt);
    LeftBackMotor.spin(fwd, forwardVolts + turnVolts, volt);
    RightBackMotor.spin(fwd, forwardVolts - turnVolts, volt);

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

    // // LIFT
    // if (Controller1.ButtonL1.pressing())
    // {
    //   LiftMotor.spin(fwd, 12, volt);
    // }
    // else if (Controller1.ButtonL2.pressing())
    // {
    //   LiftMotor.spin(fwd, -12, volt);
    // }
    // else
    // {
    //   LiftMotor.stop();
    // }

    // KICKER
    if (Controller1.ButtonLeft.pressing())
    {
      KickerMotor.spin(fwd, 12, volt);
      KickerMotor2.spin(fwd, 12, volt);
    }
    else
    {
      KickerMotor.stop(); // hold
      KickerMotor2.stop();
    }

    // kicker button
    // if (Controller1.ButtonB.pressing())
    // {
    //   // KickerMotor.setVelocity(100, velocityUnits::pct);
    //   // KickerMotor.setPosition(0, deg);
    //   // KickerMotor.spinToPosition(600, deg, true);

    //   while (KickerRotation.angle() > 310)
    //   {
    //     KickerMotor.spin(fwd, 8, volt);
    //   }
    // }

    // PISTONS
    Controller1.ButtonA.pressed(actuateRightWing);
    Controller1.ButtonY.pressed(actuateLeftWing);
    Controller1.ButtonL1.pressed(actuateBothWings);
    Controller1.ButtonL2.pressed(actuateIntakePiston);
    Controller1.ButtonDown.pressed(actuateBalancePiston);

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
