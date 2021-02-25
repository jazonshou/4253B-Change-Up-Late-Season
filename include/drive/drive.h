#include "vex.h"

extern int feedforward;

//DRIVE FUNCTIONS
//helper functions
void setDriveVelocity(int left, int right);
void setDriveVoltage(double left, double right);
void setDriveBrakeType(std::string brake);
void translate(double inches, int rpm);
void moveFor(int leftSpeed, int rightSpeed, int time);
void moveFor_slew(int leftSpeed, int rightSpeed, int time);
//turn functions
void spinTo(double imuHeading, double kP);
void spinToRear(double desiredHeading, double kP);
//move functions
void moveTo(double x, double y, double turn_kP, double move_kP, bool front_rear);
void moveTo_slew(double x, double y, double turn_kP, double move_kP, bool front_rear);
void moveToCurve(double x, double y, double turn_kP, double move_kP);
void moveToCurve_rear(double x, double y, double turn_kP, double move_kP);

//SLEW
void slew(int leftTarget, int rightTarget);

//DRIVER CONTROL FUNCTIONS
void robotCentricDrive();
void fieldCentricDrive();
void opControl();

//SENSOR FUNCTIONS
double avgEncoder();
void resetEnc();

//MATH FUNCTIONS
double getRadians(double deg);
double getDegrees(double radians);
double degToInch(double deg);
double inchToDeg(double inch);
float map(float value, float istart, float istop, float ostart, float ostop);
double distanceFormula(double x1, double y1, double x2, double y2);
double spitDesiredHeading(double cx, double cy);