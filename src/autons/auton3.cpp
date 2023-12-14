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
    LeftFrontMotor.setVelocity(100, pct);
    RightFrontMotor.setVelocity(100, pct);
    LeftMiddleMotor.setVelocity(100, pct);
    RightMiddleMotor.setVelocity(100, pct);
    LeftBackMotor.setVelocity(100, pct);
    RightBackMotor.setVelocity(100, pct);

    // testing stuff
    turnPID(-45, 1);

    // RightFrontMotor.spinFor(forward, 150, deg, false);
    // RightMiddleMotor.spinFor(forward, 150, deg, false);
    // RightBackMotor.spinFor(forward, 150, deg, true);

    // drivePID(350, 1);

    // fwd little
    LeftFrontMotor.spinFor(forward, 400, deg, false);
    RightFrontMotor.spinFor(forward, 400, deg, false);
    LeftMiddleMotor.spinFor(forward, 400, deg, false);
    RightMiddleMotor.spinFor(forward, 400, deg, false);
    LeftBackMotor.spinFor(forward, 400, deg, false);
    RightBackMotor.spinFor(forward, 400, deg, true);

    // back a little
    LeftFrontMotor.spinFor(forward, -175, deg, false);
    RightFrontMotor.spinFor(forward, -175, deg, false);
    LeftMiddleMotor.spinFor(forward, -175, deg, false);
    RightMiddleMotor.spinFor(forward, -175, deg, false);
    LeftBackMotor.spinFor(forward, -175, deg, false);
    RightBackMotor.spinFor(forward, -175, deg, true);

    // RETRACT PISTON

    //
    turnPID(-85, 1);

    wait(0.1, sec);

    LeftFrontMotor.spinFor(forward, 1600, deg, false);
    RightFrontMotor.spinFor(forward, 1600, deg, false);
    LeftMiddleMotor.spinFor(forward, 1600, deg, false);
    RightMiddleMotor.spinFor(forward, 1600, deg, false);
    LeftBackMotor.spinFor(forward, 1600, deg, false);
    RightBackMotor.spinFor(forward, 1600, deg, true);

    // turnPID(-90, 1);

    // drivePID(450, 1);
}