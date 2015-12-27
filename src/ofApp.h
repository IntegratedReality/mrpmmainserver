#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "Robot.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //projection mapping setting
    ofxQuadWarp warper;
    ofFbo fbo;

    //projection range
    int projectionWidth = 600;
    int projectionHeight = 400;

    Robot robotlist[10];    

    ofPoint points[10];
};
