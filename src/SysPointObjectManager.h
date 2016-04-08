#pragma once

#include "Const.h"
#include "SysPointObject.h"

class SysPointObjectManager {
	public:
		void init();
		void update();
		void draw();
	private:
		SysPointObject pObjs[NUM_OF_POINT_OBJ];
};
