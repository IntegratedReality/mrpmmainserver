#pragma once

#include "Const.h"
#include "ofxOsc.h"

class MainSender {
	public:
		void init();
		// 一度のsendDataで全てのロボットにデータが送信されます
		void sendData(int _id, int _time, double _x, double _y, double _theta);
	private:
		ofxOscSender sender[NUM_OF_ROBOT];
};
