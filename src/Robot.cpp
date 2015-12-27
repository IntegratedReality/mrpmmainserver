#include "ofMain.h"
#include "Robot.h"

Robot::Robot(): x(0), y(0), angle(0), radius(20)
{
}

void Robot::update(int _x, int _y, int _angle)
{
     x = _x;
     y = _y;
     angle += 10;
}

void Robot::disp()
{
    ofSetColor(ofColor::white);
    ofDrawCircle(x, y, radius);
    int r = radius;
    int rect_x = r / 2;
    int rect_y = r;
    ofTranslate(x, y);
    ofRotate(angle);
    ofTranslate(-rect_x, -rect_y);
    ofSetColor(ofColor::yellow);
    ofDrawCircle(0, 0, 5);
    ofDrawCircle(2 * rect_x, 0, 5);
    ofSetColor(ofColor::orange);
    ofDrawRectangle(0, 0, 2 * rect_x, 2 * rect_y);
    ofTranslate(rect_x, rect_y);
    ofRotate(-angle);
    ofTranslate(-x, -y);
}
