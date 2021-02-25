#include "vex.h"

//TELLS IF RED/BLUE LOST
extern bool redGameover;
extern bool blueGameover;

//BALL CLASS
class Ball {
  public:
    float x, y, r, cx, cy;
    Ball();
    bool pointCircle(float px, float py, float cx, float cy, float cr);
    bool lineCircle(float cx, float cy, float radius, float rx, float ry, float rw, float rh);
    bool linePoint(float x1, float y1, float x2, float y2, float px, float py);
    void display();
    void move(float px, float py, float pw, float ph, float px2, float py2, float pw2, float ph2);
};

//PADDLE CLASS
class Paddle {
  public:
    int x, y, w, h;
    Paddle(int xx);
    void display();
    void move();
};