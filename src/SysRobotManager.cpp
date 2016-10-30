#include "SysRobotManager.h"

void SysRobotManager::init() {
  sysRobots.resize(hostsConfig::NUM_OF_ROBOT);
  for(int i=0; i<sysRobots.size(); ++i){
    sysRobots[i].init
    (i, (i < hostsConfig::NUM_OF_HUMAN ? TEAM_A : TEAM_B));
  }
}

void SysRobotManager::update() {
  for (auto& e: sysRobots) {
    e.update();
  }
}

void SysRobotManager::draw() {
  for (auto& e: sysRobots) {
    e.draw();
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

std::vector<Position> SysRobotManager::getPosVec(){
  std::vector<Position> vec;
  for(auto& e:sysRobots){
    vec.push_back(e.getData().pos);
  }
  return vec;
}
