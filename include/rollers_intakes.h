#include "vex.h"

extern bool allianceColor;
extern bool badBallDetected;

//ROLLER & INTAKE FUNCTIONS
void setRollers(int bottom, int top);
void setIntakes(int left, int right);

//ROLLER & INTAKE AUTOMATION
void poop();
void autoIndex();
void shoot();
void score(int balls, bool longShoot);
void descore(int balls, bool spit);
void topPoop(int t);
void deploy();

//DRIVER CONTROL FUNCTIONS
void opControl_rollerIntakes();