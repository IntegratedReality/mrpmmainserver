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
	else {
		if (key == OF_KEY_RIGHT){
			PM.camAngle += 0.5;
			PM.cam[0].setFov(PM.camAngle);   //35.45
			PM.cam[1].setFov(PM.camAngle);
			cout << "camAngle : " << PM.camAngle;
		}
		if (key == OF_KEY_LEFT){
			PM.camAngle -= 0.5;
			PM.cam[0].setFov(PM.camAngle);   //35.45
			PM.cam[1].setFov(PM.camAngle);
			cout << "camAngle : " << PM.camAngle;
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

void PMx::_drawPO(int _id) {
	PM.p_object[_id].draw(PM.textureImg);
}

void PMx::_drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
	PM.robot[_data->id].draw(_x,_y,_theta,PM.textureImg);
}

void PMx::_drawImg(double _x, double _y, double _theta, ofImage &_img) {
	ofDisableNormalizedTexCoords();
	PM.bullet.draw(_x, _y, _theta, PM.bulletImg);
	ofEnableNormalizedTexCoords();
}
