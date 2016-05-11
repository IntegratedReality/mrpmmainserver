#include "ofApp.h"

#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(FPS);

	// PM
	PM = PMx::getInstance();
	PM->setup();

	//ofNoFill();
	//ofBackground(0, 0, 0);
	//ofSetWindowShape(WIDTH_OF_FIELD * SCALE, HEIGHT_OF_FIELD * SCALE);
	//ofSetWindowTitle("MRPMMainServer");
	//ofEnableAlphaBlending();

	manager.init();
}

//--------------------------------------------------------------
void ofApp::update() {
	manager.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	manager.draw();
	PM->drawShaderField();
    
    /* PM text-example */
//    PM->drawTextField();
//    PM->drawText("Left",0,0,10);
//    PM->drawText("TextTest",10,300,20);
//    PM->drawText("Right", 1024, 0,30);
//    PM->drawText("Bottom",0,768, 5);
    
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	PM->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofxOscMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
