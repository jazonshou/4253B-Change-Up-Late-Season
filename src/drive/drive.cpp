#include "vex.h"
#include "drive/drive.h"
#include "drive/odom.h"

using namespace vex;

int feedforward = 100;

//DRIVE FUNCTIONS
void setDriveVelocity(int left, int right){
  leftFront.spin(fwd, left, rpm);
  leftBack.spin(fwd, left, rpm);
  rightFront.spin(fwd, right, rpm);
  rightBack.spin(fwd, right, rpm);
}

void setDriveVoltage(double left, double right){
  leftFront.spin(fwd, left, voltageUnits::volt);
  leftBack.spin(fwd, left, voltageUnits::volt);
  rightFront.spin(fwd, right, voltageUnits::volt);
  rightBack.spin(fwd, right, voltageUnits::volt);
}

void setDriveBrakeType(std::string brake){
  if(brake == "coast"){
    leftFront.setStopping(brakeType::coast);
    leftBack.setStopping(brakeType::coast);
    rightFront.setStopping(brakeType::coast);
    rightBack.setStopping(brakeType::coast);
  }
  if(brake == "brake"){
    leftFront.setStopping(brakeType::brake);
    leftBack.setStopping(brakeType::brake);
    rightFront.setStopping(brakeType::brake);
    rightBack.setStopping(brakeType::brake);
  }
  if(brake == "hold"){
    leftFront.setStopping(brakeType::hold);
    leftBack.setStopping(brakeType::hold);
    rightFront.setStopping(brakeType::hold);
    rightBack.setStopping(brakeType::hold);
  }
}

void translate(double inches, int rpm){
  double dist = inchToDeg(inches);
  while(dist < avgEncoder()){
    setDriveVelocity(rpm, rpm);
    wait(10, msec);
  }
}

void moveFor(int leftSpeed, int rightSpeed, int time){
  setDriveVelocity(leftSpeed, rightSpeed);
  wait(time, msec);
  setDriveVelocity(0, 0);
}



void spinTo(double desiredHeading, double kP){
  //imu.resetRotation();
  double heading2 = (desiredHeading < 0) ? desiredHeading + 360 : desiredHeading - 360;
	desiredHeading = (fabs(imu.rotation() - desiredHeading) < fabs(imu.rotation() - heading2)) ? desiredHeading : heading2;
  int dir = abs((int)desiredHeading - (int)imu.rotation()) / (int)desiredHeading - (int)imu.rotation();
	double imu_error = 0.0;
  while(true){
    imu_error = (desiredHeading - imu.rotation()) * kP;
  
    setDriveVelocity(imu_error, -imu_error);

    Brain.Screen.printAt(1, 120, "Imu_error %f", imu_error);
    Brain.Screen.printAt(1, 140, "dir %d", dir);
    
    if(fabs(imu_error) < 2) break; 
    wait(5, msec);
  }
  setDriveVelocity(0, 0);
}

void spinToRear(double desiredHeading, double kP){
  //imu.resetRotation();
  int theta = 180;
  double heading2 = (desiredHeading < 0) ? desiredHeading + 360 : desiredHeading - 360;
	desiredHeading = (fabs(theta - desiredHeading) < fabs(theta - heading2)) ? desiredHeading : heading2;
  int dir = abs((int)desiredHeading - theta) / ((int)desiredHeading - theta);
	double imu_error = 0.0;
  while(true){
    imu_error = -(desiredHeading - (imu.rotation() + 180)) * kP;
    setDriveVelocity(-imu_error, imu_error);

    Brain.Screen.printAt(1, 100, "Imu_error %f", imu_error);
    Brain.Screen.printAt(1, 140, "dir %d", dir);

    if(fabs(imu_error) < 2) break; 
    wait(5, msec);
  }
  setDriveVelocity(0, 0);
}

void moveTo(double x, double y, double turn_kP, double move_kP, bool front_rear){
  double leftEnc = 0.0; double rightEnc = 0.0;
  double changeX = x - XPos; double changeY = y - YPos;
  double theta = getDegrees(spitDesiredHeading(changeY, changeX)); double dist = sqrt((changeX*changeX) + (changeY*changeY));
  double error = 0.0; double pow = 0.0;
  //turn
  if(front_rear) spinTo(theta, turn_kP);
  else spinToRear(theta, turn_kP);

  //fwd movement
  while(true){
    leftEnc += deltaL; rightEnc += deltaR;
    error = front_rear ? dist - ((leftEnc + rightEnc) / 2) : dist + ((leftEnc + rightEnc) / 2);
    pow = front_rear ? error * move_kP : -(error * move_kP);
    //pow = error * move_kP;
    if(fabs(pow) < feedforward) pow = front_rear ? feedforward : -feedforward;
    //if((front_rear && error >= 0) || (!front_rear && error <= 0)) break;
    if(fabs(error) < 2) break;

    setDriveVelocity(pow, pow);
    wait(5, msec);
  }
  setDriveVelocity(0, 0); 
}

void moveTo_slew(double x, double y, double turn_kP, double move_kP, bool front_rear){
  double leftEnc = 0.0; double rightEnc = 0.0;
  double changeX = x - XPos; double changeY = y - YPos;
  double theta = getDegrees(spitDesiredHeading(changeY, changeX)); double dist = sqrt((changeX*changeX) + (changeY*changeY));
  double error = 0.0; double pow = 0.0;
  //turn
  if(front_rear) spinTo(theta, turn_kP);
  else spinToRear(theta, turn_kP);

  //fwd movement
  while(true){
    leftEnc += deltaL; rightEnc += deltaR;
    error = front_rear ? dist - ((leftEnc + rightEnc) / 2) : dist + ((leftEnc + rightEnc) / 2);
    pow = front_rear ? error * move_kP : -(error * move_kP);
    //pow = error * move_kP;
    if(fabs(pow) < feedforward) pow = front_rear ? feedforward : -feedforward;
    //if((front_rear && error >= 0) || (!front_rear && error <= 0)) break;
    if(fabs(error) < 2) break;

    slew(pow, pow);
    wait(5, msec);
  }
  setDriveVelocity(0, 0); 
}

