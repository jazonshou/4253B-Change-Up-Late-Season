#include "vex.h"

//HELPER FUNCTIONS
class Button {
  public:
    int x, y, w, h; color c; std::string text;
    Button(int xx, int yy, int ww, int hh, color cc, std::string ttext);
    void generateButton();
    bool isPressed();
};
bool buttonPressed(int leftX, int rightX, int topY, int bottomY);
void background();

//GAMES
void pong();

//CONTROLLER
std::string getTemp(motor m);