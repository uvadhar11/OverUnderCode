#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>
// using namespace std;

// GOAL: FAR SIDE AUTON
void auton2()
{
    // lift down
    LiftMotor.spinFor(reverse, 250, degrees);

    // spool up intake motor
    IntakeFlywheelMotor.spin(fwd, 12, volt);
    wait(1, sec);
    IntakeFlywheelMotor.stop();

    // drive slightly forward
    goodPID(100, 1, 100, 2000);

    // drive back
    goodPID(-1500, 1, 100, 2000);

    // turn parallel with matchload bar
    goodTurnPID(-45, 1, 100, 2000);

    // drive to take zone triball out
    goodPID(-400, 1, 100, 2000);

    // wing out
    LeftWing.off();

    wait(0.2, sec);

    // turn slightly
    goodTurnPID(-90, 1, 100, 2000);
}