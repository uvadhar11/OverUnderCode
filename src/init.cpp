// VARIABLE DEFINITIONS FOR THE GLOBAL VARIABLES
#include "vex.h"
#include "init.h"

using namespace vex;

// Initializing the Brain
brain Brain = brain();

// Initializing the Controller
controller Controller1 = controller(); 

// Initializing Motors
// assuming intake is the font
motor LeftFrontMotor = motor(PORT11, ratio6_1, true);
motor LeftMiddleMotor = motor(PORT12, ratio6_1, true);
motor LeftBackMotor = motor(PORT13, ratio6_1, true);
motor RightFrontMotor = motor(PORT1, ratio6_1, false);
motor RightMiddleMotor = motor(PORT2, ratio6_1, false);
motor RightBackMotor = motor(PORT3, ratio6_1, false);
motor IntakeFlywheelMotor = motor(PORT4, ratio6_1, false);
motor LiftMotor = motor(PORT8, ratio36_1, false);