#include "vex.h"
#include "screen/screen_functions.h"
#include "screen/pong_utilities.h"

using namespace vex;

//HELPER FUNCTIONS
Button::Button(int xx, int yy, int ww, int hh, color cc, std::string ttext){
  x = xx; y = yy; w = ww; h = hh; c = cc; text = ttext;
}

void Button::generateButton(){
  Brain.Screen.drawRectangle(x, y, w, h, c);
  Brain.Screen.printAt(x+50, y+50, text.c_str());
}

bool Button::isPressed(){
  if(buttonPressed(x, x+w, y, y+h)){
    return true;
  }
  return false;
}

bool buttonPressed(int leftX, int rightX, int topY, int bottomY){
  if(Brain.Screen.pressing() && (Brain.Screen.xPosition() > leftX && Brain.Screen.xPosition() < rightX) && (Brain.Screen.yPosition() > topY && Brain.Screen.yPosition() < bottomY)){
    return true;
  } 
  return false;
}

void background(){
  Brain.Screen.clearScreen();
}

//GAMES
void pong(){
  Paddle p1(0);
  Paddle p2(SYSTEM_DISPLAY_WIDTH - 25);
  Ball b;

  while(!buttonPressed(250, 450, 150, 250)){
    Brain.Screen.drawRectangle(250, 150, 200, 100, red);
    Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(fontType::mono15);
    Brain.Screen.printAt(300, 200, "Start Pong");
    if(buttonPressed(250, 450, 150, 250)){
      Brain.Screen.clearScreen();
      break;
    }
    wait(20, msec);
  }
  while(redGameover == false && blueGameover == false){
    Brain.Screen.clearScreen();
    p1.display();
    p1.move();
    p2.display();
    p2.move();
    b.display();
    b.move(p1.x, p1.y, p1.w, p1.h, p2.x, p2.y, p2.w, p2.h);
    wait(5, msec);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(SYSTEM_DISPLAY_WIDTH/2, SYSTEM_DISPLAY_HEIGHT/2-100, "y'all r both bad");
  Brain.Screen.printAt(SYSTEM_DISPLAY_WIDTH/2-50, SYSTEM_DISPLAY_HEIGHT/2-70, "imagine being bored enough to play this game lmao");
}

