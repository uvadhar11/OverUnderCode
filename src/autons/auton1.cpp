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
    goodTurnPID(135, 0.7, 100, 2500);

    // drive back a little to touch matchload bar
    goodPID(200, 1, 100, 2000);

    // spin flywheel
    IntakeFlywheelMotor.spin(fwd, 12, volt);
    wait(2, sec); // 30
    IntakeFlywheelMotor.stop();

    // turn to goal
    goodTurnPID(-100, 1, 100, 2000);

    // ram triball in
    goodPID(1000, 1, 100, 2000);

    // wait for a second
    wait(.8, sec);

    // drive back
    goodPID(-600, 1, 100, 2000);

    // turn to cross side
    goodTurnPID(45, 1, 100, 2000);

    // drive forward
    goodPID(800, 1, 100, 2000);

    // turn to straighten
    goodTurnPID(0, 1, 100, 2000);

    // drive forward
    goodPID(2000, 1, 100, 3000);
}