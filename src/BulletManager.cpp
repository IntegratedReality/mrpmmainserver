#include "BulletManager.h"
#include "Const.h"
#include <cmath>

using namespace std;

void BulletManager::init() {

}

void BulletManager::update() {
	for (auto bullet : BulletManager::bullets) {
		bullet->update();
	}
	for (int i = 0; i < BulletManager::bullets.size(); i++) {
		if (BulletManager::bullets[i]->getDeleteFlag()) {
			delete BulletManager::bullets[i];
			BulletManager::bullets.erase(BulletManager::bullets.begin() + i);
		}
	}
}

void BulletManager::draw() {
	for (auto bullet : BulletManager::bullets) {
		bullet->draw();
	}
}

vector<Bullet*> BulletManager::bullets;

void BulletManager::makeBullet(Position _pos, ETeam _team) {
	Bullet *bullet = new Bullet();
	_pos.x += (RADIUS_OF_POINT_OBJ + 10) * cos(_pos.theta);
	_pos.y += (RADIUS_OF_POINT_OBJ + 10) * sin(_pos.theta);
	bullet->init(_pos, _team);
	BulletManager::bullets.push_back(bullet);
}
