#pragma once

#include "Position.h"
#include "ofxBox2D.h"
#include "CollisionObject.h"

class Bullet : public CollisionObject{
	public:
		void init(Position _pos, ETeam _team);
		void update();
		void draw();
		bool getDeleteFlag();

		// override CollisionObject
		virtual void collisionListner(CollisionObject *other);
		virtual int getValue();
	private:
		int radius;
		int count;
		Position pos;
		ofxBox2dCircle b2dCircle;
		bool deleteFlag;
		int damage;
};
