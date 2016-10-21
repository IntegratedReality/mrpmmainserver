#pragma once

#include "FX.h"
#include "EFX.h"
#include <vector>

class FXManager {
public:
		void init();
		void update();
		void draw();
		static void makeFX(Position _pos, EFX _FX);
private:
		static std::vector<FX*> FXs;
};
