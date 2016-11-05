#include "Bullet.h"
#include "ofApp.h"
#include "Const.h"
#include "SysBox2D.h"
#include <cmath>
#include <iostream>
using namespace std;

void Bullet::init(Position _pos, ETeam _team, bool _deathshot) {
  type = BULLET;
  team = _team;
  damage = 50;
  deleteFlag = false;
  this->pos = _pos;
  this->count = 0;
  this->radius = 25;
  
  if (_deathshot) {
    sustain = 70;
  } else {
    sustain = 330;
  }
  
  b2dCircle.setPhysics(3.0, 0.53, 0.1);
  this->b2dCircle.fixture.isSensor = true; // 衝突検知のみを行う
  this->b2dCircle.setup(SysBox2D::getInstance()->getWorld(), pos.x, pos.y, radius - 5);
  //b2dCircle.body->SetBullet(true);
  b2dCircle.setData(this);
  timer = Timer::getInstance();
  
  PM = PMx::getInstance();
}

void Bullet::update() {
  this->count += timer->getDiff();
  b2dCircle.setVelocity(50 * cos(pos.theta), 50 * sin(pos.theta));
  vel={static_cast<float>(50 * cos(pos.theta)),
    static_cast<float>(50 * sin(pos.theta))};
  pos.x = b2dCircle.getPosition().x;
  pos.y = b2dCircle.getPosition().y;
  //int v = 1000;
  //pos.x += v * cos(pos.theta) * TIME_PER_FRAME;
  //pos.y += v * sin(pos.theta) * TIME_PER_FRAME;
  //b2dCircle.setPosition(pos.x, pos.y);
}

void Bullet::draw() {
  if (deleteFlag) return;
  Position &p = this->pos;
  ofSetColor(255 * (team == TEAM_A), 120, 255 * (team == TEAM_B), 255);
  //ofFill();
  if (sim) ofDrawCircle(p.x * SCALE_SIM, p.y * SCALE_SIM, radius * SCALE_SIM);
  //ofNoFill();
  PM->drawBullet(p.x, p.y, 0, team);
}

bool Bullet::getDeleteFlag() {
  deleteFlag |= count > sustain;
  deleteFlag |= pos.x < 0 || WIDTH_OF_FIELD < pos.x;
  deleteFlag |= pos.y < 0 || HEIGHT_OF_FIELD < pos.y;
  return deleteFlag;
}

// override CollisionObject
void Bullet::collisionListner(CollisionObject *other) {
  switch (other->getType()) {
    case ROBOT:
      deleteFlag = true;
      break;
    case POINT_OBJ:
      deleteFlag = true;
      break;
    case VIRTUAL_WALL:
      deleteFlag = true;
      break;
    case BULLET:
      if (team != other->getTeam()) deleteFlag = true;
      break;
    case ITEM:
      ;
  }
}

int Bullet::getValue() {
  return damage;
}
