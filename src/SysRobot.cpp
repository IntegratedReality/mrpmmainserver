#include "ofApp.h"
#include "SysRobot.h"
#include "BulletManager.h"
#include "SoundManager.h"
#include "SysBox2D.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAX_HP 100
#define MAX_ENG 100

#define ENG_TO_SHOT 33

#define GAIN_HP_KAIHUKU 0.03
#define GAIN_ENG_KAIHUKU 0.02

#define TIME_SHOT_TO_SHOT 500
#define TIME_DEAD_TO_RECOVERY 6000
#define TIME_RECOVERY_TO_NORMAL 3000

void SysRobot::init(int _id, ETeam _team) {
  type = ROBOT;
  data.id = _id;
  data.team = _team;
  team = _team;
  
  HP = MAX_HP;
  energy = 100;
  
  recoveryTime = 0;
  coolTime = 0;
  thermo = 0;
  
  if (isinit) return;
  b2dCircle.setPhysics(3.0, 0.53, 0.1);
  b2dCircle.fixture.isSensor = true; // 衝突検知のみを行う
  b2dCircle.setup(SysBox2D::getInstance()->getWorld(), data.pos.x, data.pos.y, RADIUS_OF_ROBOT + 10);
  b2dCircle.setData(this);
  isinit = true;
  
  pmx = PMx::getInstance();
  pmx-> initRobot(_id, _team);
  
  timer = Timer::getInstance();
}

void SysRobot::setPos(Position _pos) {
  data.pos= _pos;
}

void SysRobot::setState(EState _state) {
  data.state = _state;
}

void SysRobot::setShot(bool _shot) {
  data.operation.shot = _shot;
}

void SysRobot::sufferDamage(int _damage) {
  HP -= _damage - 1;
  thermo = 1000;
}

void SysRobot::update() {
  // 当たり判定用オブジェクト座標の更新
  b2dCircle.setPosition(data.pos.x, data.pos.y);
  
  if (data.item != NO_ITEM) {
    itemTime++;
    if (itemTime >= 300) {
      itemTime = 0;
      data.item = NO_ITEM;
    }
  }
  
  // ステート毎の処理
  switch (data.state) {
    case DEAD:
      deadTime += timer->getDiff();
      if (deadTime >= TIME_DEAD_TO_RECOVERY) {
        data.state = RECOVERY;
        deadTime = 0;
        HP = MAX_HP;
        coolTime = 0;
        thermo = 0;
        energy = 100;
      }
      break;
      
    case RECOVERY:
      recoveryTime += timer->getDiff();
      if (recoveryTime >= TIME_RECOVERY_TO_NORMAL) {
        data.state = NORMAL;
        recoveryTime = 0;
      }
      // breakせず下に続く
      
    case NORMAL:
      if (HP <= 0) {
        HP = 0;
        data.state = DEAD;
        Position p = data.pos;
        for (int i = 0; i < 8; i++) {
          p.theta += M_PI / 4;
          BulletManager::makeBullet(p, (ETeam)!team, true);
        }
        break;
      }
      
      // 体力の自然回復と放熱
      if (thermo == 0 && HP < MAX_HP) HP += timer->getDiff() * GAIN_HP_KAIHUKU;
      else thermo = max(0, thermo - timer->getDiff());
      
      // 弾の生成
      if (data.operation.shot && coolTime == 0 && energy >= ENG_TO_SHOT) {
        SoundManager::makeSE(SHOT);
        BulletManager::makeBullet(data.pos, team);
        coolTime = TIME_SHOT_TO_SHOT;
        energy -= ENG_TO_SHOT;
      } else {
        if (coolTime != 0) coolTime = 0 > coolTime - timer->getDiff() ? 0 : coolTime - timer->getDiff();
        if (energy < 100) energy = min(100., energy + timer->getDiff() * GAIN_ENG_KAIHUKU);
      }
      
      break;
    default:;
  }
}

void SysRobot::draw() {
  Position& p = data.pos;
  double r = RADIUS_OF_ROBOT;
  
  ofSetColor(255 * (data.team == TEAM_A), 0, 255 * (data.team == TEAM_B), 255);
  if (sim){
    ofDrawLine(p.x * SCALE, p.y * SCALE, (p.x + r * cos(p.theta)) * SCALE, (p.y + r * sin(p.theta)) * SCALE);
  }
  
  if (data.state == DEAD){
    ofSetColor(50, 50, 50, 255);
  }
  else if (data.state == RECOVERY) {
    ofSetColor(255, 255, 0, 255);
  }
  else {
  ofSetColor(255, 255 * HP / MAX_HP, 255 * HP / MAX_HP, 255);
  }
  
  if (sim) {
    ofDrawCircle(p.x * SCALE, p.y * SCALE, r * SCALE);
  }
  
  ofSetColor(255, 255, 255, 255);
  
  pmx->drawRobot(p.x, p.y, p.theta, &data);
}

int SysRobot::getId() {
  return data.id;
}

RobotData SysRobot::getData() {
  data.HP = HP;
  data.EN = energy;
  return data;
}

// override CollisionObject
void SysRobot::collisionListner(CollisionObject *other) {
  switch (other->getType()) {
    case BULLET:
      if (data.state != DEAD && data.state != RECOVERY && team != other->getTeam()) {
        sufferDamage(other->getValue());
        SoundManager::makeSE(DAMAGE);
      }
      break;
    case ITEM:
      data.item = (EItem)other->getValue();
      itemTime = 0;
      break;
    default:;
  }
}
