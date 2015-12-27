#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(50);
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    //OSC
    receiver.setup( PORT );
    for(int i = 0; i < 10; i++){
        remotepos[i].x = 0;
        remotepos[i].y = 0;
        remotepos[i].z = 0;
    }
    counter = 0;

    int x = (ofGetWidth() - projectionWidth) * 0.5;       // center on screen.
    int y = (ofGetHeight() - projectionHeight) * 0.5;     // center on screen.
    int w = projectionWidth;
    int h = projectionHeight;

    fbo.allocate(w, h);

    warper.setSourceRect(ofRectangle(0, 0, w, h));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warper.setTopLeftCornerPosition(ofPoint(x, y));             // this is position of the quad warp corners, centering the image on the screen.
    warper.setTopRightCornerPosition(ofPoint(x + w, y));        // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));      // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h)); // this is position of the quad warp corners, centering the image on the screen.
    warper.setup();
    warper.load(); // reload last saved changes.
    
    for(int i=0; i<10; i++) {
        // randomise points over the image area.
        points[i].x = ofRandom(projectionWidth);
        points[i].y = ofRandom(projectionHeight);
        robotlist[i].update((int)points[i].x, (int)points[i].y, 30);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    //OSC
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if(m.getAddress() == "/robot/pos"){
            remotepos[counter].x = m.getArgAsInt32(0);
            remotepos[counter].y = m.getArgAsInt32(1);
            remotepos[counter].z = m.getArgAsInt32(2);
        }

        dumpOSC(m);
    }
    
    if(ofGetFrameNum() % 5 != 0) {
        // only update every 5 frames.
        return;
    }

    for(int i=0; i<10; i++) {
        //points[i].x = ofRandom(projectionWidth);
        //points[i].y = ofRandom(projectionHeight);
        points[i].x += ofRandom(10) - 5;
        points[i].y += ofRandom(10) - 5;
        robotlist[i].update((int)points[i].x, (int)points[i].y, 0);
    }
}

//OSC stream out
void ofApp::dumpOSC(ofxOscMessage m){
    std::string msg_string;
    msg_string = m.getAddress();
    for(int i = 0; i < m.getNumArgs(); i++){
        msg_string += " ";
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += ofToString(m.getArgAsString(i));
        }
    }
    std::cout << msg_string << std::endl;
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);

    //======================== draw image into fbo.
    // edit here to draw constant object
    fbo.begin();
    ofClear(255, 255, 255, 0);
    for(int i = 0; i < 10; i++){
        robotlist[i].disp();
    }
    fbo.end();

    //======================== get our quad warp matrix.

    ofMatrix4x4 mat = warper.getMatrix();

    //======================== use the matrix to transform our fbo.

    ofPushMatrix();
    ofMultMatrix(mat);
    fbo.draw(0, 0);
    ofPopMatrix();

    //======================== use the matrix to transform points.

    /*ofSetLineWidth(2);
    ofSetColor(ofColor::cyan);
    for(int i=0; i<9; i++) {
        int j = i + 1;

        ofVec3f p1 = mat.preMult(ofVec3f(points[i].x, points[i].y, 0));
        ofVec3f p2 = mat.preMult(ofVec3f(points[j].x, points[j].y, 0));

        ofDrawLine(p1.x, p1.y, p2.x, p2.y);
    }*/

    //======================== draw quad warp ui.

    ofSetColor(ofColor::magenta);
    warper.drawQuadOutline();

    ofSetColor(ofColor::yellow);
    warper.drawCorners();

    ofSetColor(ofColor::magenta);
    warper.drawHighlightedCorner();

    ofSetColor(ofColor::red);
    warper.drawSelectedCorner();

    //======================== info.

    ofSetColor(ofColor::white);
    ofDrawBitmapString("to warp the image, drag the corners of the image.", 20, 30);
    ofDrawBitmapString("press 's' to toggle quad warp UI. this will also disable quad warp interaction.", 20, 50);
    ofDrawBitmapString("press & hold 1, 2, 3, 4 to snap that point to the mouse", 20, 70);
    ofDrawBitmapString("when a corner is selected (red), use keyboard arrow keys to nudge the corner position.", 20, 90);
}

void ofApp::exit() {
    warper.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    if(key == 's' || key == 'S') {
        warper.toggleShow();
    }

    if(key == 'l' || key == 'L') {
        warper.load();
    }

    if(key == 'h' || key == 'H') {
        warper.save();
    }
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
