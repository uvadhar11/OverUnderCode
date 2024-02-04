#include "vex.h"
#include "init.h"
#include "linking.h"
#include <iostream>
// using namespace std;

// GOAL: SIMPLE WINPOINT AUTON (take triball out, touch elevation bar at the end)
void auton2()
{
    // drive forward to the starting part of the matchload bar (while pushing the alliance triball)

    // turn and drive forward a little bit with wing to get the green triball out

    // wing back in (if necessary)

    // push the triball and alliance triball into the goal

    // turn and angle to touch the elevation bar

    // drive forward to touch the elevation bar and push the green triball to the other side
    // turnPID(-45, 1);

    // // ANOTHER TESTING THING
    // // trying to spin the right side only to align it with the matchload thing [INTAKE FRONT]
    // while (Inertial.heading(deg) > -45)
    // {
    //     RightFrontMotor.spin(forward, 8, volt);
    //     RightMiddleMotor.spin(forward, 8, volt);
    //     RightBackMotor.spin(forward, 8, volt);

    //     // print the heading
    //     std::cout << Inertial.heading(deg) << std::endl;

    //     // std::cout << Inertial.heading(deg) << std::endl;
    // }

    // // ACTUATE wings because bot is aligned with the matchload bar

    // // drive forward a little bit
    // LeftFrontMotor.spinFor(forward, 300, deg, false);
    // RightFrontMotor.spinFor(forward, 300, deg, false);
    // LeftMiddleMotor.spinFor(forward, 300, deg, false);
    // RightMiddleMotor.spinFor(forward, 300, deg, false);
    // LeftBackMotor.spinFor(forward, 300, deg, false);
    // RightBackMotor.spinFor(forward, 300, deg, true);

    // wait(0.1, sec);

    // // drive back a little bit
    // LeftFrontMotor.spinFor(forward, -150, deg, false);
    // RightFrontMotor.spinFor(forward, -150, deg, false);
    // LeftMiddleMotor.spinFor(forward, -150, deg, false);
    // RightMiddleMotor.spinFor(forward, -150, deg, false);
    // LeftBackMotor.spinFor(forward, -150, deg, false);
    // RightBackMotor.spinFor(forward, -150, deg, true);

    // // turn to the elevation bar
    // turnPID(-80, 1);

    // // drive forward
    // LeftFrontMotor.spinFor(forward, 1600, deg, false);
    // RightFrontMotor.spinFor(forward, 1600, deg, false);
    // LeftMiddleMotor.spinFor(forward, 1600, deg, false);
    // RightMiddleMotor.spinFor(forward, 1600, deg, false);
    // LeftBackMotor.spinFor(forward, 1600, deg, false);
    // RightBackMotor.spinFor(forward, 1600, deg, true);

    // TESTING THE CODE WITH THE WEDGE AT THE FRONT
    // idk if the heading will change but we will need to try that.

    // code
    LeftFrontMotor.spin(reverse, 12, volt);
    RightFrontMotor.spin(reverse, 12, volt);
    LeftMiddleMotor.spin(reverse, 12, volt);
    RightMiddleMotor.spin(reverse, 12, volt);
    LeftBackMotor.spin(reverse, 10, volt);
    RightBackMotor.spin(reverse, 12, volt);

    // wait for the robot to ram the triball in the goal
    wait(0.7, sec); // 1.l2 for ram

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

    // other
    LeftFrontMotor.spin(forward, 12, volt);
    RightFrontMotor.spin(forward, 12, volt);
    LeftMiddleMotor.spin(forward, 12, volt);
    RightMiddleMotor.spin(forward, 12, volt);
    LeftBackMotor.spin(forward, 10, volt);
    RightBackMotor.spin(forward, 12, volt);

    // wait for the robot to ram the triball in the goal
    wait(0.3, sec); // 1.l2 for ram

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
}