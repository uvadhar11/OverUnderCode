#include "vex.h"
#include "init.h"
#include "linking.h"

// GOAL: guarantee alliance triball (ram it into the goal)
// STARTING POSITION: alliance triball in front of bot and angled to ram into goal
void auton1()
{
    // just drive forward and ram the triball inside the goal
    LeftFrontMotor.spin(forward, 12, volt);
    RightFrontMotor.spin(forward, 12, volt);
    LeftMiddleMotor.spin(forward, 12, volt);
    RightMiddleMotor.spin(forward, 12, volt);
    LeftBackMotor.spin(forward, 12, volt);
    RightBackMotor.spin(forward, 12, volt);

    // wait for the robot to ram the triball in the goal
    wait(1.2, sec);

    // stop the drivetrain motors
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
}