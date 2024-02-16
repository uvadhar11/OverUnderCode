#include "vex.h"
#include "init.h"
#include "linking.h"

// GOAL: SKILLS
void auton1()
{
    // wing to get push triball near alliance
    LeftWing.off(); // left

    wait(0.2, sec);

    LeftWing.on(); // left

    // turn parallel with matchload bar
    goodTurnPID(45, 1, 100, 2000);

    // drive towards goal
    goodPID(-700, 1, 100, 2000);

    // turn to matchload
    goodTurnPID(142, 0.7, 100, 2500);

    // drive back a little to touch matchload bar
    goodPID(200, 1, 100, 2000);

    // spin flywheel
    IntakeFlywheelMotor.spin(fwd, 12, volt);
    wait(30, sec);
    IntakeFlywheelMotor.stop();
}