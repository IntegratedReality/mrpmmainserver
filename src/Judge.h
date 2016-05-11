#pragma once

#include "ETeam.h"
#include "EState.h"
#include "Timer.h"

class Judge {
	public:
		void init();
		void update();
		int getScore(ETeam _team);
		void setPOOwner(int _id, ETeam _owner);
		void setRobotState(int _id, EState _state);
		void start();
		ETeam end();
	private:
		bool playing;
		double score[2];
		ETeam POOwner[3];
		EState robotState[6];
		Timer *timer;
};
