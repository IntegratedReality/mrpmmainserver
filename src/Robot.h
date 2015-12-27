#pragma once

#include "ofMain.h"

class Robot
{
public:
    Robot();
    void update(int _x, int _y, int _angle);
    void disp();

private:
    int x;
    int y;
    int angle;
    int radius;
};
