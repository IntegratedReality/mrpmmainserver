#include "MainSender.h"

void MainSender::init() {
	sender[0].setup("mrpmpi0.local", PORT);
	sender[1].setup("mrpmpi1.local", PORT);
	sender[2].setup("mrpmpi2.local", PORT);
	sender[3].setup("mrpmpi3.local", PORT);
	sender[4].setup("mrpmpi4.local", PORT);
	sender[5].setup("mrpmpi5.local", PORT);
	sender[6].setup("PE25.local", PORT);
	sender[7].setup("PE26.local", PORT);
	sender[8].setup("PE27.local", PORT);
}

void MainSender::sendData(int _id, int _time, double _x, double _y, double _theta, double _HP, double _EN) {
	ofxOscMessage m;
	m.setAddress("/main/position");
	m.addInt32Arg(_id);
	m.addInt32Arg(_time);
	m.addDoubleArg(_x);
	m.addDoubleArg(_y);
	m.addDoubleArg(_theta);
	m.addDoubleArg(_HP);
	m.addDoubleArg(_EN);
	for (int i = 0; i < NUM_OF_ROBOT + 3; i++) {
		sender[i].sendMessage(m);
	}
}

void MainSender::sendPOOwner(int _id, ETeam _team) {
	ofxOscMessage m;
	m.setAddress("/main/poowner");
	m.addInt32Arg(_id);
	m.addInt32Arg((int)_team);
	for (int i = 0; i < NUM_OF_ROBOT + 3; i++) {
		sender[i].sendMessage(m);
	}
}
