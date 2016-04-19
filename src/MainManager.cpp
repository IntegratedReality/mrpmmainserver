#include "MainManager.h"
#include "ofApp.h"

#include <iostream>
using namespace std;

#define DEBUG(x) cout << x << endl

void MainManager::init() {
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
}

void MainManager::update() {
	mainRcvr.update();
	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		//sysRbtMgr.setPos(i, mainRcvr.getData(i).pos);
		sysRbtMgr.setPos(i, Position(100 * i, 100 * i, 0));
		//cout << i << mainRcvr.getData(i).pos.x << endl;
		sysRbtMgr.setShot(i, mainRcvr.getData(i).operation.shot);
	}
	sysRbtMgr.update();
	sysPObjMgr.update();
	vWllMgr.update();
	itmMgr.update();
	blltMgr.update();
	box2d->update();

	RobotData data;
	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		data = sysRbtMgr.getData(i);
		mainSndr.sendData(data.id, data.time, data.pos.x, data.pos.y, data.pos.theta);
	}

	time++;
	if (time == 300) {
		itmMgr.makeItem(Position(WIDTH_OF_FIELD / 4, HEIGHT_OF_FIELD / 2, 0), SPEEDER);
		time = 0;
	}
}

void MainManager::draw() {
	sysRbtMgr.draw();
	sysPObjMgr.draw();
	vWllMgr.draw();
	itmMgr.draw();
	blltMgr.draw();
}
