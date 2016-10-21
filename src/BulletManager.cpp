#include "BulletManager.h"
#include "Const.h"
#include <cmath>
#include <iostream>

using namespace std;

void BulletManager::init() {
  for (int i = 0; i < BulletManager::bullets.size(); i++) {
    if (BulletManager::bullets[i] != nullptr) delete BulletManager::bullets[i];
  }
  BulletManager::bullets.clear();
}

void BulletManager::update() {
  for (int i = 0; i < BulletManager::bullets.size(); i++) {
    BulletManager::bullets[i]->update();
  }
  for (int i = 0; i < BulletManager::bullets.size(); i++) {
    if (BulletManager::bullets[i]->getDeleteFlag()) {
      delete BulletManager::bullets[i];
      BulletManager::bullets.erase(BulletManager::bullets.begin() + i);
    }
  }
}

void BulletManager::draw() {
  for (int i = 0; i < BulletManager::bullets.size(); i++) {
    BulletManager::bullets[i]->draw();
  }
}

vector<Bullet*> BulletManager::bullets;

void BulletManager::makeBullet(Position _pos, ETeam _team, bool _deathshot) {
  Bullet *bullet = new Bullet();
  _pos.x += (RADIUS_OF_POINT_OBJ + 10) * cos(_pos.theta);
  _pos.y += (RADIUS_OF_POINT_OBJ + 10) * sin(_pos.theta);
  bullet->init(_pos, _team, _deathshot);
  BulletManager::bullets.push_back(bullet);
}
