#include "vex.h"

//BOT TRACK
extern double track;

//CURRENT SENSOR VALUES
extern double currentL;
extern double currentR;
extern double currentAngle;

//PREVIOUS SENSOR VALUES (5 MSEC AGO)
extern double prevL;
extern double prevR;
extern double prevAngle;

//CHANGE IN SENSOR VALUES
extern double deltaL;
extern double deltaR;
extern double deltaAngle;

//CHANGE IN POLAR/CARTESIAN
extern double localDeltaX;
extern double localDeltaY;
extern double globalDeltaX;
extern double globalDeltaY;

//PREVIOUS POLAR COORDINATES
extern double prevLocalX;
extern double prevLocalY;

//CURRENT CARTESIAN COORDINATES
extern double XPos;
extern double YPos;

//ODOMETRY FUNCTIONS
void updateEncoders();
void updatePosition();

//RESET
void resetOdom();