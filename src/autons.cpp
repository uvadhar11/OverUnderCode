#include "vex.h"

void default_constants()
{
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 4, 0, 10, 0); // defaults: 10, 1.5, 0, 10, 0 -> 6 had no oscillation. 10, 4, 0, 10, 0 has smooth stop.  10, 5, 0, 10, 0 has smooth stop. another: 10, 7, 0, 11, 0
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 100, 5000);
  chassis.set_turn_exit_conditions(1, 100, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants()
{
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test()
{
  // chassis.drive_distance(12);
  // chassis.drive_distance(12);
  // chassis.drive_distance(18);
  // chassis.drive_distance(-36);

  // chassis.drive_with_voltage(6, 6);

  // chassis.turn_to_angle(180);

  LeftWing.off();
}

void winpoint_auton()
{
  // chassis.turn_to_angle(5);
  // chassis.turn_to_angle(30);
  // chassis.turn_to_angle(90);
  // chassis.turn_to_angle(225);
  // chassis.turn_to_angle(0);

  // STARTING POSITION:

  // drive back a little bit
  chassis.drive_distance(6); // drive back a bit

  // wing out
  LeftWing.off();

  // wait for wing actuation
  wait(0.2, sec);

  // drive forward to remove triball
  chassis.drive_distance(-4);

  // retract wing
  LeftWing.on();

  // quick wait for wing retraction
  wait(0.2, sec);

  // turn to go touch the wp bar
  chassis.turn_to_angle(-30);

  // drive forward to bar little bit (then fix the angle)
  chassis.drive_distance(-28); // -18

  // turn a little bit to face elevation bar with wedge
  chassis.turn_to_angle(-45);

  // drive forward to touch the elevation bar
  chassis.drive_distance(-12);
}

// 3 TRIBALL AUTON
void swing_test()
{
  // chassis.left_swing_to_angle(90);
  // chassis.right_swing_to_angle(0);

  // spool up intake motor
  IntakeFlywheelMotor.spin(fwd, 12, volt);
  wait(1.2, sec);
  // IntakeFlywheelMotor.stop();

  // lift down
  LiftMotor.spinFor(reverse, 180, degrees);

  // // spool up intake motor
  // IntakeFlywheelMotor.spin(fwd, 12, volt);
  // wait(1.2, sec);
  // IntakeFlywheelMotor.stop();

  // drive slightly forward
  chassis.drive_distance(1);

  // wait a second
  wait(0.3, sec);

  // drive back
  chassis.drive_distance(-34);

  // turn to goal
  chassis.turn_to_angle(-45);

  // piston out
  LeftWing.off();

  wait(0.2, sec);

  // drive forward to take the triball out
  chassis.drive_distance(-14);

  // wait real quick for triball to get out
  wait(0.15, sec);

  // close wing
  LeftWing.on();

  // turn to goal
  chassis.turn_to_angle(-60);

  // drive forward to score
  chassis.drive_distance(-20);

  // quick wait
  wait(0.05, sec);

  // drive back
  chassis.drive_distance(10);

  // turn to goal with intake
  chassis.turn_to_angle(120);

  IntakeFlywheelMotor.stop();

  // drive to score
  chassis.drive_distance(10);
}

//  SKILLS
void full_test()
{
  // chassis.drive_distance(24);
  // chassis.turn_to_angle(-45);
  // chassis.drive_distance(-36);
  // chassis.right_swing_to_angle(-90);
  // chassis.drive_distance(24);
  // chassis.turn_to_angle(0);

  // wall ride matchload bar
  chassis.drive_distance(25, 45, 6, 6);

  // turn to goal
  chassis.turn_to_angle(90);

  // push triballs in goal
  chassis.drive_distance(20, 90, 10, 12, 1.5, 100, 1000);

  // back to matchload bar
  chassis.drive_distance(-22);

  // angle for matchloading
  chassis.turn_to_angle(-20);

  // drive back to make sure we are touching the bar
  chassis.drive_distance(3);

  // matchload
  // wait(2, sec);
  KickerMotor.spin(fwd, 11, volt);
  wait(32, sec);
  KickerMotor.stop();

  // moving kicker under
  while (KickerRotation.angle() > 310)
  {
    KickerMotor.spin(fwd, 8, volt);
  }
  KickerMotor.stop(hold); // hold position of kicker motor

  // turn to cross side
  chassis.turn_to_angle(45);
  chassis.drive_distance(-24);

  // angle straight
  chassis.turn_to_angle(0);

  // drive across
  chassis.drive_distance(-60, 0, 10, 12);
  // slow to make sure triballs don't fly over into zone
  chassis.drive_distance(-24, 0, 6, 6, 1.5, 100, 1000);

  // turn to goal
  chassis.turn_to_angle(-45);

  // forward a little bit
  chassis.drive_distance(-14, -45, 8, 12, 1.5, 100, 700);

  // turn to goal to cover more triballs
  chassis.turn_to_angle(-60);

  // drive forward to score
  chassis.drive_distance(-20, -60, 12, 12, 1.5, 100, 1200);

  // back
  chassis.drive_distance(7, -60, 8, 12, 1.5, 100, 700);

  // again
  chassis.drive_distance(-10, -60, 12, 12, 1.5, 100, 600);

  // back
  chassis.drive_distance(22);

  // turn
  chassis.turn_to_angle(-135);

  // wing off for funneling
  // LeftWing.off();

  // drive forward
  chassis.drive_distance(-38, -135, 7, 9);

  // turn to goal
  chassis.turn_to_angle(20);

  // drive forward to score
  RightWing.off();
  chassis.drive_distance(-30, 0, 8, 10, 1.5, 100, 900);

  // wings off
  LeftWing.on();
  RightWing.on();

  // drive back and angle
  chassis.drive_distance(30, 30, 12, 12, 1.5, 150, 900);

  // score
  RightWing.off();
  chassis.drive_distance(-30, 0, 12, 12, 1.5, 150, 900);

  // drive back and angle
  RightWing.on();
  chassis.drive_distance(30, 30, 12, 12, 1.5, 150, 900);

  // score
  RightWing.off();
  LeftWing.off();
  chassis.drive_distance(-30, 0, 12, 12, 1.5, 100, 900);

  // back little
  // chassis.drive_distance(10, 0, 12, 12, 1.5, 100, 400);
}

void odom_test()
{
  // KickerMotor.setVelocity(100, velocityUnits::pct);
  // KickerMotor.setPosition(0, deg);
  // KickerMotor.spinToPosition(600, deg, true);
  // chassis.set_coordinates(0, 0, 0);
  // while (1)
  // {
  //   Brain.Screen.clearScreen();
  //   Brain.Screen.printAt(0, 50, "X: %f", chassis.get_X_position());
  //   Brain.Screen.printAt(0, 70, "Y: %f", chassis.get_Y_position());
  //   Brain.Screen.printAt(0, 90, "Heading: %f", chassis.get_absolute_heading());
  //   Brain.Screen.printAt(0, 110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
  //   Brain.Screen.printAt(0, 130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
  //   task::sleep(20);
  // }
  // while (KickerRotation.angle() > 310)
  // {
  //   KickerMotor.spin(fwd, 8, volt);
  // }
  // KickerMotor.stop(hold); // hold position of kicker motor

  // score triball
  LeftFrontMotor.spin(fwd, 12, volt);
  RightFrontMotor.spin(fwd, 12, volt);
  LeftMiddleMotor.spin(fwd, 12, volt);
  RightMiddleMotor.spin(fwd, 12, volt);
  LeftBackMotor.spin(fwd, 12, volt);
  RightBackMotor.spin(fwd, 12, volt);

  wait(1.75, sec);

  LeftFrontMotor.stop();
  RightFrontMotor.stop();
  LeftMiddleMotor.stop();
  RightMiddleMotor.stop();
  LeftBackMotor.stop();
  RightBackMotor.stop();

  // drive back
  LeftFrontMotor.spin(reverse, 12, volt);
  RightFrontMotor.spin(reverse, 12, volt);
  LeftMiddleMotor.spin(reverse, 12, volt);
  RightMiddleMotor.spin(reverse, 12, volt);
  LeftBackMotor.spin(reverse, 12, volt);
  RightBackMotor.spin(reverse, 12, volt);

  wait(0.4, sec);

  LeftFrontMotor.stop();
  RightFrontMotor.stop();
  LeftMiddleMotor.stop();
  RightMiddleMotor.stop();
  LeftBackMotor.stop();
  RightBackMotor.stop();
}

void tank_odom_test()
{
  // odom_constants();
  // chassis.set_coordinates(0, 0, 0);
  // chassis.turn_to_point(24, 24);
  // chassis.drive_to_point(24, 24);
  // chassis.drive_to_point(0, 0);
  // chassis.turn_to_angle(0);

  // activate right wing, Start pos: 45 degree angle wedge first to most middle triball
  RightWing.off();

  // drive into middle triball
  // goodPID(-2100, 1, 0, 2000);

  // turn to middle barrier
  // turnPID(45, 1);
  // chassis.drive_distance(-47, 45, 10, 0.3, 1.5, 100, 4000);
  chassis.drive_distance(-47);

  chassis.turn_to_angle(45);

  // close right wing
  RightWing.on();
}

void holonomic_odom_test()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}