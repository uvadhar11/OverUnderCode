// WILL INCLUDE THE SIGNATURES FOR FUNCTIONS AND STUFF
#pragma once

// AUTONOMOUS SELECTION FUNCTIONS
void initalizeAutonSelector();
void initalizeAllianceColorSelector();
void autonScreenSelector();

// AUTONOMOUS FUNCTIONS
void auton1();
void auton2();
void auton3();
void auton4();

// DRIVE PID FUNCTIONS
void drivePID(int desiredValue, double multiplier);
void drivePID(int desiredValue, double multiplier, bool intakeWhile);
void turnPID(int desiredValue, double multiplier);
