#pragma once

#include "Bullet.h"
#include <vector>

class BulletManager {
	public:
		void init();
		void update();
		void draw();
		static void makeBullet(Position _pos, ETeam _team);
	private:
		static std::vector<Bullet*> bullets;
};
