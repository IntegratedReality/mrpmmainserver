#include "Const.h"
#include "Item.h"
#include "SysBox2D.h"

void Item::init(Position _pos, EItem _item) {
	type = ITEM;
	x = _pos.x;
	y = _pos.y;
	radius = 50;
	itemType = _item;
	deleteFlag = false;

	b2dCircle.setPhysics(3.0, 0.53, 0.1);
	this->b2dCircle.fixture.isSensor = true; // 衝突検知のみを行う
	this->b2dCircle.setup(SysBox2D::getInstance()->getWorld(), x, y, radius);
	//b2dCircle.body->SetBullet(true);
	b2dCircle.setData(this);
}

void Item::update() {

}

void Item::draw() {
	ofSetColor(0, 255, 0, 255);
	ofDrawCircle(x * SCALE, y * SCALE, radius * SCALE);
	ofSetColor(255, 255, 255, 255);
}

void Item::collisionListner(CollisionObject *other) {
	switch (other->getType()) {
		case ROBOT:
			deleteFlag = true;
			break;
    default:;
	}
}

int Item::getValue() {
	return (int)itemType;
}
