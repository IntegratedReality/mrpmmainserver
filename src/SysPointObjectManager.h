#pragma once

#include "Const.h"
#include "SysPointObject.h"

class SysPointObjectManager {
	public:
		void init();
		void update();
		void draw();
		ETeam getOwner(int _id);
		double getTeamPoint(int _id, ETeam _team);
	private:
		SysPointObject pObjs[NUM_OF_POINT_OBJ];
};
