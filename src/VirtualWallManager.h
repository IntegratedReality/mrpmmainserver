#pragma once

#include "VirtualWall.h"

class VirtualWallManager {
public:
  void init();
  void update();
  void draw();
private:
  VirtualWall vWalls[2];
};
