#pragma once

#include "MainSender.h"
#include "MainReceiver.h"
#include "SysRobotManager.h"
#include "SysPointObjectManager.h"
#include "BulletManager.h"
#include "ItemManager.h"
#include "VirtualWallManager.h"
#include "SysBox2D.h"
#include "CollisionListener.h"

class MainManager {
	public:
		void init();
		void update();
		void draw();
	private:
		ofxBox2d *box2d;
		MainSender mainSndr;
		MainReceiver mainRcvr;
		SysRobotManager sysRbtMgr;
		SysPointObjectManager sysPObjMgr;
		int time;
		ItemManager itmMgr;
		VirtualWallManager vWllMgr;
		BulletManager blltMgr;
		CollisionListener collisionListener;
};
