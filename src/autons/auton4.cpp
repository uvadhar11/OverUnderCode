#include "vex.h"
#include "init.h"
#include "linking.h"

// WP auton
void auton4()
{
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