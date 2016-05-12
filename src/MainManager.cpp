#include "MainManager.h"
#include "ofApp.h"

#include <iostream>
using namespace std;

void MainManager::init() {
	ofSetWindowTitle("STANDBY");

	timer = Timer::getInstance();
	timer->init();

	box2d = SysBox2D::getInstance();
	box2d->init();
	box2d->setGravity(0, 0);
	box2d->setFPS(FPS);
	box2d->getWorld()->SetContactListener(&collisionListener);

	mainSndr.init();
	mainRcvr.init();
	sysRbtMgr.init();
	sysPObjMgr.init();
	time = 0;
	itmMgr.init();
	vWllMgr.init();
	blltMgr.init();
	sndMgr.init();
	judge.init();

	mode = STANDBY;
}

void MainManager::update() {
	timer->update();

	mainRcvr.update();

	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		sysRbtMgr.setPos(i, mainRcvr.getData(i).pos);
	}

	if (mode != GAME) return;

	if (timer->getTime() >= 3 * 60 * 1000) {
		mode = RESULT;
		ofSetWindowTitle("RESULT");
		judge.end();
		sndMgr.stopBGM();
	}

	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		sysRbtMgr.setShot(i, mainRcvr.getData(i).operation.shot);
	}

	sysRbtMgr.update();
	sysPObjMgr.update();
	vWllMgr.update();
	itmMgr.update();
	blltMgr.update();
	sndMgr.update();
	judge.update();

	box2d->update();

	RobotData data;
	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		data = sysRbtMgr.getData(i);
		mainSndr.sendData(data.id, data.time, data.pos.x, data.pos.y, data.pos.theta, data.HP, data.EN, data.state);
		judge.setRobotState(i, data.state);
	}

	for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
		mainSndr.sendPOOwner(i, sysPObjMgr.getOwner(i));
		judge.setPOOwner(i, sysPObjMgr.getOwner(i));
	}

	//time++;
	//if (time == 300) {
	//	itmMgr.makeItem(Position(WIDTH_OF_FIELD / 4, HEIGHT_OF_FIELD / 2, 0), SPEEDER);
	//	time = 0;
	//}
}

void MainManager::draw() {
	sysRbtMgr.draw();
	sysPObjMgr.draw();
	vWllMgr.draw();
	itmMgr.draw();
	blltMgr.draw();
	
	if (mode == RESULT) {

	}
}

void MainManager::keyPressed(int key) {
	switch (mode) {
		case STANDBY:
			if (key == OF_KEY_RETURN) {
				mode = GAME;
				ofSetWindowTitle("GAME");
				sndMgr.startBGM();
				timer->init();
				sysRbtMgr.init();
				sysPObjMgr.init();
				blltMgr.init();
				judge.start();
			}
			break;
		case GAME:
			if (key == 'q') {
				mode = STANDBY;
				ofSetWindowTitle("STANDBY");
				sndMgr.stopBGM();
				timer->init();
				sysRbtMgr.init();
				sysPObjMgr.init();
				blltMgr.init();
				judge.end();
			} else if (key == OF_KEY_RETURN) {
				//mode = RESULT;
				//ofSetWindowTitle("RESULT");
				//sndMgr.stopBGM();
			}
			break;
		case RESULT:
			if (key == OF_KEY_RETURN) {
				mode = STANDBY;
				ofSetWindowTitle("STANDBY");
				sndMgr.stopBGM();
				timer->init();
				sysRbtMgr.init();
				sysPObjMgr.init();
				blltMgr.init();
			}
			break;
	}
}
