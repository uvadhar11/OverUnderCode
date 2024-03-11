#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// Initializing the controller
controller Controller1 = controller();

// VEXcode device constructors

// VEXcode generated functions

// MOTORS
// OLD BOT
// motor LeftFrontMotor = motor(PORT11, ratio6_1, true); // l: true
// motor LeftMiddleMotor = motor(PORT12, ratio6_1, true);
// motor LeftBackMotor = motor(PORT13, ratio6_1, true);
// motor RightFrontMotor = motor(PORT1, ratio6_1, false);
// motor RightMiddleMotor = motor(PORT2, ratio6_1, false);
// motor RightBackMotor = motor(PORT3, ratio6_1, false);
// motor IntakeFlywheelMotor = motor(PORT19, ratio6_1, false);
// motor KickerMotor = motor(PORT17, ratio36_1, false);
// motor KickerMotor2 = motor(PORT5, ratio36_1, true);
// motor LiftMotor = motor(PORT8, ratio36_1, false);

// NEW BOT
motor LeftFrontMotor = motor(PORT11, ratio6_1, true);   // l: true
motor LeftMiddleMotor = motor(PORT20, ratio6_1, false); // f
motor LeftBackMotor = motor(PORT19, ratio6_1, true);    // t
motor RightFrontMotor = motor(PORT1, ratio6_1, false);
motor RightMiddleMotor = motor(PORT9, ratio6_1, true);
motor RightBackMotor = motor(PORT10, ratio6_1, false);
motor IntakeFlywheelMotor = motor(PORT14, ratio6_1, false);
motor KickerMotor = motor(PORT2, ratio36_1, true);
motor KickerMotor2 = motor(PORT8, ratio36_1, false);
motor LiftMotor = motor(PORT8, ratio36_1, false);

// SENSORS
inertial Inertial = inertial(PORT7);
rotation KickerRotation = rotation(PORT13);

// PISTONS
led IntakePiston = led(Brain.ThreeWirePort.H);
led LeftWing = led(Brain.ThreeWirePort.B);
led RightWing = led(Brain.ThreeWirePort.A);
led BalancePiston = led(Brain.ThreeWirePort.C);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}