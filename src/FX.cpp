#include "FX.h"

void FX::init(Position _pos, EFX _FXType) {
	pos = _pos;
	FXType = _FXType;
	img.load("fx.png");
  
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
      size +=2;
      if (size >= 300){
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
      ofPushStyle();
      ofSetLineWidth(3);
      ofSetColor(255, 200, 0);
      ofDrawCircle(pos.x, pos.y, size);
      ofPopStyle();
      break;
    default:
      break;
  }
}

bool FX::getDeleteFlag() {
	return deleteFlag;
}
