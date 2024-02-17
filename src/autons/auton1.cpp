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
    // chassis.turn_to_angle(45, 12, 100, 2000);

    // drive towards goal
    goodPID(-700, 1, 100, 2000); // 15.88
    // chassis.drive_distance(-700, 45, 12, 12, 100, 2000);

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
    goodTurnPID(350, 1, 100, 2000);

    // drive forward to go to other side of the field
    goodPID(3500, 1, 100, 4500);

    // turn to face goal
    goodTurnPID(-50, 1, 100, 2000);

    // drive forward to score triballs
    goodPID(1000, 1, 100, 2000);

    // turn more
    goodTurnPID(-80, 1, 100, 2000);

    // drive forward to score triballs
    goodPID(500, 1, 100, 1200);

    // back up
    goodPID(-500, 1, 100, 1200);

    // again
    goodPID(500, 1, 100, 1200);

    // back up
    goodPID(-500, 1, 100, 1200);

    // turn towards barrier
    goodTurnPID(-40, 1.1, 100, 2000);

    // actuate wing
    RightWing.off();

    // drive forward
    goodPID(-600, 0.8, 0, 1500);

    // turn slowly
    goodTurnPID(180, 0.7, 100, 2000);

    // ram into goal

    // OLD BEFORE CHANGE TO INCHES
    // // wing to get push triball near alliance
    // LeftWing.off(); // left

    // wait(0.2, sec);

    // LeftWing.on(); // left

    // // turn parallel with matchload bar
    // goodTurnPID(45, 1, 100, 2000);

    // // drive towards goal
    // goodPID(-700, 1, 100, 2000);

    // // turn to matchload
    // goodTurnPID(135, 0.7, 100, 2500);

    // // drive back a little to touch matchload bar
    // goodPID(200, 1, 100, 2000);

    // // spin flywheel
    // IntakeFlywheelMotor.spin(fwd, 12, volt);
    // wait(2, sec); // 30
    // IntakeFlywheelMotor.stop();

    // // turn to goal
    // goodTurnPID(-100, 1, 100, 2000);

    // // ram triball in
    // goodPID(1000, 1, 100, 2000);

    // // wait for a second
    // wait(.8, sec);

    // // drive back
    // goodPID(-600, 1, 100, 2000);

    // // turn to cross side
    // goodTurnPID(45, 1, 100, 2000);

    // // drive forward
    // goodPID(800, 1, 100, 2000);

    // // turn to straighten
    // goodTurnPID(0, 1, 100, 2000);

    // // drive forward
    // goodPID(2000, 1, 100, 3000);
}