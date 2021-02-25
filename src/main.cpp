/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         9               
// leftBack             motor         2               
// rightFront           motor         10              
// rightBack            motor         1               
// imu                  inertial      8               
// encoderRight         encoder       E, F            
// encoderLeft          encoder       G, H            
// Controller1          controller                    
// intakeLeft           motor         19              
// intakeRight          motor         18              
// rollerTop            motor         11              
// rollerBottom         motor         12              
// opticalMiddle        optical       17              
// distanceTop          distance      16              
// distanceBottom       distance      14              
// distanceMiddle       distance      15              
// leftLimit            limit         B               
// rightLimit           limit         A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

//DRIVE
#include "drive/drive.h"
#include "drive/odom.h"
//#include "drive/vision.h"
#include "drive/visiontt.h"

//SCREEN
#include "screen/screen_functions.h"
#include "screen/pong_utilities.h"

//ROLLERS & INTAKES
#include "rollers_intakes.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

const int autonCnt = 5;
int autonType = 0;
bool aColor = true; //true = blue; false = red;
bool side = true; //true = left; false = right;
std::string autonLeft[autonCnt] = {"none", "1 goal (home)", "2 goals (home)", "mid goal", "dominate"};
std::string autonRight[autonCnt] = {"none", "1 goal (home)", "2 goals (home)", "side goal", "ha"};

