#include "ofApp.h"

#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(FPS);
  ofSetWindowShape(1024, 768*2);
  ofSetWindowPosition(1680, 0);
  
  // PM
  pmx = PMx::getInstance();
  pmx->setup();
  
  //ofNoFill();
  //ofBackground(0, 0, 0);
  //ofSetWindowTitle("MRPMMainServer");
  //ofEnableAlphaBlending();
  
  manager.init();
  //    startTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update() {
  manager.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  pmx->drawShaderField();
  manager.draw();
  
  //    PM->drawBullet(500, 1000, 0, ETeam(0));
  
  //    PM->drawVWall(500,1000,50,600);
  
  /* PM bullet-example */
  //    PM->drawBullet(500, 100, 0, 500, 500);
  //    PM->drawBullet(200, 200, double(0), float(5000), float(ofGetElapsedTimeMillis() - startTime));
  
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
  pmx->keyPressed(key);
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
