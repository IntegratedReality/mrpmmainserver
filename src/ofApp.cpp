#include "ofApp.h"

#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(FPS);
	ofNoFill();
	ofBackground(0, 0, 0);
	ofSetWindowShape(WIDTH_OF_FIELD * SCALE, HEIGHT_OF_FIELD * SCALE);
	ofSetWindowTitle("MRPMSimulator");
	ofEnableAlphaBlending();

	manager.init();
}

//--------------------------------------------------------------
void ofApp::update() {
	manager.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	manager.draw();
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
