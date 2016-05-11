#include "SysPointObjectManager.h"

void SysPointObjectManager::init() {
	for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
		pObjs[i].init(i);
	}
}

void SysPointObjectManager::update() {
	for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
		pObjs[i].update();
	}
}

void SysPointObjectManager::draw() {
	for (int i = 0; i < NUM_OF_POINT_OBJ; i++) {
		pObjs[i].draw();
	}
}

ETeam SysPointObjectManager::getOwner(int _id) {
	return pObjs[_id].getOwner();
}

double SysPointObjectManager::getTeamPoint(int _id, ETeam _team) {
	return pObjs[_id].getTeamPoint(_team);
}
