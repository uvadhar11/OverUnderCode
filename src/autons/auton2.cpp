#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>
// using namespace std;

// GOAL: FAR SIDE AUTON
void auton2()
{
    // 3 TRIBALL
    // lift down
    // LiftMotor.spinFor(reverse, 250, degrees);

    // // spool up intake motor
    // IntakeFlywheelMotor.spin(fwd, 12, volt);
    // wait(1, sec);
    // IntakeFlywheelMotor.stop();

    // // drive slightly forward
    // goodPID(100, 1, 100, 2000);

    // wait(0.3, sec);

    // // drive back
    // goodPID(-1500, 1, 100, 2000);

    // turn parallel with matchload bar
    // goodTurnPID(-45, 1, 100, 2000);

    // // drive to take zone triball out
    // goodPID(-700, 1, 100, 2000);

    // // wing out
    // LeftWing.off();

    // wait(0.2, sec);

    // // turn slightly
    // goodTurnPID(-90, 1, 100, 2000);

    // ALLIANCE TRIBALL GUARANTEE
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

    // wait(0.5, sec);

    // // drive back
    // LeftFrontMotor.spin(reverse, 12, volt);
    // RightFrontMotor.spin(reverse, 12, volt);
    // LeftMiddleMotor.spin(reverse, 12, volt);
    // RightMiddleMotor.spin(reverse, 12, volt);
    // LeftBackMotor.spin(reverse, 12, volt);
    // RightBackMotor.spin(reverse, 12, volt);

    // wait(0.6, sec);

    // LeftFrontMotor.stop();
    // RightFrontMotor.stop();
    // LeftMiddleMotor.stop();
    // RightMiddleMotor.stop();
    // LeftBackMotor.stop();
    // RightBackMotor.stop();

    // SKILLS
    IntakeFlywheelMotor.spin(reverse, 12, volt);
    wait(55, sec);
    IntakeFlywheelMotor.stop();

    LeftFrontMotor.spin(forward, 12, volt);
    RightFrontMotor.spin(forward, 12, volt);
    LeftMiddleMotor.spin(forward, 12, volt);
    RightMiddleMotor.spin(forward, 12, volt);
    LeftBackMotor.spin(forward, 12, volt);
    RightBackMotor.spin(forward, 12, volt);

    wait(5, sec);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
}