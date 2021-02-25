#include "vex.h"
#include "drive/odom.h"
#include "drive/drive.h"

using namespace vex;

//BOT TRACK
double track = 5.5; //inches

//CURRENT SENSOR VALUES
double currentL = 0.0;
double currentR = 0.0;
double currentAngle = 0.0;

//PREVIOUS SENSOR VALUES
double prevL = 0.0;
double prevR = 0.0;
double prevAngle = 0.0;

//CHANGE IN SENSOR VALUES
double deltaL = 0.0;
double deltaR = 0.0;
double deltaAngle = 0.0;

//CHANGE IN POLAR/CARTESIAN
double localDeltaX = 0.0;
double localDeltaY = 0.0;
double globalDeltaX = 0.0;
double globalDeltaY = 0.0;

//PREVIOUS POLAR COORDINATES
double prevLocalX = 0.0;
double prevLocalY = 0.0;

//CURRENT CARTESIAN COORDINATES
double XPos = 0.0;
double YPos = 0.0;

//ODOMETRY FUNCTIONS
void updateEncoders(){
  currentL = degToInch(encoderLeft.rotation(deg));
  currentR = degToInch(encoderRight.rotation(deg));
  currentAngle = -(currentR - currentL) / track;

  deltaL = currentL - prevL;
  deltaR = currentR - prevR;
  deltaAngle = currentAngle - prevAngle;

  prevL = currentL;
  prevR = currentR;
  prevAngle = currentAngle;
}

void updatePosition(){  
  double localY = (currentL + currentR) / 2;
  //double localX = (currentImuAngle - (deltaAngle * backEncoderToRotationRatio));
  //double robotRotation = getRadians(imu.heading());

  localDeltaY = localY - prevLocalY;
  //localDeltaX = localX - prevLocalX;

  /*globalDeltaY = (localDeltaY * cos(getRadians(robotRotation)) + localDeltaX * sin(getRadians(robotRotation)));
  globalDeltaX = (localDeltaX * cos(getRadians(robotRotation)) - localDeltaY * sin(getRadians(robotRotation)));*/
  globalDeltaY = cos(currentAngle) * localDeltaY;
  globalDeltaX = sin(currentAngle) * localDeltaY;

  //globalDeltaX *= -1;

  YPos += globalDeltaY;
  XPos += globalDeltaX;

  prevLocalY = localY;
  //prevLocalX = localX;
  //wait(20, msec);
}

void resetOdom(){
  XPos = 0.0; YPos = 0.0; prevL = 0.0; prevR = 0.0;
  encoderLeft.resetRotation(); encoderRight.resetRotation();
  currentAngle = 0.0; prevAngle = 0.0;
  prevLocalY = 0.0; localDeltaY = 0.0;
  imu.resetRotation();
}