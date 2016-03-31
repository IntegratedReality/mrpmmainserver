#include "ofApp.h"

#include <iostream>
using namespace std;

#define IP_OF_ROBOT "mrpmpi2.local"
#define PORT 8000

//--------------------------------------------------------------
void ofApp::setup() {
	sender.init(IP_OF_ROBOT, PORT);
	receiver.init(PORT);
}

//--------------------------------------------------------------
void ofApp::update() {
	receiver.update();
	RobotData data = receiver.getData(0);
	cout << "id: " << data.id << endl;
	cout << "time: " << data.time << endl;
	cout << "x: " << data.pos.x << endl;
	cout << "y: " << data.pos.y << endl;
	cout << "theta: " << data.pos.theta << endl;
	cout << endl;
	sender.sendData(0, data.time, data.pos.x + 1, data.pos.y, data.pos.theta);
}

//--------------------------------------------------------------
void ofApp::draw() {
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
