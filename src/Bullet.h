#pragma once

#include "Position.h"
#include "ofxBox2d.h"
#include "CollisionObject.h"
#include "Timer.h"
#include "PMx.h"
#include "FXManager.h"

class Bullet : public CollisionObject{
public:
    void init(Position _pos, ETeam _team, int _shooterID, bool _deathshot = false);
    void update();
    void draw();
    bool getDeleteFlag();
    
    // override CollisionObject
    virtual void collisionListner(CollisionObject *other);
    virtual int getValue();
    
    inline Position getPosition(){
        return pos;
    }
    inline ofVec2f getVelocity(){
        return vel;
    }
    inline int getShooterID(){
        return shooterID;
    }
private:
    int shooterID;
    PMx *PM;
    int radius;
    int count;
    Position pos;
    ofVec2f vel;
    ofxBox2dCircle b2dCircle;
    bool deleteFlag;
    int damage;
    Timer *timer;
    
    int sustain;
};
