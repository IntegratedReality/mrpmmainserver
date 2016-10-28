#pragma once

#include "Const.h"
#include "SysRobot.h"
#include "MRPMMainReceiver.h"
#include "MRPMHostsConfig.h"

class SysRobotManager {
public:
		void init();
		void update();
		void draw();
		void setPos(int _id, Position _pos);
		void setShot(int _id, bool _shot);
		RobotData getData(int _id);
private:
    std::vector<SysRobot> sysRobots;
};
