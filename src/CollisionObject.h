#pragma once

#include "EType.h"
#include "ETeam.h"

class CollisionObject {
	public:
		virtual void collisionListner(CollisionObject *other) = 0;
		virtual int getValue() {return 0;}
		EType getType() {return type;}
		ETeam getTeam() {return team;}
	protected:
		EType type;
		ETeam team;
};
