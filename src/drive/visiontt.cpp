#include "vex.h"
#include "drive/drive.h"
#include "drive/vision.h"
#include "drive/visiontt.h"

//MACROS
int VISION_FOV_WIDTH = 316;
int VISION_FOV_HEIGHT = 212;

//VISION FUNCTIONS
void visionTrack(int idealHeight, double turn_kP, double move_kP, double move_kD){
  double center = VISION_FOV_WIDTH * 0.5;
  double prevLateralPower = 0, derivative = 0;
  while(Vision1.largestObject.height < idealHeight){
    Vision1.takeSnapshot(SIG_1);
    if(Vision1.largestObject.exists){
      double turnPower = (center - Vision1.largestObject.centerX) * turn_kP;
      double lateralPower = (idealHeight - Vision1.largestObject.height);

      derivative = lateralPower - prevLateralPower;
      prevLateralPower = lateralPower;

      double translate = lateralPower * move_kP /*+ derivative * move_kD*/;

      setDriveVelocity(translate + turnPower, translate - turnPower);
    }
    wait(10, msec);
  }
  setDriveVelocity(0, 0);
  setDriveVelocity(150, 150); wait(250, msec); setDriveVelocity(0, 0);
}

void visionTurn(){
  Vision1.takeSnapshot(SIG_1);
  if(Vision1.largestObject.exists){
    double xMid = Vision1.largestObject.originX + (Vision1.largestObject.width/2);
    int maxWidth = 316; int center = maxWidth/2;
    double power = (center - xMid)/2;
    setDriveVelocity(power, -power);
  }
}