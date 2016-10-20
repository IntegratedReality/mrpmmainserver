#include "Judge.h"
#include <iostream>
using namespace std;

constexpr int GAIN_KILL = 100;
constexpr double GAIN_OWN  = 0.01;
constexpr int GAIN_BONUS = 500;

void Judge::init() {
	playing = false;
	for (int i = 0; i < 3; i++) {
		POOwner[i] = NEUTRAL;
	}
	for (int i = 0; i < 6; i++) {
		robotState[i] = NORMAL;
	}
	score[0] = 0;
	score[1] = 0;
	timer = Timer::getInstance();
}

void Judge::update() {
	cout << "HUMAN: " << score[0];
	cout << " | AI: " << score[1] << endl;
}

int Judge::getScore(ETeam _team) {
	return (int)score[(int)_team];
}

void Judge::setPOOwner(int _id, ETeam _owner) {
	POOwner[_id] = _owner;
	switch (_owner) {
		case TEAM_A:
			score[0] += timer->getDiff() * GAIN_OWN;
			break;
		case TEAM_B:
			score[1] += timer->getDiff() * GAIN_OWN;
			break;
    case NEUTRAL:;
	}
}

void Judge::setRobotState(int _id, EState _state) {
	if (robotState[_id] == NORMAL && _state == DEAD) {
		if (_id < 3) score[1] += GAIN_KILL;
		else if (_id >= 3) score[0] += GAIN_KILL;
	}
	robotState[_id] = _state;
}

void Judge::start() {
	init();
	playing = true;
}

ETeam Judge::end() {
	playing = false;
	for (int i = 0; i < 3; i++) {
		switch (POOwner[i]) {
			case TEAM_A:
				score[0] += GAIN_BONUS;
				break;
			case TEAM_B:
				score[1] += GAIN_BONUS;
				break;
      default:;
		}
	}
	cout << "HUMAN: " << score[0];
	cout << " | AI: " << score[1] << endl;
	if (score[TEAM_A] > score[TEAM_B]) {
		cout << "HUMAN win" << endl;
		return TEAM_A;
	}
	else if (score[TEAM_A] < score[TEAM_B]) {
		cout << "AI win" << endl;
		return TEAM_B;
	}
	else if (score[TEAM_A] == score[TEAM_B]) {
		cout << "draw" << endl;
		return NEUTRAL;
	}
}

ETeam Judge::getWinner() {
	if (score[TEAM_A] > score[TEAM_B]) {
		cout << "HUMAN win" << endl;
		return TEAM_A;
	}
	else if (score[TEAM_A] < score[TEAM_B]) {
		cout << "AI win" << endl;
		return TEAM_B;
	}
	else if (score[TEAM_A] == score[TEAM_B]) {
		cout << "draw" << endl;
		return NEUTRAL;
	}
}
