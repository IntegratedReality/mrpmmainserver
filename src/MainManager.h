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
#include "SoundManager.h"
#include "Timer.h"
#include "EMode.h"
#include "Judge.h"
#include "PMx.h"

class MainManager {
public:
		void init();
		void update();
		void draw();
		void keyPressed(int key);
private:
		ofxBox2d *box2d;
  Timer *timer;
  PMx *PM;
  
		MainSender mainSndr;
		MainReceiver mainRcvr;
		SysRobotManager sysRbtMgr;
		SysPointObjectManager sysPObjMgr;
		ItemManager itmMgr;
		VirtualWallManager vWllMgr;
		BulletManager blltMgr;
		CollisionListener collisionListener;
		SoundManager sndMgr;
		Judge judge;
  
		int time;
		EMode mode;
};
