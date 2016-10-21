#include "SysRobotManager.h"

void SysRobotManager::init() {
  for (int i = 0; i < NUM_OF_ROBOT; i++) {
    sysRobots[i].init(i, (i < 3 ? TEAM_A : TEAM_B));
  }
}

void SysRobotManager::update() {
  for (int i = 0; i < NUM_OF_ROBOT; i++) {
    sysRobots[i].update();
  }
}

void SysRobotManager::draw() {
  for (int i = 0; i < NUM_OF_ROBOT; i++) {
    sysRobots[i].draw();
  }
}

void SysRobotManager::setPos(int _id, Position _pos) {
  sysRobots[_id].setPos(_pos);
}

void SysRobotManager::setShot(int _id, bool _shot) {
  sysRobots[_id].setShot(_shot);
}

RobotData SysRobotManager::getData(int _id) {
  return sysRobots[_id].getData();
}
