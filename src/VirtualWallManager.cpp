#include "VirtualWallManager.h"

void VirtualWallManager::init() {
	vWalls[0].init(0);
	vWalls[1].init(1);
}

void VirtualWallManager::update() {
	vWalls[0].update();
	vWalls[1].update();
}

void VirtualWallManager::draw() {
	vWalls[0].draw();
	vWalls[1].draw();
}
