#pragma once // only include this file once
#include "vex.h"
#include <string> // include the string library

// GLOBAL VARIABLES

// driver control
// pneumatics
// extern bool rightWingEnabled;
// extern bool leftWingEnabled;
// extern bool bothWingsEnabled;
// extern bool intakePistonEnabled;

// autonomous selection
extern int autonSelected;         // can set to a default auton if necessary
extern std::string allianceColor; // track alliance color

// defines the struct for use later
struct autonRects
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
struct colorRects
{
    int xCoordinate;
    int yCoordinate;
    int rectWidth;
    int rectLength;
};

extern colorRects redButton;
extern colorRects blueButton;