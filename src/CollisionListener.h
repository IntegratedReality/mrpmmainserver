#pragma once

#include "ofxBox2d.h"

class CollisionListener : public b2ContactListener {
public:
		void BeginContact(b2Contact* contact) {
      CollisionObject *a = (CollisionObject*)contact->GetFixtureA()->GetBody()->GetUserData();
      CollisionObject *b = (CollisionObject*)contact->GetFixtureB()->GetBody()->GetUserData();
      a->collisionListner(b);
      b->collisionListner(a);
//      b2WorldManifold manif;
//      contact -> GetWorldManifold(&manif);
//      cout << manif.normal.x << ", " << manif.normal.y << endl;
//      cout << float(manif.points[0].x) << ", " << float(manif.points[0].y) << endl;
    }
};
