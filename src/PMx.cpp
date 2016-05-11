#include "PMx.h"

void PMx::setup() {
	/* initialize oF */
	ofBackground(0);
	PM.initializeProjection();  //this function includes configurations of oF

	//    /* set point objects(x,y,theta) */
	//    PM.p_object[0].init(screen_height/2,screen_width/4, 2); //(x,y,theta)
	//    PM.p_object[1].init(screen_height,screen_width/2, 1);
	//    PM.p_object[2].init(screen_height*1.5,screen_width*0.75, 0.5);

	/* load images if needed */
	PM.textureImg.load("281.gif");
	PM.pointObjectTexture.load("texture.jpg");  //example texture
	PM.bulletImg.load("blue.png");  //image for bullet
    PM.backGroundImg.load("bg.jpg");
    //PM.createFieldBgFbo();
    
    PM.fieldShader.load("test.vert", "water.frag");
    PM.objectShader.load("test.vert", "cloud.frag");
    
    /* load font */
    for (int i = 1; i < 34; i++){
        PM.font[i].load("Arial.ttf",i);
    }
    
    PM.startTime = ofGetElapsedTimef();
}

void PMx::keyPressed(int key) {
	/* simple calibration utils */
	if (key == 49){
		PM.bConfPort2 = 0;
		PM.bConfPort1 = !PM.bConfPort1;
		cout << "bConfPort1 : " << PM.bConfPort1 << endl;
	}
	if (key == 50){
		PM.bConfPort1 = 0;
		PM.bConfPort2 = !PM.bConfPort2;
		cout << "bConfPort2 : " << PM.bConfPort2 << endl;
	}
    if (key == 51){
        PM.bConfShade1 = !PM.bConfShade1;
        PM.bConfPort1 = false;
        PM.bConfPort2 = false;
        PM.bconfShade2 = false;
        cout << "bConfShade1 : " << PM.bConfShade1 << endl;
    }
    if (key == 52){
        PM.bconfShade2 = !PM.bconfShade2;
        PM.bConfPort1 = false;
        PM.bConfPort2 = false;
        PM.bConfShade1 = false;
        cout << "bConfShade2 : " << PM.bconfShade2 << endl;
    }

	if (PM.bConfPort1){
		if (key == OF_KEY_RIGHT){
			PM.viewPortPosition1.x += 1;
			PM.viewPort[0].setPosition(PM.viewPortPosition1.x, PM.viewPortPosition1.y);
			cout << "position1(x) : " << PM.viewPortPosition1.x << endl;
		}
		if (key == OF_KEY_LEFT){
			PM.viewPortPosition1.x -= 1;
			PM.viewPort[0].setPosition(PM.viewPortPosition1.x, PM.viewPortPosition1.y);
			cout << "position1(x) : " << PM.viewPortPosition1.x << endl;
		}
		if (key == OF_KEY_UP){
			PM.viewPortPosition1.y -= 1;
			PM.viewPort[0].setPosition(PM.viewPortPosition1.x, PM.viewPortPosition1.y);
			cout << "position1(x) : " << PM.viewPortPosition1.y << endl;
		}
		if (key == OF_KEY_DOWN){
			PM.viewPortPosition1.y += 1;
			PM.viewPort[0].setPosition(PM.viewPortPosition1.x, PM.viewPortPosition1.y);
			cout << "position1(x) : " << PM.viewPortPosition1.y << endl;
		}
	}
	else if (PM.bConfPort2){
		if (key == OF_KEY_RIGHT){
			PM.viewPortPosition2.x += 1;
			PM.viewPort[1].setPosition(PM.viewPortPosition2.x, PM.viewPortPosition2.y);
			cout << "position2(x) : " << PM.viewPortPosition1.x << endl;
		}
		if (key == OF_KEY_LEFT){
			PM.viewPortPosition2.x -= 1;
			PM.viewPort[1].setPosition(PM.viewPortPosition2.x, PM.viewPortPosition2.y);
			cout << "position2(x) : " << PM.viewPortPosition1.x << endl;
		}
		if (key == OF_KEY_UP){
			PM.viewPortPosition2.y -= 1;
			PM.viewPort[1].setPosition(PM.viewPortPosition2.x, PM.viewPortPosition2.y);
			cout << "position2(y) : " << PM.viewPortPosition1.y << endl;
		}
		if (key == OF_KEY_DOWN){
			PM.viewPortPosition2.y += 1;
			PM.viewPort[1].setPosition(PM.viewPortPosition2.x, PM.viewPortPosition2.y);
			cout << "position2(y) : " << PM.viewPortPosition1.y << endl;
		}
	}
    else if (PM.bConfShade1){
        switch (key) {
            case OF_KEY_UP:
                PM.shadeWidth1 += 1;
                cout << "shade1 : " << PM.shadeWidth1 << endl;
                break;
            case OF_KEY_DOWN:
                PM.shadeWidth1 -= 1;
                cout << "shade1 : " << PM.shadeWidth1 << endl;
            default:
                break;
        }
    }
    else if (PM.bconfShade2){
        switch (key) {
            case OF_KEY_UP:
                PM.shadeWidth2 += 1;
                cout << "shade2 : " << PM.shadeWidth2 << endl;
                break;
            case OF_KEY_DOWN:
                PM.shadeWidth2 -= 1;
                cout << "shade2 : " << PM.shadeWidth2 << endl;
                
            default:
                break;
        }
    }
	else {
		if (key == OF_KEY_RIGHT){
			PM.camAngle += 0.5;
			PM.cam[0].setFov(PM.camAngle);   //35.45
			PM.cam[1].setFov(PM.camAngle);
            cout << "camAngle : " << PM.camAngle << endl;
		}
		if (key == OF_KEY_LEFT){
			PM.camAngle -= 0.5;
			PM.cam[0].setFov(PM.camAngle);   //35.45
			PM.cam[1].setFov(PM.camAngle);
			cout << "camAngle : " << PM.camAngle << endl;
		}
	}
}

