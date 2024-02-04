#include "vex.h"
#include "init.h"
#include "linking.h"

void auton3()
{
    // starting at 90 degrees
    // turn towards net

    // turnPID(45, 1);

    // drive to yeet the triball in the goal
    // LeftFrontMotor.spin(forward, 12, volt);
    // RightFrontMotor.spin(forward, 12, volt);
    // LeftMiddleMotor.spin(forward, 12, volt);
    // RightMiddleMotor.spin(forward, 12, volt);
    // LeftBackMotor.spin(forward, 12, volt);
    // RightBackMotor.spin(forward, 12, volt);

    // wait(2, sec);

    // LeftFrontMotor.stop();
    // RightFrontMotor.stop();
    // LeftMiddleMotor.stop();
    // RightMiddleMotor.stop();
    // LeftBackMotor.stop();
    // RightBackMotor.stop();

    // drivePID(400, 1);

    // then drive forward to get the triball out

    // actuate wing

    // drive forward to get the green out

    // then drive forward to touch the elevation bar

    // SPIN FLYWHEEL TO GET ZIP TIE OUT
    // IntakeFlywheelMotor.spin(forward, 12, volt);

    // wait(0.3, sec);

    // IntakeFlywheelMotor.stop();

    // // setting velocity
    // LeftFrontMotor.setVelocity(100, pct);
    // RightFrontMotor.setVelocity(100, pct);
    // LeftMiddleMotor.setVelocity(100, pct);
    // RightMiddleMotor.setVelocity(100, pct);
    // LeftBackMotor.setVelocity(100, pct);
    // RightBackMotor.setVelocity(100, pct);

    // // testing stuff
    // turnPID(-45, 0.8);

    // // RightFrontMotor.spinFor(forward, 150, deg, false);
    // // RightMiddleMotor.spinFor(forward, 150, deg, false);
    // // RightBackMotor.spinFor(forward, 150, deg, true);

    // // drivePID(350, 1);

    // // fwd little
    // LeftFrontMotor.spinFor(forward, 350, deg, false); // may need to reduce this a bit
    // RightFrontMotor.spinFor(forward, 350, deg, false);
    // LeftMiddleMotor.spinFor(forward, 350, deg, false);
    // RightMiddleMotor.spinFor(forward, 350, deg, false);
    // LeftBackMotor.spinFor(forward, 350, deg, false);
    // RightBackMotor.spinFor(forward, 350, deg, true);

    // // back a little
    // LeftFrontMotor.spinFor(forward, -175, deg, false);
    // RightFrontMotor.spinFor(forward, -175, deg, false);
    // LeftMiddleMotor.spinFor(forward, -175, deg, false);
    // RightMiddleMotor.spinFor(forward, -175, deg, false);
    // LeftBackMotor.spinFor(forward, -175, deg, false);
    // RightBackMotor.spinFor(forward, -175, deg, true);

    // // RETRACT PISTON

    // //
    // turnPID(-75, 1); // change angle a bit less cuz turn is wrong. old: -85

    // wait(0.1, sec);

    // LeftFrontMotor.spinFor(forward, 700, deg, false); // old was 1600
    // RightFrontMotor.spinFor(forward, 700, deg, false);
    // LeftMiddleMotor.spinFor(forward, 700, deg, false);
    // RightMiddleMotor.spinFor(forward, 700, deg, false);
    // LeftBackMotor.spinFor(forward, 700, deg, false);
    // RightBackMotor.spinFor(forward, 700, deg, true);

    // // trying this stuff
    // wait(0.1, sec);

    // LeftFrontMotor.spinFor(forward, 1000, deg, false);
    // RightFrontMotor.spinFor(forward, 1000, deg, false);
    // LeftMiddleMotor.spinFor(forward, 1000, deg, false);
    // RightMiddleMotor.spinFor(forward, 1000, deg, false);
    // LeftBackMotor.spinFor(forward, 1000, deg, false);
    // RightBackMotor.spinFor(forward, 1000, deg, true);

    // turnPID(-90, 1);

    // drivePID(450, 1);

    // turning pid

    // AUTON
    // activate right wing, Start pos: 45 degree angle wedge first to most middle triball
    RightWing.off();

    // drive into middle triball
    goodPID(-2100, 1);

    // turn to middle barrier
    turnPID(45, 1);

    // close right wing
    RightWing.on();

    // turn back to go to the watchload area to descore triball
    // turnPID(-90, 1.5);

    // drive to matchload
    // goodPID(-2000, 1);
}