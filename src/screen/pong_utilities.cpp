#include "vex.h"
#include "screen/screen_functions.h"
#include "screen/pong_utilities.h"
#include "drive/drive.h"

using namespace vex;

//TELLS IF RED/BLUE LOST
bool redGameover = false;
bool blueGameover = false;

//BALL CONSTRUCTOR
Ball::Ball(){
  x = SYSTEM_DISPLAY_WIDTH/2; y = SYSTEM_DISPLAY_HEIGHT/2; r = 10;
  cx = 0.6; cy = 0.2;
}

//BALL COLLISION FUNCTIONS
bool Ball::pointCircle(float px, float py, float cx, float cy, float cr){
  if(distanceFormula(px, py, cx, cy) < cr){
    return true;
  } else {
    return false;
  }
}

bool Ball::linePoint(float x1, float y1, float x2, float y2, float px, float py) {
  // get distance from the point to the two ends of the line
  float d1 = distanceFormula(px,py, x1,y1);
  float d2 = distanceFormula(px,py, x2,y2);
  // get the length of the line
  float lineLen = distanceFormula(x1,y1, x2,y2);
  // since floats are so minutely accurate, add
  // a little buffer zone that will give collision
  float buffer = 0.1;    // higher # = less accurate
  // if the two distances are equal to the line's 
  // length, the point is on the line!
  // note we use the buffer here to give a range, 
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return true;
  }
  return false;
}

bool Ball::lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r) {

  // is either end INSIDE the circle?
  // if so, return true immediately
  bool inside1 = pointCircle(x1,y1, cx,cy,r);
  bool inside2 = pointCircle(x2,y2, cx,cy,r);
  if (inside1 || inside2) return true;

  // get length of the line
  float distX = x1 - x2;
  float distY = y1 - y2;
  float len = sqrt( (distX*distX) + (distY*distY) );

  // get dot product of the line and circle
  float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

  // find the closest point on the line
  float closestX = x1 + (dot * (x2-x1));
  float closestY = y1 + (dot * (y2-y1));

  // is this point actually on the line segment?
  // if so keep going, but if not, return false
  bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
  if (!onSegment) return false;

  // optionally, draw a circle at the closest
  // point on the line
  //fill(255,0,0);
  //noStroke();
  //ellipse(closestX, closestY, 20, 20);

  // get distance to closest point
  distX = closestX - cx;
  distY = closestY - cy;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  if (distance <= r) {
    return true;
  }
  return false;
}

//BALL FUNCTIONS
void Ball::display(){
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawCircle(x, y, r);
}

static int blueScore = 0;
static int redScore = 0;
void Ball::move(float px, float py, float pw, float ph, float px2, float py2, float pw2, float ph2){
  y += cy; x += cx;

  if(x+(3*r) > SYSTEM_DISPLAY_WIDTH || x-(3*r) < 0){
    if(lineCircle(px+pw, py, px+pw, py+ph, x, y, r) || lineCircle(px2, py2, px2, py2+ph2, x, y, r)){
      cx *= -1;
      if(lineCircle(px+pw, py, px+pw, py+ph, x, y, r)){
        float val = map(cy, py, py+ph, 0.3, -0.3);
        cy += val;
      }
      if(lineCircle(px2, py2, px2, py2+ph2, x, y, r)){
        float val = map(cy, py2, py2+ph2, 0.3, -0.3);
        cy += val;
      }
    } else {
      if(x+(r) > SYSTEM_DISPLAY_WIDTH){
        redGameover = true;
      }
      if(x-(r) < 0){
        blueGameover = true;
      }
    }
  }
  if(y-(r) < 0 || y+(3*r) > SYSTEM_DISPLAY_HEIGHT){
    cy *= -1;
  }
  if(lineCircle(px+pw, py, px+pw, py+ph, x, y, r)){
    blueScore++;
  }
  if(lineCircle(px2, py2, px2, py2+ph2, x, y, r)){
    redScore++;
  }
  
  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(fontType::prop20);
  Brain.Screen.printAt(5, 30, "Blue Score: %d", blueScore);
  Brain.Screen.printAt(SYSTEM_DISPLAY_WIDTH-150, 30, "Red Score: %d", redScore);
}

//PADDLE CONSTRUCTOR
Paddle::Paddle(int xx){
  w = 25; h = 100; x = xx; y = SYSTEM_DISPLAY_HEIGHT/2 + (h/2); 
}

//PADDLE FUNCTIONS
void Paddle::display(){
  if(x < SYSTEM_DISPLAY_WIDTH/2){
    Brain.Screen.setFillColor(blue);
  } else {
    Brain.Screen.setFillColor(red);
  }
  Brain.Screen.drawRectangle(x, y, w, h);
}

void Paddle::move(){
  if(buttonPressed(x, x + w, 0, SYSTEM_DISPLAY_HEIGHT)){
    y = Brain.Screen.yPosition() - h/2;
  }
}