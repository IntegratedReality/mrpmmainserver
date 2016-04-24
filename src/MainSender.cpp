#include "MainSender.h"

void MainSender::init() {
	sender[0].setup("mrpmpi2.local", PORT);
	sender[1].setup("mrpmpi3.local", PORT);
	sender[2].setup("mrpmpi4.local", PORT);
	sender[3].setup("mrpmpi5.local", PORT);
	sender[4].setup("mrpmpi6.local", PORT);
	sender[5].setup("mrpmpi7.local", PORT);
}

void MainSender::sendData(int _id, int _time, double _x, double _y, double _theta) {
	ofxOscMessage m;
	m.setAddress("/position");
	m.addInt32Arg(_id);
	m.addInt32Arg(_time);
	m.addDoubleArg(_x);
	m.addDoubleArg(_y);
	m.addDoubleArg(_theta);
	for (int i = 0; i < NUM_OF_ROBOT; i++) {
		sender[i].sendMessage(m);
	}
}
