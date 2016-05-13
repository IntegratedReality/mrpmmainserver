#include "FX.h"

void FX::init(Position _pos, EFX _FXType) {
	pos = _pos;
	FXType = _FXType;
	img.load("fx.png");
}

void FX::update() {

}

void FX::draw() {

}

bool FX::getDeleteFlag() {
	return deleteFlag;
}
