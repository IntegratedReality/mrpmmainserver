#pragma once

#include "Const.h"
#include "RobotData.h"
#include "ofxOscReceiver.h"

class MainReceiver {
	public:
		void init(int _port);
		void update();
		RobotData getData(int _id);
	private:
		ofxOscReceiver receiver;
		RobotData data[NUM_OF_ROBOT];
};
