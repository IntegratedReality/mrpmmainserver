#pragma once

#include "Bullet.h"
#include "Position.h"
#include <vector>

class BulletManager {
public:
    void init();
    void update();
    void draw();
    static void makeBullet(Position _pos, ETeam _team, int _shooterID, bool _deathshot = false);
  std::vector<std::pair<Position, int>> getPositionsVec();
    std::vector<ofVec2f> getVelocitiesVec();
private:
    static std::vector<unique_ptr<Bullet>> bullets;
};