bool aColorButtonPressed = false;
bool sideButtonPressed = false;
bool autonTypeButtonPressed = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  imu.calibrate();
  wait(2000, msec);

  while(true){
    //Alliance color button
    Button alliance(10, 10, 100, 220, aColor ? blue : red, aColor ? "blue" : "red");
    alliance.generateButton();
    //Side button
    Button s(120, 10, 100, 220, side ? ClrLightSeaGreen : ClrLightGreen, side ? "left" : "right");
    s.generateButton();
    //Auton type button
    Button a(230, 10, 200, 220, ClrAquamarine, side ? autonLeft[autonType] : autonRight[autonType]);
    a.generateButton();

    //Alliance color button toggle
    if(alliance.isPressed() && !aColorButtonPressed){
      aColor = !aColor;
      aColorButtonPressed = true;
    }
    if(!alliance.isPressed()) aColorButtonPressed = false;

    //Side button toggle
    if(s.isPressed() && !sideButtonPressed){
      side = !side;
      sideButtonPressed = true;
    }
    if(!s.isPressed()) sideButtonPressed = false;

    //Auton type toggle
    if(a.isPressed() && !autonTypeButtonPressed){
      autonType++;
      autonTypeButtonPressed = true;
      if(autonType == autonCnt){
        autonType = 0;
      }
    }
    if(!a.isPressed()) autonTypeButtonPressed = false;

    wait(50, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool ASTonishingA = false;
bool ASTonishingB = false;
bool ASTonishingC = false;
bool ASTonishingD = false;

bool dominationA = false;
bool dominationB = false;

int odometry(){
  while(true){
    updateEncoders();
    updatePosition();
    Brain.Screen.printAt(1, 20, "X: %f", XPos);
    Brain.Screen.printAt(1, 40, "Y: %f", YPos);
    Brain.Screen.printAt(1, 60, "Rotation: %f", currentAngle);
    Brain.Screen.printAt(1, 80, "Left Encoder: %f", encoderLeft.rotation(deg));
    Brain.Screen.printAt(1, 100, "Right Encoder: %f", encoderRight.rotation(deg));
    this_thread::sleep_for(5);
  }
  return(0);
}

int ballz(){
  while(true){
    if(ASTonishingA){
      topPoop(600);
      ASTonishingA = false;
      setRollers(0, 0);
      setIntakes(-600, -600); //wait(400, msec); setIntakes(0, 0);
    }

    if(ASTonishingB){
      setIntakes(600, 600);
      topPoop(600);
      ASTonishingB = false;
    }

    if(dominationA){
      descore(2, true);
      //score(1, true);
      //descore(1, true);
      dominationA = false;
    }

    if(dominationB){
      setRollers(-100, 0); setIntakes(-600, -600); wait(400, msec); setRollers(0, 0); setIntakes(0, 0);
      dominationB = false;
    }
    this_thread::sleep_for(5);
  }
  return(0);
}

void nothing(){}

void McBigMac(){
  //1ST GOAL
  score(2, false); 
  descore(2, true);
  setIntakes(200, 200);
  setDriveVelocity(100, 100);
  score(1, false);
  ASTonishingA = true;
  wait(50, msec);
}

void McCheeseburger(){
  descore(2, true);
  score(1, false);
  setRollers(0, 600);
  wait(150, msec);
}

void homerow_oneGoal(){
  setDriveVelocity(220, 400); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(80, 300); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(50, msec);
  score(2, true); //changed to true
  wait(100, msec);
  descore(2, true);/////
  //setRollers(-300, -300); wait(200, msec); 
  setRollers(600, 600); wait(700, msec); setRollers(0, 0); 
  ASTonishingA = true;

  setIntakes(600, 600); setDriveVelocity(100, 100);
  wait(75, msec);
  moveFor(-200, -200, 600); 
  wait(500, msec);
  spinTo(90, 3.5);
}

void homerow_twoGoals(){
  setDriveVelocity(220, 400); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(80, 300); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(50, msec);
  score(2, true); //changed to true
  wait(100, msec);
  descore(2, true);/////
  //setRollers(-300, -300); wait(200, msec); 
  setRollers(600, 600); wait(700, msec); setRollers(0, 0); 
  ASTonishingA = true;
  //McBigMac();

  //AFTER 1ST GOAL
  setIntakes(600, 600); setDriveVelocity(200, 200);///////
  wait(75, msec);
  moveToCurve_rear(-4.9, -41.0, 6, 12); //changed
  spinTo(270, 3.75);
  
  //RESET
  resetOdom();

  //2ND GOAL
  //visionTrack(175, 0.5, 3, 69);
  moveFor(200, 240, 900);
  setIntakes(250, 250); score(1, false); setIntakes(0, 0); setRollers(0, 0);//changed score false
  wait(200, msec);
  //McCheeseburger();
  
  //AFTER 2ND GOAL
  moveFor(-300, -300, 600);
  ASTonishingB = true;
  spinTo(270, 3.5); 
}

void midGoal(){
  setDriveVelocity(220, 400); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(80, 300); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(50, msec);
  score(2, true); //changed to true
  wait(100, msec);
  descore(2, true);/////
  //setRollers(-300, -300); wait(200, msec); 
  setRollers(600, 600); wait(700, msec); setRollers(0, 0); 
  ASTonishingA = true;

  setIntakes(600, 600); setDriveVelocity(100, 100);
  //wait(150, msec);
  moveFor(-200, -200, 500);
  wait(50, msec);
  spinTo(90, 4.0);

  setIntakes(600, 600);
  moveTo_slew(46.0, -4.45, 5, 14, true);
  setIntakes(600, 600);
  setRollers(50, 0);
  moveFor(-200, -200, 500);
  moveTo_slew(30.00, -38.0, 4.5, 17, false);
  spinTo(90.0, 3.5);

  wait(200, msec);

  setIntakes(-600, -600);
  moveFor(305, 300, 1050);
  setIntakes(-600, -600);
  setDriveVelocity(-75, -75);
  score(1, true);

}

void rightOne(){
  //1ST GOAL
  setDriveVelocity(400, 220); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(300, 80); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(50, msec);
  score(2, true); //changed to true
  wait(100, msec);
  descore(2, true);/////
  //setRollers(-300, -300); wait(200, msec); 
  setRollers(600, 600); wait(700, msec); setRollers(0, 0); 
  ASTonishingA = true;

  

  

  setIntakes(300, 300);
  moveFor(-200, -200, 600);
  wait(500, msec);
  spinTo(270, 3.5);
}

void rightTwo(){
  //1ST GOAL
  setDriveVelocity(400, 220); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(300, 80); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(50, msec);
  score(2, true); //changed to true
  wait(100, msec);
  descore(2, true);/////
  //setRollers(-300, -300); wait(200, msec); 
  setRollers(600, 600); wait(700, msec); setRollers(0, 0); 
  ASTonishingA = true;

  //AFTER 1ST GOAL
  setIntakes(300, 300);
  moveToCurve_rear(4.9, -45.0, 6, 12);
  spinToRear(270, 3.75);
  
  //RESET
  resetOdom();

  //2ND GOAL
  //visionTrack(175, 0.5, 3, 69);
  moveFor(440, 300, 800);
  //setIntakes(250, 250); score(1, false); setIntakes(0, 0); setRollers(0, 0);
  //wait(200, msec);
  McCheeseburger();
  
  //AFTER 2ND GOAL
  moveFor(-300, -300, 600);
  ASTonishingB = true;
  spinTo(270, 3.5); 
}

void sideGoal(){
  //1ST GOAL
  setDriveVelocity(400, 220); setIntakes(600, 600); wait(600, msec); setDriveVelocity(0, 0); 
  setDriveVelocity(300, 80); wait(200, msec); setDriveVelocity(0, 0); setIntakes(0, 0);
  wait(100, msec);
  score(1, true);
  wait(100, msec);
  descore(2, true);
  setRollers(600, 600); wait(800, msec); setRollers(0, 0); 
  ASTonishingA = true;

  moveFor(-200, -200, 600);
  wait(500, msec);
  spinTo(270, 3.5);

  resetOdom();

  moveTo_slew(0, 28, 5, 12, true);
  spinTo(35, 3.75);

  setIntakes(600, 600);
  moveFor(300, 300, 800); wait(500, msec);
  moveFor(-300, -300, 500); setRollers(600, -300); wait(500, msec);
  moveFor(340, 300, 600); score(1, true); wait(500, msec);
  moveFor(-300, -300, 500); wait(300, msec);
  moveFor(350, 300, 600); setIntakes(600, 600); wait(500, msec); moveFor(-300, -300, 500); setIntakes(0, 0);
}

void domination(color ac){
  moveTo_slew(0, 32.0, 5, 14, true);
  spinTo(281, 3.8);

  setIntakes(600, 600);
  dominationA = true;
  moveFor(500, 500, 1000);
  //setRollers(0, 600);
  //setIntakes(600, 600);
  score(1, false); wait(50, msec);
  setRollers(0, -250);
  //descore(1, true);
  setIntakes(600, 600);
  //setDriveVelocity(-200, -200); wait(400, msec); setIntakes(600, 600); setDriveVelocity(250, 250); wait(800, msec); setIntakes(600, 600); setDriveVelocity(0, 0);
  
  wait(600, msec);
  setRollers(0, -300); //setIntakes(-400, -400);
  setIntakes(300, 300);
  wait(500, msec);
  setIntakes(200, 200);
  moveFor(-300, -300, 500); 

  spinTo(323, 3.75);
  dominationB = true;

  wait(200, msec);
  resetOdom();
  if((opticalMiddle.color() == red && ac == blue) || (opticalMiddle.color() == blue && ac == red)){
    setIntakes(-600, -600); setRollers(-600, -600);
  } else {
    moveTo_slew(15, -41.0, 5, 16, false);
    spinTo(90, 3.75);
  }
  setIntakes(600, 600);
  moveFor(375, 300, 1100);
  setDriveVelocity(-50, -50);
  score(1, false);
}



void autonomous(void) {
  Brain.Screen.clearScreen();
  //imu.calibrate(); wait(2000, msec);
  thread t(odometry);
  thread t2(ballz);
  setDriveBrakeType("brake");

  opticalMiddle.setLightPower(100, pct);opticalMiddle.setLight(ledState::on);
  deploy();

  
  if(aColor){ //blue
    allianceColor = true;
  } else {
    allianceColor = false;
  }

  

  if(side){ //left
    switch(autonType){
      case 0:
      nothing();
      break;

      case 1:
      homerow_oneGoal();
      break;

      case 2: 
      homerow_twoGoals();
      break;

      case 3:
      midGoal();
      break;

      case 4: 
      if(allianceColor){
        domination(blue);
      } else {
        domination(red);
      }
      break;
    }
  } else {
    switch(autonType){
      case 0:
      nothing();
      break;

      case 1:
      rightOne();
      break;

      case 2: 
      rightTwo();
      break;

      case 3:
      sideGoal();
      break;
    }
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  //imu.calibrate(); wait(2000, msec);
  //thread t(odometry);
  setDriveBrakeType("coast");
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0); Controller1.Screen.print("Ryan pp smol");
  
  while (true) {
    opControl();
    opControl_rollerIntakes();
    
    //Controller1.Screen.setCursor(2, 0); Controller1.Screen.print;
    //Controller1.Screen.setCursor(3, 0); Controller1.Screen.print(leftFront.temperature(temperatureUnits::celsius) >= 55 ? "Too Hot" : "Good");
    //Controller1.Screen.setCursor(2, 5); Controller1.Screen.print(leftFront.temperature(temperatureUnits::celsius) >= 55 ? "Too Hot" : "Good");
    //Controller1.Screen.setCursor(2, 0); Controller1.Screen.print(leftFront.temperature(temperatureUnits::celsius) >= 55 ? "Too Hot" : "Good");

    wait(5, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
