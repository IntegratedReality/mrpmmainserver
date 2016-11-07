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
//      vWllMgr.init();
  fxMgr.init();
  blltMgr.init();
  sndMgr.init();
  judge.init();
  
  mode = EMode::STANDBY;
  
  pmx = PMx::getInstance();
  
  sim = false;
}

void MRPMMainManager::update() {
  timer->update();
  
  mainRcvr.update();
  
  for (int i = 0; i < hostsConfig::NUM_OF_ROBOT; i++) {
    sysRbtMgr.setPos(i, mainRcvr.getData(i).pos);
  }
  
  if (mode == EMode::STANDBY){
    static SparseExecutor assignRobotsToCtrlrs
    (static_cast<int>(ofGetFrameRate()*2),
     [&](){
       mainSndr.sendToCtrlrsAssignSignal();
     });
    assignRobotsToCtrlrs.touch();
  }
  
  if (mode == EMode::GAME) {
    
    if (timer->getTime() >= GAME_DURATION_MSEC) {
      mode = EMode::RESULT;
      ofSetWindowTitle("RESULT");
      judge.end();
      sndMgr.stopBGM();
    }
    
    for (int i = 0; i < hostsConfig::NUM_OF_ROBOT; i++) {
      sysRbtMgr.setShot(i, mainRcvr.getData(i).operation.shot);
    }
    
    sysRbtMgr.update();
    sysPObjMgr.update();
//           vWllMgr.update();
    //      itmMgr.update();
    fxMgr.update();
    blltMgr.update();
    sndMgr.update();
    judge.update();
    
    box2d->update();
    
    //data sending ------------------
    
    //send to ctrlrs
    {
      static MRPMPackMainToCtrlr pack;
      pack.robsData = sysRbtMgr.getRobotDataVec();
      pack.bulletsPos = blltMgr.getPositionsVec();
      pack.timeSec = static_cast<int>(timer->getTime()/1000);
      pack.score = judge.getScore(TEAM_A);
      mainSndr.sendToCtrlrsSync(pack);
    }
    
    //send to each robot
    for(int i=0; i<hostsConfig::NUM_OF_ROBOT; ++i){
      static MRPMPackMainToRobot pack;
      auto roboData = sysRbtMgr.getData(i);
      pack.time = static_cast<int>(roboData.time);
      pack.pos = roboData.pos;
      pack.permissions.fill(true);  //とりあえず全部許可しとく
      
      //pack.permissions = checkMovability(roboData.pos);
      //TODO: 全許可で動作確認とれたら UNCOMMENT
      
      mainSndr.sendToOneRobot(i, pack);
    }
    
    
    //send to AIs
    static std::vector<Position> posVec;
    static std::array<int, NUM_OF_POINT_OBJ> poownerAry;
    posVec = sysRbtMgr.getPosVec();
    poownerAry = sysPObjMgr.getOwnersAry();
    
    
    for(Position& p: posVec){
      //for each AI (Dense)
      mainSndr.sendToOneAI(p);
    }
    
    static SparseExecutor syncToAIs
    (static_cast<int>(ofGetFrameRate()),
     [&](){
       MRPMPackMainToAI p;
       p.robsPos=posVec;
       p.POowners=poownerAry;
       mainSndr.sendToAIsSparse(p);
     });
    syncToAIs.touch();  //touch()するとmod回に1回実行される
    
    
    //sync judgement
    for(int i=0; i<hostsConfig::NUM_OF_ROBOT; ++i){
      judge.setRobotState(i, sysRbtMgr.getData(i).state);
    }
    for(int i=0; i<NUM_OF_POINT_OBJ; ++i){
      judge.setPOOwner(i, static_cast<ETeam>(poownerAry[i]));
    }
    
  }

}

void MRPMMainManager::draw() {
  pmx->drawTextureField();
  sysRbtMgr.draw();
  sysPObjMgr.draw();
//      vWllMgr.draw();
  //    itmMgr.draw();
  fxMgr.draw();
  blltMgr.draw();
  
  if (mode == EMode::RESULT) {
    pmx->drawTextField();
    switch (judge.getWinner()) {
      case TEAM_A:
        pmx->drawText("WIN", 100, 300, 49, ofColor(255, 120, 0, 200));
        break;
      case TEAM_B:
        pmx->drawText("LOSE", 100, 300, 49, ofColor(0, 120, 255, 200));
        break;
      case NEUTRAL:
        pmx->drawText("DRAW", 100, 300, 49, ofColor(0, 120, 0, 200));
        break;
    }
  } else if (mode == EMode::STANDBY) {
     //通信しないとモード遷移できないので、とりあえず文字は非表示にしておきます
//    pmx->drawTextField();
//    pmx->drawText("MRPM", 300, 150, 50, ofColor(220, 120, 0, 200));
//    pmx->drawText("Multi", 400, 180, 30, ofColor(220, 120, 0, 200));
//    pmx->drawText("Robots with", 450, 180, 30, ofColor(220, 120, 0, 200));
//    pmx->drawText("Projection", 500, 180, 30, ofColor(220, 120, 0, 200));
//    pmx->drawText("Mapping", 550, 180, 30, ofColor(220, 120, 0, 200));
  }
  
  //added by sakabe
  //カメラやビューポートと独立に描画したい
  pmx->drawLatticeIfNeeded();
}

void MRPMMainManager::keyPressed(int key) {
  if (key == 's') sim = !sim;
  switch (mode) {
    case EMode::STANDBY:
      if (key == OF_KEY_RETURN && mainRcvr.haveAllCtrlrsEntried()) {
//      if (key == OF_KEY_RETURN) {   //for debug
        mode = EMode::GAME;
        ofSetWindowTitle("GAME");
        sndMgr.startBGM();
        timer->init();
        sysRbtMgr.init();
        sysPObjMgr.init();
        blltMgr.init();
        fxMgr.init();
        judge.start();
      }
      break;
    case EMode::GAME:
      if (key == 'q') {
        mode = EMode::STANDBY;
        ofSetWindowTitle("STANDBY");
        mainRcvr.resetAckReceived();
        sndMgr.stopBGM();
        timer->init();
        sysRbtMgr.init();
        sysPObjMgr.init();
        blltMgr.init();
        fxMgr.init();
        judge.end();
      } else if (key == OF_KEY_RETURN) {
        //mode = RESULT;
        //ofSetWindowTitle("RESULT");
        //sndMgr.stopBGM();
      }
      break;
    case EMode::RESULT:
      if (key == OF_KEY_RETURN) {
        mode = EMode::STANDBY;
        ofSetWindowTitle("STANDBY");
        mainRcvr.resetAckReceived();
        sndMgr.stopBGM();
        timer->init();
        sysRbtMgr.init();
        sysPObjMgr.init();
        blltMgr.init();
        fxMgr.init();
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
