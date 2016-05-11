#pragma once

#include "Position.h"
#include "ETeam.h"
#include "EState.h"
#include "EItem.h"
#include "Operation.h"

struct RobotData {
	int id; // A:0~2 B:3~5
	ETeam team;
	EState state;
	EItem item;
	Position pos;
	Operation operation;
	long time;
	int HP;
	int EG;
};
