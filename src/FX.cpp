#include "FX.h"

void FX::init(Position _pos, EFX _FXType) {
	pos = _pos;
	FXType = _FXType;
  
  pmx = PMx::getInstance();
  
  switch (_FXType) {
    case HIT:
      break;
    case COLLISION:
      size = 0;
    default:
      break;
  }
}

void FX::update() {
  switch (FXType) {
    case HIT:
        break;
    case COLLISION:
      size +=5;
      if (size >= 100){
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
      break;
    case COLLISION:
      pmx->drawFX(ofVec2f(pos.y,pos.x), size, FXType);
      break;
    default:
      break;
  }
}

bool FX::getDeleteFlag() {
	return deleteFlag;
}