void moveToCurve(double x, double y, double turn_kP, double move_kP){
  //imu.resetRotation();

  double leftEnc = 0.0; double rightEnc = 0.0;
  double error = 0.0; double imu_error = 0;

  double turnPow = 0.0; double movePow = 0.0;
  double leftPow = 0.0; double rightPow = 0.0;
  double changeX = x - XPos; double changeY = y - YPos;

  while(true){
    leftEnc += deltaL; rightEnc += deltaR;
    double theta = getDegrees(spitDesiredHeading(changeY, changeX)); double dist = sqrt((changeX*changeX) + (changeY*changeY));
    double heading2 = (theta < 0) ? theta + 360 : theta - 360;
	  theta = (fabs(imu.rotation() - theta) < fabs(imu.rotation() - heading2)) ? theta : heading2;

    imu_error = theta - imu.rotation();
    error = dist - ((leftEnc + rightEnc) / 2);

    turnPow = imu_error * turn_kP; movePow = error * move_kP;
    leftPow = movePow + turnPow; rightPow = movePow - turnPow;
    if(fabs(movePow) < feedforward) movePow = feedforward;

    if(error < 2 && imu_error < 1) break;

    //if(imu.rotation() >= imu_error && avgEncoder() >= dist) break;
    Brain.Screen.printAt(1, 140, "cx: %f", changeX);
    Brain.Screen.printAt(1, 160, "cy: %f", changeY);

    setDriveVelocity(leftPow, rightPow);
    wait(5, msec);
  }
  setDriveVelocity(0, 0);
}

void moveToCurve_rear(double x, double y, double turn_kP, double move_kP){
  //imu.resetRotation();

  double leftEnc = 0.0; double rightEnc = 0.0;
  double error = 0.0; double imu_error = 0;

  double turnPow = 0.0; double movePow = 0.0;
  double leftPow = 0.0; double rightPow = 0.0;
  double changeX = x - XPos; double changeY = y - YPos;

  while(true){
    leftEnc += deltaL; rightEnc += deltaR;
    double theta = getDegrees(spitDesiredHeading(changeY, changeX)); double dist = sqrt((changeX*changeX) + (changeY*changeY));
    int theta2 = 180;
    double heading2 = (theta < 0) ? theta + 360 : theta - 360;
  	theta = (fabs(theta2 - theta) < fabs(theta2 - heading2)) ? theta : heading2;

    
    
    imu_error = -(theta - (imu.rotation() + 180));
    error = dist + ((leftEnc + rightEnc) / 2);

    turnPow = imu_error * turn_kP; movePow = error * move_kP; if(fabs(movePow) < feedforward) movePow = feedforward;
    leftPow = -movePow - turnPow; rightPow = -movePow + turnPow;

    if(fabs(error) < 2 && fabs(imu_error) < 1) break;

    Brain.Screen.printAt(1, 140, "dist: %f", dist);
    Brain.Screen.printAt(1, 180, "enc: %f", (leftEnc + rightEnc) / 2);

    setDriveVelocity(leftPow, rightPow);
    wait(5, msec);
  }
  setDriveVelocity(0, 0);
}

//SLEW
const int accel_step = 6;
const int deccel_step = 256; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void slew(int leftTarget, int rightTarget){
  int step;

  if(abs(leftSpeed) < abs(leftTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(leftTarget > leftSpeed + step)
    leftSpeed += step;
  else if(leftTarget < leftSpeed - step)
    leftSpeed -= step;
  else
    leftSpeed = leftTarget;

  
  if(abs(rightSpeed) < abs(rightTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(rightTarget > rightSpeed + step)
    rightSpeed += step;
  else if(rightTarget < rightSpeed - step)
    rightSpeed -= step;
  else
    rightSpeed = rightTarget;

  setDriveVelocity(leftSpeed, rightSpeed);
}

//DRIVER CONTROL FUNCTIONS
void opControl(){
  double left = ((double)Controller1.Axis3.position() / 100) * 12;
  double right = ((double)Controller1.Axis2.position() / 100) * 12;

  //if(abs(left) < 2) {left = 0;}
  //if(abs(right) < 2) {right = 0;}
  Brain.Screen.printAt(1, 20, "left %f", left);
  Brain.Screen.printAt(1, 40, "right %f", right);

  setDriveVoltage(left, right);
}

//SENSOR FUNCTIONS
double avgEncoder(){
  return (encoderLeft.rotation(deg) + encoderRight.rotation(deg)) / 2;
}

void resetEnc(){
  encoderLeft.resetRotation(); encoderRight.resetRotation();
}

//MATH FUNCTIONS
double getRadians(double deg){
  return (deg * M_PI) / 180;
}

double getDegrees(double radians){
  return radians * (180/M_PI);
}

double degToInch(double deg){
  return (deg / 360) * (M_PI * 2.75);
}

double inchToDeg(double inch){
  return (inch / (M_PI * 2.75)) * 360;
}

float map(float value, float istart, float istop, float ostart, float ostop){
  return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

double distanceFormula(double x1, double y1, double x2, double y2){
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

double spitDesiredHeading(double cx, double cy){
  return ((cx > 0 && cy > 0) || (cx < 0 && cy > 0)) ? atan2(cy, cx) : atan2(cy, cx) + (2 * M_PI);
}