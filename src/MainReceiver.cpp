#include "MainReceiver.h"

void MainReceiver::init(int _port) {
	receiver.setup(_port);
}

void MainReceiver::update() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		if (m.getAddress() == "/position") {
			int id = m.getArgAsInt32(0);
			int time = m.getArgAsInt32(1);
			double x = m.getArgAsDouble(2);
			double y = m.getArgAsDouble(3);
			double theta = m.getArgAsDouble(4);
			data[id].time = time;
			data[id].pos.x = x;
			data[id].pos.y = y;
			data[id].pos.theta = theta;
		}
	}
}

RobotData MainReceiver::getData(int _id) {
	return data[_id];
}
