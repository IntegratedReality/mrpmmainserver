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

std::array<int, NUM_OF_POINT_OBJ>
SysPointObjectManager::getOwnersAry(){
  std::array<int, NUM_OF_POINT_OBJ> ary;
  for(int i=0; i<NUM_OF_POINT_OBJ; ++i){
    ary[i] = static_cast<int>(getOwner(i));
  }
  return ary;
}

double SysPointObjectManager::getTeamPoint(int _id, ETeam _team) {
  return pObjs[_id].getTeamPoint(_team);
}
