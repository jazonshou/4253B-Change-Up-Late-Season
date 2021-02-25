#include "vex.h"
#include "rollers_intakes.h"

//blue = true, red = false
bool allianceColor = true;
bool badBallDetected = false;

//ROLLER & INTAKE FUNCTIONS
void setRollers(int bottom, int top){
  rollerBottom.spin(fwd, bottom, rpm);
  rollerTop.spin(fwd, top, rpm);
}
void setIntakes(int left, int right){
  intakeLeft.spin(fwd, left, rpm);
  intakeRight.spin(fwd, right, rpm);
}

//ROLLER & INTAKE AUTOMATION
void poop(){
  setRollers(600, -200);
  if(leftLimit.pressing() || rightLimit.pressing()){
    setRollers(600, 600);
  }
}

bool ballDetected = false;
void autoIndex(){
  opticalMiddle.setLightPower(100, percent);
  opticalMiddle.setLight(ledState::on);
  Brain.Screen.printAt(1, 120, "dist mid: %f", distanceMiddle.objectDistance(inches));
  //setRollers(600, 250);
  if((opticalMiddle.hue() < 15 && allianceColor == true) || (opticalMiddle.hue() > 200 && allianceColor == false)){
    badBallDetected = true;
  } 
  if(badBallDetected == true && (!leftLimit.pressing() || !rightLimit.pressing())){
    setRollers(600, -300);
  } 
  if(leftLimit.pressing() || rightLimit.pressing()){
    badBallDetected = false;
  }
  else {
    if(distanceTop.objectDistance(inches) < 1.5 && !ballDetected){
      setRollers(300, -100); wait(250, msec); setRollers(300, 0);
      ballDetected = true;
    } 
    if(distanceMiddle.objectDistance(inches) < 1.5 && distanceTop.objectDistance(inches) < 1.5){
        setRollers(0, 0);
    } else {
      if(!ballDetected) setRollers(600, 200);
    }
    if(distanceTop.objectDistance(inches) > 3){
      ballDetected = false;
    }
    //setRollers(600, 600);
  }
}

void shoot(){
  opticalMiddle.setLightPower(100, percent);
  opticalMiddle.setLight(ledState::on);
  Brain.Screen.printAt(1, 120, "dist mid: %f", distanceMiddle.objectDistance(inches));
  setRollers(400, 600);
  if((opticalMiddle.hue() < 15 && allianceColor == true) || (opticalMiddle.hue() > 200 && allianceColor == false)){
    badBallDetected = true;
  } 
  if(badBallDetected == true && (!leftLimit.pressing() || !rightLimit.pressing())){
    setRollers(450, -600);
  } 
  if(leftLimit.pressing() || rightLimit.pressing()){
    badBallDetected = false;
  }
  else {
    if(distanceTop.objectDistance(inches) < 1 && distanceMiddle.objectDistance(inches) < 1){
      setRollers(0, 600); wait(150, msec); setRollers(450, 600);
    }
    //setRollers(600, 600);
  }
}

void score(int balls, bool longShoot){
  bool boi = false;
  int cnt = 0;
  while(true){
    if(distanceTop.objectDistance(inches) <= 2 && boi == false){boi = true; cnt++;}

    if(distanceTop.objectDistance(inches) >= 2) {boi = false;}
    
    if(cnt >= balls) {shoot(); setIntakes(0, 0); wait(longShoot ? 350 : 200 , msec); setRollers(0, 0); break;}
    else {shoot();}

    wait(5, msec);
  }
}
void descore(int balls, bool spit){
  bool boi = false;
  int cnt = 0;
  while(true){
    if(distanceBottom.objectDistance(inches) <= 1.5 && boi == false){boi = true; cnt++;}
    
    if(distanceBottom.objectDistance(inches) >= 1.25) {boi = false;}
    
    if(cnt >= balls) {
      if(spit) setIntakes(-600, -600); wait(500, msec); setIntakes(0, 0); setRollers(0, 0); break;
      if(!spit) {setIntakes(0, 0); setRollers(0, 0); break;}
    } else {
      autoIndex(); setIntakes(250, 250);
    }

    wait(5, msec);
  }
}

void topPoop(int t){
  int cnt = 0;
  setRollers(-200, -400); wait(600, msec); setRollers(0, 0);
  while(true){
    setRollers(600, -600);
    cnt += 5;

    if(leftLimit.pressing() || rightLimit.pressing() || cnt > t) break;
    wait(5, msec);
  }
  setRollers(0, 0);
}

void deploy(){
  setRollers(0, 600); setIntakes(600, 600);
  wait(400, msec);
  setRollers(0, 0); setIntakes(0, 0);
}

//DRIVER CONTROL FUNCTIONS
void opControl_rollerIntakes(){
  //Auto index & failsafe - reverse all rollers
  /*if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()){
    setRollers(-600, -600);
  } else if (Controller1.ButtonL1.pressing()){
    autoIndex();
  } else if (Controller1.ButtonL2.pressing()){
    shoot();
  } else {
    setRollers(0, 0);
  }

  //Shoot
  if(Controller1.ButtonR1.pressing()){
    setIntakes(600, 600);
  } else if (Controller1.ButtonR2.pressing()){
    setIntakes(-600, -600);
  } else {
    setIntakes(0, 0);
  }

  //Failsafe - in case a ball poops when the button isn't being pressed
  if(leftLimit.pressing() || rightLimit.pressing()){
    badBallDetected = false;
  }*/
  if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()){
    setRollers(-400, -400);
  } else if(Controller1.ButtonL1.pressing()){
    setRollers(600, 600);
  } else if(Controller1.ButtonL2.pressing()){
    setRollers(600, -300);
  } else {
    setRollers(0, 0);
  }

  if(Controller1.ButtonR1.pressing()){
    setIntakes(600, 600);
  } else if (Controller1.ButtonR2.pressing()){
    setIntakes(-600, -600);
  } else {
    setIntakes(0, 0);
  }
}