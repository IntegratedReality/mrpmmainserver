#include "FXManager.h"

std::vector<FX*> FXManager::FXs;

void FXManager::init() {

}

void FXManager::update() {
	for (auto fx : FXManager::FXs) {
		fx->update();
	}
	for (int i = 0; i < FXManager::FXs.size(); i++) {
		if (FXManager::FXs[i]->getDeleteFlag()) {
			delete FXManager::FXs[i];
			FXManager::FXs.erase(FXManager::FXs.begin() + i);
		}
	}
}

void FXManager::draw() {
	for (auto FX : FXManager::FXs) {
		FX->draw();
	}
}

void FXManager::makeFX(Position _pos, EFX _FX) {
	FX *fx = new FX();
	fx->init(_pos, _FX);
	FXManager::FXs.push_back(fx);
}
