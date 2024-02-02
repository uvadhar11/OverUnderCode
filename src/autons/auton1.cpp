#include "vex.h"
#include "init.h"
#include "linking.h"

// GOAL: guarantee alliance triball (ram it into the goal)
// STARTING POSITION: alliance triball in front of bot and angled to ram into goal
void auton1()
{
    // // just drive forward and ram the triball inside the goal
    LeftFrontMotor.spin(reverse, 12, volt);
    RightFrontMotor.spin(reverse, 12, volt);
    LeftMiddleMotor.spin(reverse, 12, volt);
    RightMiddleMotor.spin(reverse, 12, volt);
    LeftBackMotor.spin(reverse, 10, volt);
    RightBackMotor.spin(reverse, 12, volt);

    // wait for the robot to ram the triball in the goal
    wait(0.91, sec); // 1.l2 for ram

    // wing
    // RightWing.off();

    // wait(0.33, sec); // 1.l2 for ram

    // stop the drivetrain motors
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();

    RightWing.off();

    // wait(.1, sec);

    // turn to middle
    turnPID(45, 1);

    // mid over
    LeftFrontMotor.spin(reverse, 12, volt);
    RightFrontMotor.spin(reverse, 12, volt);
    LeftMiddleMotor.spin(reverse, 12, volt);
    RightMiddleMotor.spin(reverse, 12, volt);
    LeftBackMotor.spin(reverse, 12, volt);
    RightBackMotor.spin(reverse, 12, volt);

    // wait for the robot to ram the triball in the goal
    wait(0.3, sec); // 1.l2 for ram

    // stop the drivetrain motors
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftMiddleMotor.stop();
    RightMiddleMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();

    //

    // wait(0.55, sec); // 1.l2 for ram

    // RightBackMotor.spin(reverse, 12, volt);

    // far side, messer upper
    // drivePID(-1000, 1);
}