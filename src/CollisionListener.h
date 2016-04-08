#pragma once

#include "ofxBox2D.h"

class CollisionListener : public b2ContactListener {
	public:
		void BeginContact(b2Contact* contact) {
			CollisionObject *a = (CollisionObject*)contact->GetFixtureA()->GetBody()->GetUserData();
			CollisionObject *b = (CollisionObject*)contact->GetFixtureB()->GetBody()->GetUserData();
			a->collisionListner(b);
			b->collisionListner(a);
		}
};
