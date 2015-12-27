#include "ofMain.h"
#include "Robot.h"

Robot::Robot(): x(0), y(0), angle(0), radius(20)
{
}

void Robot::update(int _x, int _y, int _angle)
{
     x = _x;
     y = _y;
     angle = _angle;
     std::cout << "call" << std::endl;
}

void Robot::disp()
{
    ofCircle(x, y, radius);
    int r = radius / 2;
    ofTranslate(x, y);
    ofRotate(angle);
    ofRect(-r, -r, r, r);
    ofRotate(-angle);
    ofTranslate(-x, -y);

    std::cout << "x:" << x << " y:" << y << std::endl;
}
