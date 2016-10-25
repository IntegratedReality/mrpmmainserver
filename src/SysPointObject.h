#pragma once

#include "Position.h"
#include "ofxBox2d.h"
#include "CollisionObject.h"
#include "PMx.h"

class SysPointObject : public CollisionObject {
public:
    SysPointObject() {
        isinit = false;
    }
    
    void init(int _id);
    void update();
    void draw();
    ETeam getOwner();
    double getTeamPoint(ETeam _team);
    
    // override CollisionObject
    virtual void collisionListner(CollisionObject *other);
private:
    int id;
    Position pos;
    ofxBox2dCircle b2dCircle;
    PMx *pmx;
    
    void changePoint(ETeam _team, int _point);
    int point[2];
    
    bool isinit;
};
