#include "VirtualWall.h"
#include "SysBox2D.h"
#include "Const.h"
#include <cmath>

void VirtualWall::init(int _id) {
  PM = PMx::getInstance();
  
  type = VIRTUAL_WALL;
  h = 50, w = 300;
//  if (_id == 0) y = 500, x = 1000;
  if (_id == 0) y = 300, x = 400;
  else if (_id == 1) x = 400-w, y = 900;
  b2dRect.setPhysics(3.0, 0.53, 0.1);
  this->b2dRect.fixture.isSensor = true; // 衝突検知のみを行う
  this->b2dRect.setup(SysBox2D::getInstance()->getWorld(), x + w / 2, y + h / 2, w, h);
  b2dRect.setData(this);
  
}

void VirtualWall::update() {
  b2dRect.setPosition(x + w / 2, y + h / 2);
}

void VirtualWall::draw() {
  if(sim){
    ofPushStyle();
    ofSetColor(255, 255, 255, 100);
    ofDrawRectangle(x * SCALE, y * SCALE, w * SCALE, h * SCALE);
    ofPopStyle();
  }
  
  ofPushStyle();
  ofSetColor(0,0,0,140);
  PM->drawVWall(x, y, w, h);
  //    ofDrawRectangle(x, y, w, h);
  ofPopStyle();
}

void VirtualWall::collisionListner(CollisionObject *other) {
  
}
