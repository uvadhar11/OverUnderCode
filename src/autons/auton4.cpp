#include "vex.h"
#include "init.h"
#include "linking.h"

// skills program
void auton4()
{
    // see if you can try to score the alliance triballs in the goal
    // LiftMotor.spin(forward, 12, volt);
    // wait(1.5, sec);
    // LiftMotor.stop();

    // // spin the flywheel for the match loading
    // IntakeFlywheelMotor.spin(vex::reverse, 12, volt);

    // // wait time for matchloading
    // wait(40, sec);

    // // stop the flywheel
    // IntakeFlywheelMotor.stop();

    // LiftMotor.spin(vex::reverse, 12, volt);
    // wait(1.5, sec);
    // LiftMotor.stop();

    // // drive forward
    // LeftFrontMotor.spin(forward, 12, volt);
    // RightFrontMotor.spin(forward, 12, volt);
    // LeftMiddleMotor.spin(forward, 12, volt);
    // RightMiddleMotor.spin(forward, 12, volt);
    // LeftBackMotor.spin(forward, 12, volt);
    // RightBackMotor.spin(forward, 12, volt);

    // wait(3, sec);

    // LeftFrontMotor.stop();
    // RightFrontMotor.stop();
    // LeftMiddleMotor.stop();
    // RightMiddleMotor.stop();
    // LeftBackMotor.stop();
    // RightBackMotor.stop();

    // turnPID()

    // turn

    // turn to the elevation bar

    // drive forward past the elevation bar

    // turn to angle to the goal

    // drive forward to push alliance triballs in the goal

    // drive back a little and turn away to do a center push

    // activate wings

    // drive forward to push in the goal

    // more pushes and edit as necessary

    // turnPID(-170, 1);

    // AUTON STUFF
    drivePID(300, 1); // drive back a bit

    // wing out
    LeftWing.off();

    // wait a second
    // wait(0.2, sec);

    // drive forward to descore
    drivePID(-200, 1);

    // turn
    turnPID(10, 1);

    // wing in
    LeftWing.on();

    // turn slightly
    // Inertial.
    wait(0.2, sec);

    // turn to bar
    turnPID(-30, 1);

    // release zipties
    IntakeFlywheelMotor.spin(reverse, 12, volt);
    wait(.3, sec);
    IntakeFlywheelMotor.stop();

    // // go to touch bar
    drivePID(-1500, 1);
}