#include "FX.h"

void FX::init(Position _pos, EFX _FXType) {
	pos = _pos;
	FXType = _FXType;
  
  pmx = PMx::getInstance();
  
  switch (_FXType) {
    case HIT:
      size = 0;
      maxSize = 30;
      break;
    case COLLISION:
      size = 60;
      maxSize = 120;
      break;
    default:
      break;
  }
}

void FX::update() {
  switch (FXType) {
    case HIT:
      size += 2;
      if (size >= maxSize){
        deleteFlag = true;
      }
        break;
    case COLLISION:
      size +=6;
      if (size >= maxSize){
        deleteFlag = true;
      }
        break;
    default:
        break;
  }

}

void FX::draw() {
  switch (FXType) {
    case HIT:
      pmx->drawFX(ofVec2f(pos.y,pos.x), size, maxSize, FXType);
      break;
    case COLLISION:
      pmx->drawFX(ofVec2f(pos.y,pos.x), size, maxSize, FXType);
      break;
    default:
      break;
  }
}

bool FX::getDeleteFlag() {
	return deleteFlag;
}
