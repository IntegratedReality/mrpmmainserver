#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "ofxOsc.h"
#include "Robot.h"

constexpr int PORT = 8000;

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
    void gotMessage(ofxOscMessage msg);

    //projection mapping setting
    ofxQuadWarp warper;
    ofFbo fbo;

    //projection range
    int projectionWidth = 600;
    int projectionHeight = 400;

    Robot robotlist[10];    
    ofPoint points[10];

    void dumpOSC(ofxOscMessage m);

private:
    //OSC
    ofxOscReceiver receiver;
    ofVec3f remotepos[10];
    int counter;
};
