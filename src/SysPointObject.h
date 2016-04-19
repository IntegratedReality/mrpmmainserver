#pragma once

#include "Position.h"
#include "ofxBox2d.h"
#include "CollisionObject.h"
#include "PMx.h"

class SysPointObject : public CollisionObject {
	public:
		void init(int _id);
		void update();
		void draw();
		ETeam getOwner();
		
		// override CollisionObject
		virtual void collisionListner(CollisionObject *other);
	private:
		int id;
		Position pos;
		ofxBox2dCircle b2dCircle;
		PMx *PM;

		void changePoint(ETeam _team, int _point);
		int point[2];
};
