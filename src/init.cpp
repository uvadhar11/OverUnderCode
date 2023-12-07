// VARIABLE DEFINITIONS FOR THE GLOBAL VARIABLES
#include "vex.h"
#include "init.h"

using namespace vex;

// Initializing the Brain
brain Brain = brain();

// Initializing the Controller
controller Controller1 = controller(); 

// Initializing the Drivetrain Motors - All motors are spinning forward
motor LeftFrontMotor = motor(PORT10, ratio6_1, true);
motor LeftBackMotor = motor(PORT9, ratio6_1, true);
motor RightFrontMotor = motor(PORT6, ratio6_1, false);
motor RightBackMotor = motor(PORT7, ratio6_1, false);
