#pragma once

#include "Position.h"
#include "ofxBox2d.h"
#include "CollisionObject.h"
#include "Timer.h"
#include "PMx.h"

class Bullet : public CollisionObject{
public:
    void init(Position _pos, ETeam _team, bool _deathshot = false);
    void update();
    void draw();
    bool getDeleteFlag();
    
    // override CollisionObject
    virtual void collisionListner(CollisionObject *other);
    virtual int getValue();
private:
    PMx *PM;
    int radius;
    int count;
    Position pos;
    ofxBox2dCircle b2dCircle;
    bool deleteFlag;
    int damage;
    Timer *timer;
    
    int sustain;
};