void PMx::drawField() {
	// screen 1
	PM.cam[0].begin(PM.viewPort[0]);
	_drawField();
	PM.cam[0].end();

	// screen 2
	PM.cam[1].begin(PM.viewPort[1]);
	_drawField();
	PM.cam[1].end();
}

void PMx::drawFieldTexture() {
    // screen 1
    PM.cam[0].begin(PM.viewPort[0]);
    _drawFieldTexture();
    PM.cam[0].end();
    
    // screen 2
    PM.cam[1].begin(PM.viewPort[1]);
    _drawFieldTexture();
    PM.cam[1].end();
}

void PMx::drawShaderField(){
    // screen 1
    PM.cam[0].begin(PM.viewPort[0]);
    _drawShaderField();
    PM.cam[0].end();
    
    // screen 2
    PM.cam[1].begin(PM.viewPort[1]);
    _drawShaderField();
    PM.cam[1].end();
}

void PMx::drawPO(int _id) {
	// screen 1
	PM.cam[0].begin(PM.viewPort[0]);
	_drawPO(_id);
	PM.cam[0].end();

	// screen 2
	PM.cam[1].begin(PM.viewPort[1]);
	_drawPO(_id);
	PM.cam[1].end();
}

void PMx::drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
	// screen 1
	PM.cam[0].begin(PM.viewPort[0]);
	_drawRobot(_x, _y, _theta, _data);
	PM.cam[0].end();

	// screen 2
	PM.cam[1].begin(PM.viewPort[1]);
	_drawRobot(_x, _y, _theta, _data);
	PM.cam[1].end();
}

