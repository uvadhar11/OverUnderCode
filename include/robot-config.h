using namespace vex;

// Initalizing the brain
extern brain Brain;

// Initializing the controller
extern controller Controller1;

// VEXcode devices
// Declaring Motors
extern vex::motor LeftFrontMotor;
extern vex::motor LeftMiddleMotor;
extern vex::motor LeftBackMotor;
extern vex::motor RightFrontMotor;
extern vex::motor RightMiddleMotor;
extern vex::motor RightBackMotor;
extern vex::motor IntakeFlywheelMotor;
extern vex::motor LiftMotor;
extern vex::motor KickerMotor2;
extern vex::motor KickerMotor;

// Declaring Sensors
extern vex::inertial Inertial;
extern vex::rotation KickerRotation;

// Declaring Pistons
extern vex::led LeftWing;
extern vex::led RightWing;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);