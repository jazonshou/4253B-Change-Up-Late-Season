#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT9, ratio6_1, true);
motor leftBack = motor(PORT2, ratio6_1, true);
motor rightFront = motor(PORT10, ratio6_1, false);
motor rightBack = motor(PORT1, ratio6_1, false);
inertial imu = inertial(PORT8);
encoder encoderRight = encoder(Brain.ThreeWirePort.E);
encoder encoderLeft = encoder(Brain.ThreeWirePort.G);
controller Controller1 = controller(primary);
motor intakeLeft = motor(PORT19, ratio6_1, true);
motor intakeRight = motor(PORT18, ratio6_1, false);
motor rollerTop = motor(PORT11, ratio6_1, true);
motor rollerBottom = motor(PORT12, ratio6_1, false);
optical opticalMiddle = optical(PORT17);
distance distanceTop = distance(PORT16);
distance distanceBottom = distance(PORT14);
distance distanceMiddle = distance(PORT15);
limit leftLimit = limit(Brain.ThreeWirePort.B);
limit rightLimit = limit(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}