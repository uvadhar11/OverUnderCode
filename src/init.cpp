// VARIABLE DEFINITIONS FOR THE GLOBAL VARIABLES
#include "vex.h"
#include "init.h"
#include <string> // include the string library

using namespace vex;

// Initializing the Brain
brain Brain = brain();

// Initializing the Controller
controller Controller1 = controller();

// INITALIZING MOTORS
// assuming intake is the font
motor LeftFrontMotor = motor(PORT11, ratio6_1, true);
motor LeftMiddleMotor = motor(PORT12, ratio6_1, true);
motor LeftBackMotor = motor(PORT13, ratio6_1, true);
motor RightFrontMotor = motor(PORT1, ratio6_1, false);
motor RightMiddleMotor = motor(PORT2, ratio6_1, false);
motor RightBackMotor = motor(PORT3, ratio6_1, false);
motor IntakeFlywheelMotor = motor(PORT9, ratio6_1, false);
motor LiftMotor = motor(PORT8, ratio36_1, false);

// INITALIZING SENSORS
inertial Inertial = inertial(PORT7);

// INITIALIZING PISTONS
// digital_out LeftPiston = digital_out(Brain.ThreeWirePort.A);
led LeftWing = led(Brain.ThreeWirePort.B);
led RightWing = led(Brain.ThreeWirePort.C);

// GLOBAL VARIABLES
// (type specifier needed for all these declarations here)
// autonomous selection
int autonSelected = 0;              // default auton
std::string allianceColor = "NONE"; // default alliance color

int rectWidth = 240;        // left-right
int rectLength = 70;        // up-down
int autonButtonsStart = 60; // this will be the red/blue button size

// use x coordinate for drawing rectangle and NOT for pressing since 2 coordinates are 0!!!
autonRects auton1Rect = {0, 60, rectWidth, rectLength};
autonRects auton2Rect = {240, 60, rectWidth, rectLength};
autonRects auton3Rect = {0, 130, rectWidth, rectLength};
autonRects auton4Rect = {240, 130, rectWidth, rectLength};

// alliance color selection
int colorWidth = 80;  // left-right
int colorLength = 40; // up-down

colorRects redButton = {200, 10, colorWidth, colorLength};
colorRects blueButton = {220 + colorWidth, 10, colorWidth, colorLength};