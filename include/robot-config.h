using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftFront;
extern motor leftBack;
extern motor rightFront;
extern motor rightBack;
extern inertial imu;
extern encoder encoderRight;
extern encoder encoderLeft;
extern controller Controller1;
extern motor intakeLeft;
extern motor intakeRight;
extern motor rollerTop;
extern motor rollerBottom;
extern optical opticalMiddle;
extern distance distanceTop;
extern distance distanceBottom;
extern distance distanceMiddle;
extern limit leftLimit;
extern limit rightLimit;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );