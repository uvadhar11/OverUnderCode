#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors

// VEXcode generated functions
motor LeftFrontMotor = motor(PORT11, ratio6_1, true); // l: true
motor LeftMiddleMotor = motor(PORT12, ratio6_1, true);
motor LeftBackMotor = motor(PORT13, ratio6_1, true);
motor RightFrontMotor = motor(PORT1, ratio6_1, false);
motor RightMiddleMotor = motor(PORT2, ratio6_1, false);
motor RightBackMotor = motor(PORT3, ratio6_1, false);
motor IntakeFlywheelMotor = motor(PORT10, ratio6_1, false);
motor LiftMotor = motor(PORT8, ratio36_1, false);
inertial Inertial = inertial(PORT7);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}