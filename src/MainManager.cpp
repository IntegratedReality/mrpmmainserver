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
 //   itmMgr.init();
//    vWllMgr.init();
    blltMgr.init();
    sndMgr.init();
    judge.init();

    mode = STANDBY;

    PM = PMx::getInstance();

    sim = false;
}

void MainManager::update() {
    timer->update();

    mainRcvr.update();

    for (int i = 0; i < NUM_OF_ROBOT; i++) {
        sysRbtMgr.setPos(i, mainRcvr.getData(i).pos);
    }

    if (mode == GAME) {

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
 //       vWllMgr.update();
 //      itmMgr.update();
        blltMgr.update();
        sndMgr.update();
        judge.update();

        box2d->update();

    }

    RobotData data;
    for (int i = 0; i < NUM_OF_ROBOT; i++) {
        data = sysRbtMgr.getData(i);
        mainSndr.sendData(data.id, data.time, data.pos.x, data.pos.y, data.pos.theta, data.HP, data.EN, mode != GAME ? STANDBY2 : data.state);
        judge.setRobotState(i, data.state);
    }

    for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
        mainSndr.sendPOOwner(i, sysPObjMgr.getOwner(i));
        judge.setPOOwner(i, sysPObjMgr.getOwner(i));
    }
}

void MainManager::draw() {
    sysRbtMgr.draw();
    sysPObjMgr.draw();
//    vWllMgr.draw();
//    itmMgr.draw();
    blltMgr.draw();

    if (mode == RESULT) {
        PM->drawTextField();
        switch (judge.getWinner()) {
            case TEAM_A:
                PM->drawText("WIN", 1500, 700, 49, ofColor(255, 120, 0, 200)); 
                break;
            case TEAM_B:
                PM->drawText("LOSE", 1500, 700, 49, ofColor(0, 120, 255, 200));
                break;
            case NEUTRAL:
                PM->drawText("DRAW", 1500, 700, 49, ofColor(0, 120, 0, 200));
                break;
        }
    } else if (mode == STANDBY) {
        PM->drawTextField();
        PM->drawText("MRPM", 1500, 700, 49, ofColor(220, 120, 0, 200));
    }
}

void MainManager::keyPressed(int key) {
    if (key == 's') sim = !sim;
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
