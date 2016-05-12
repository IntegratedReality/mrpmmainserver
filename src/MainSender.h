#pragma once

#include "Const.h"
#include "ofxOsc.h"
#include "ETeam.h"
#include "EState.h"

class MainSender {
	public:
		void init();
		// 一度のsendDataで全てのロボットにデータが送信されます
		void sendData(int _id, int _time, double _x, double _y, double _theta, double _HP, double _EN, EState _state);
		void sendPOOwner(int _id, ETeam _team);
	private:
		ofxOscSender sender[NUM_OF_ROBOT + 3];
};
