#include "vex.h"
#include <string> // include the string library
// globals.h is included in vex.h so no need to incude it again

// GLOBAL VARIABLES
// (type specifier needed for all these declarations here)

// driver control
bool rightWingEnabled = false;
bool leftWingEnabled = false;
bool bothWingsEnabled = false;
bool intakePistonEnabled = false;

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