void PMx::drawImg(double _x, double _y, double _theta, ofImage &_img) {
	// screen 1
	PM.cam[0].begin(PM.viewPort[0]);
	_drawImg(_x, _y, _theta, _img);
	PM.cam[0].end();

	// screen 2
	PM.cam[1].begin(PM.viewPort[1]);
	_drawImg(_x, _y, _theta, _img);
	PM.cam[1].end();
}

void PMx::_drawField() {
	ofNoFill();
	ofPushStyle();
	ofSetColor(50, 50, 250);
	ofDrawRectangle(0,0,screen_height,screen_width);
	ofDrawRectangle(screen_height,0,screen_height,screen_width);
	ofPopStyle();
	ofFill();
}

void PMx::_drawFieldTexture(){
    /* not necessarily create fbo here (should be written in ofApp::update) */
    PM.backGroundFbo.begin();
    ofDisableNormalizedTexCoords();
    PM.backGroundImg.getTexture().draw(0, 0, screen_height*2, screen_width);
    ofEnableNormalizedTexCoords();
    ofNoFill();
    ofPushStyle();
    ofSetColor(50, 50, 250);
    ofDrawRectangle(0,0,1,screen_height,screen_width);
    ofDrawRectangle(screen_height,0,1,screen_height,screen_width);
    ofPopStyle();
    ofFill();
    
    /* minimum example for animation */
    ofPushMatrix();
    ofTranslate(100,100,1);
    ofRotate(ofGetElapsedTimeMillis()%360);
    ofDrawRectangle(0, 0, 100, 100);
    ofPopMatrix();
    PM.backGroundFbo.end();
    
    PM.backGroundFbo.draw(0,0);
}

void PMx::_drawShaderField(){
    PM.currentTime = ofGetElapsedTimef();
    PM.time = PM.currentTime - PM.startTime;
    
    PM.fieldShader.begin();
    PM.fieldShader.setUniform1f("time", PM.time);
    PM.fieldShader.setUniform2f("resolution", ofVec2f(screen_height*2, screen_width));
    ofDrawRectangle(0, 0, screen_height*2, screen_width);
    PM.fieldShader.end();

    ofNoFill();
    ofPushStyle();
    ofSetColor(50, 50, 250);
    ofDrawRectangle(0,0,1,screen_height,screen_width);
    ofDrawRectangle(screen_height,0,1,screen_height,screen_width);
    ofPopStyle();
    ofFill();
}

void PMx::_drawPO(int _id) {
	PM.p_object[_id].draw(PM.pointObjectTexture);
//    PM.p_object[_id].draw(PM.objectShader);
}

void PMx::_drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
	PM.robot[_data->id].draw(_x, _y, _theta, PM.textureImg);
}

void PMx::_drawImg(double _x, double _y, double _theta, ofImage &_img) {
	ofDisableNormalizedTexCoords();
	PM.bullet.draw(_x, _y, _theta, _img);
	ofEnableNormalizedTexCoords();
}

void PMx::drawText(string content, int x, int y, int size, ofColor textColor){
//        ofTranslate(0, 0, 600);
    if (size > 34){
        size = 34;
    }
    PM.cam[0].begin();
        ofPushMatrix();
        ofPushStyle();
            ofSetColor(textColor);
            ofTranslate(0,0,132);
            ofRotateZ(90);
            PM.font[size].drawString(content, PM.viewPortPosition1.x*0.5 - 105 + x*0.3, -PM.viewPortPosition1.y*0.5 - 50 - y*0.3);
            PM.font[size].drawString(content, 200, 200);
        ofPopStyle();
        ofPopMatrix();
    PM.cam[0].end();
    
}

void PMx::drawTextField(ofColor bgColor){
    PM.cam[0].begin();
        ofPushMatrix();
        ofPushStyle();
            ofTranslate(0,0,130);
            ofSetColor(bgColor);
            ofFill();
            ofDrawRectangle(-300,-300,768*2,1024);
        ofPopStyle();
        ofPopMatrix();
    PM.cam[0].end();
}

