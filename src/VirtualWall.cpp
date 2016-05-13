#include "VirtualWall.h"
#include "SysBox2D.h"
#include "Const.h"
#include <cmath>

void VirtualWall::init(int _id) {
    PM = PMx::getInstance();
    
    type = VIRTUAL_WALL;
	h = 50, w = 400;
	if (_id == 0) y = 300, x = 800;
	else if (_id == 1) x = 300, y = 2400;
	b2dRect.setPhysics(3.0, 0.53, 0.1);
	this->b2dRect.fixture.isSensor = true; // 衝突検知のみを行う
	this->b2dRect.setup(SysBox2D::getInstance()->getWorld(), x + w / 2, y + h / 2, w, h);
	b2dRect.setData(this);
    
}

void VirtualWall::update() {
	b2dRect.setPosition(x + w / 2, y + h / 2);
}

void VirtualWall::draw() {
	ofSetColor(255, 255, 255, 100);
	ofDrawRectangle(x * SCALE, y * SCALE, w * SCALE, h * SCALE);
	ofSetColor(255, 255, 255, 255);
    
    ofPushStyle();
    ofSetColor(0,0,0,140);
    PM->drawVWall(x, y, w, h);
//    ofDrawRectangle(x, y, w, h);
    ofPopStyle();
}

void VirtualWall::collisionListner(CollisionObject *other) {

}
