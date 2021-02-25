#include "vex.h"

//MACROS
extern int VISION_FOV_WIDTH;
extern int VISION_FOV_HEIGHT;

//VISION FUNCTIONS
void visionTrack(int idealHeight, double turn_kP, double move_kP, double move_kD);
void visionTurn();