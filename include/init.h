#pragma once // to make sure this file is only included once
// HEADER FILES FOR THE GLOBAL VARIABLES
using namespace vex;
#include <string>

// Declaring the Brain
extern vex::brain Brain;

// Declaring the Controller
extern vex::controller Controller1;

// Declaring the Drivetrain Motors
extern vex::motor LeftFrontMotor;
extern vex::motor LeftMiddleMotor;
extern vex::motor LeftBackMotor;
extern vex::motor RightFrontMotor;
extern vex::motor RightMiddleMotor;
extern vex::motor RightBackMotor;
extern vex::motor IntakeFlywheelMotor;
extern vex::motor LiftMotor;
extern vex::inertial Inertial;

// GLOBAL VARIABLES

// autonomous selection
extern int autonSelected;         // can set to a default auton if necessary
extern std::string allianceColor; // track alliance color

// defines the struct for use later
extern struct autonRects
{
    int xCoordinate;
    int yCoordinate;
    // width: left-right and length: up-down
    int rectWidth;  // this and below value is a default value for all instances of the stucture.
    int rectLength; // this and above represents the size of a rectangle, only thing that differs is screen position
};                  // auton1Rect, auton2Rect, auton3Rect, auton4Rect; // multiple variables storing an instance of this structure
extern int rectWidth;
extern int rectLength;
extern int autonButtonsStart;

// use x coordinate for drawing rectangle and NOT for pressing since 2 coordinates are 0!!!
extern autonRects auton1Rect; // makes the rects global to be accessed anywhere
extern autonRects auton2Rect;
extern autonRects auton3Rect;
extern autonRects auton4Rect;

// alliance color selection
extern int colorWidth;  // left-right
extern int colorLength; // up-down

extern struct colorRects
{
    int xCoordinate;
    int yCoordinate;
    int rectWidth;
    int rectLength;
};

extern colorRects redButton;
extern colorRects blueButton;