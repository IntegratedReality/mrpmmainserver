#include "ofApp.h"

#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(FPS);
	ofSetWindowShape(1024, 768*2);
	ofSetWindowPosition(1680, 0);

	// PM
	PM = PMx::getInstance();
	PM->setup();

	//ofNoFill();
	//ofBackground(0, 0, 0);
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
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	PM->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	manager.keyPressed(key);
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
