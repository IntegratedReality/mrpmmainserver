#include "MRPMMainManager.h"
#include "ofApp.h"

#include <iostream>
using namespace std;

void MRPMMainManager::init() {
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
  
  pmx = PMx::getInstance();
  
  sim = false;
}

void MRPMMainManager::update() {
  timer->update();
  
  mainRcvr.update();
  
  for (int i = 0; i < hostsConfig::NUM_OF_ROBOT; i++) {
    sysRbtMgr.setPos(i, mainRcvr.getData(i).pos);
  }
  
  if (mode == GAME) {
    
    if (timer->getTime() >= 3 * 60 * 1000) {
      mode = RESULT;
      ofSetWindowTitle("RESULT");
      judge.end();
      sndMgr.stopBGM();
    }
    
    for (int i = 0; i < hostsConfig::NUM_OF_ROBOT; i++) {
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
  
  //data sending ------------------
  
  //send to ctrlrs
  {
    MRPMPackMainToCtrlr pack;
    pack.positionsVec = blltMgr.getPositionsVec();
    pack.velocitiesVec = blltMgr.getVelocitiesVec();
    mainSndr.sendToCtrlrs(pack);
  }
  
  //send to robot
  for(int i=0; i<hostsConfig::NUM_OF_ROBOT; ++i){
    MRPMPackMainToRobot pack;
    auto roboData = sysRbtMgr.getData(i);
    pack.time = static_cast<int>(roboData.time);
    pack.x = roboData.pos.x;
    pack.y = roboData.pos.y;
    pack.theta = roboData.pos.theta;
    pack.permissions.fill(true);  //とりあえず全部許可しとく
    
    //pack.permissions = checkMovability(roboData.pos);
    //TODO: 全許可で動作確認とれたら UNCOMMENT
    
    mainSndr.sendToOneRobot(i, pack);
  }
  
  //send to AIs
  {
    MRPMPackMainToAI pack;
    
    mainSndr.sendToAIs(pack);
  }
  
  /*
  RobotData data;
  for (int i = 0; i < hostsConfig::NUM_OF_ROBOT; i++) {
    data = sysRbtMgr.getData(i);
    mainSndr.sendData
    (data.id,
     data.time,
     data.pos.x,
     data.pos.y,
     data.pos.theta,
     data.HP,
     data.EN,
     mode != GAME ? STANDBY2 : data.state);
    judge.setRobotState(i, data.state);
  }
  
  for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
    mainSndr.sendPOOwner(i, sysPObjMgr.getOwner(i));
    judge.setPOOwner(i, sysPObjMgr.getOwner(i));
  }
   */
}

void MRPMMainManager::draw() {
  sysRbtMgr.draw();
  sysPObjMgr.draw();
  //    vWllMgr.draw();
  //    itmMgr.draw();
  blltMgr.draw();
  
  if (mode == RESULT) {
    pmx->drawTextField();
    switch (judge.getWinner()) {
      case TEAM_A:
        pmx->drawText("WIN", 1500, 700, 49, ofColor(255, 120, 0, 200));
        break;
      case TEAM_B:
        pmx->drawText("LOSE", 1500, 700, 49, ofColor(0, 120, 255, 200));
        break;
      case NEUTRAL:
        pmx->drawText("DRAW", 1500, 700, 49, ofColor(0, 120, 0, 200));
        break;
    }
  } else if (mode == STANDBY) {
    pmx->drawTextField();
    pmx->drawText("MRPM", 1500, 700, 49, ofColor(220, 120, 0, 200));
  }
  
  //added by sakabe
  //カメラやビューポートと独立に描画したい
  pmx->drawLatticeIfNeeded();
}

void MRPMMainManager::keyPressed(int key) {
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

permsAry checkMovability
(Position _pos){
  //mrpmRobotから移管
  
  permsAry ary;
  enableAll(ary);
  
  double vx = cos(_pos.theta), vy = sin(_pos.theta);
  ofVec2f velocity(vx, vy);
  
  const int radAndMargin = RADIUS_OF_ROBOT + MARGIN_OF_COLLISION;
  
  // フィールド上辺
  if (_pos.y < radAndMargin) {
    if (vy < 0){
      disableForward(ary);
    }else{
      disableBackward(ary);
    }
      //_F = false;
    //else _B = false;
  }
  
  // 右辺
  if (_pos.x > WIDTH_OF_FIELD - radAndMargin) {
    if (vx > 0){
      disableForward(ary);
    }else{
      disableBackward(ary);
    }
      //_F = false;
    //else _B = false;
  }
  
  // 下辺
  if (_pos.y > HEIGHT_OF_FIELD - radAndMargin) {
    if (vy > 0){
      disableForward(ary);
    }else{
      disableBackward(ary);
    }
      //_F = false;
    //else _B = false;
  }
  
  // 左辺
  if (_pos.x < radAndMargin) {
    if (vx < 0){
      disableForward(ary);
    }else{
      disableBackward(ary);
    }
      //_F = false;
//    else _B = false;
  }
  /*
  // ポイントオブジェクト1
  if (distance(_pos, p1) < 125 + 100 + 30) {
    Eigen::Vector2f dirToObj(p1.x-_pos.x, p1.y-_pos.y);
    if (dirToObj.dot(velocity) > 0) _F = false;
    else _B = false;
  }
  // ポイントオブジェクト2
  if (distance(_pos, p2) < 125 + 100 + 30) {
    Eigen::Vector2f dirToObj(p2.x-_pos.x, p2.y-_pos.y);
    if (dirToObj.dot(velocity) > 0) _F = false;
    else _B = false;
  }
  // ポイントオブジェクト3
  if (distance(_pos, p3) < 125 + 100 + 30) {
    Eigen::Vector2f dirToObj(p3.x-_pos.x, p3.y-_pos.y);
    if (dirToObj.dot(velocity) > 0) _F = false;
    else _B = false;
  }
  */
  return ary;
}
