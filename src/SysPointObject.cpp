#include "SysPointObject.h"
#include "ofApp.h"
#include "SysBox2D.h"

#define ALL_OF_POINT 7
#define POINT_TO_OWN 5

void SysPointObject::init(int _id) {
	type = POINT_OBJ;
	this->id = _id;
	point[TEAM_A] = 0;
	point[TEAM_B] = 0;
	switch (this->id) {
		case 0:
			pos.x = POINT_OBJ_0_X;
			pos.y = POINT_OBJ_0_Y;
			break;
		case 1:
			pos.x = POINT_OBJ_1_X;
			pos.y = POINT_OBJ_1_Y;
			break;
		case 2:
			pos.x = POINT_OBJ_2_X;
			pos.y = POINT_OBJ_2_Y;
			break;
	}
	b2dCircle.setPhysics(3.0, 0.53, 0.1);
	this->b2dCircle.fixture.isSensor = true; // 衝突検知のみを行う
	this->b2dCircle.setup(SysBox2D::getInstance()->getWorld(), pos.x, pos.y, RADIUS_OF_POINT_OBJ);
	b2dCircle.setData(this);

	PM = PMx::getInstance();
}

void SysPointObject::update() {
}

void SysPointObject::draw() {
	ofFill();
	if (getOwner() == TEAM_A) ofSetColor(255, 0, 0, 255);
	else if (getOwner() == TEAM_B) ofSetColor(0, 0, 255, 255);
	ofDrawCircle(pos.x * SCALE, pos.y * SCALE, RADIUS_OF_POINT_OBJ * SCALE);
	ofSetColor(255, 255, 255, 255);
	ofNoFill();

	ofFill();
	PM->drawPO(id);
}

ETeam SysPointObject::getOwner() {
	if (point[TEAM_A] >= POINT_TO_OWN) return TEAM_A;
	else if (point[TEAM_B] >= POINT_TO_OWN) return TEAM_B;
	else return NEUTRAL;
}

// override CollisionObject::collisionListner
void SysPointObject::collisionListner(CollisionObject *other) {
	switch (other->getType()) {
		case BULLET:
			changePoint(other->getTeam(), 1);
			break;
	}
}

void SysPointObject::changePoint(ETeam _team, int _point) {
	point[_team] += _point;
	if (point[_team] > ALL_OF_POINT) point[_team] = ALL_OF_POINT;
	if (point[TEAM_A] + point[TEAM_B] > ALL_OF_POINT) point[!_team] = ALL_OF_POINT - point[_team];
}
