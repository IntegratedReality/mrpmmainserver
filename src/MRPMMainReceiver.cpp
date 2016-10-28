#include "MRPMMainReceiver.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

std::mutex mtx;

void MRPMMainReceiver::init() {
  receiver.setup(PORT);
  auto th = std::thread([this]{
    while (1) {
      if (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if (m.getAddress() == "/camera/position") {
          int id = m.getArgAsInt32(0);
          int time = m.getArgAsInt32(1);
          double x = m.getArgAsDouble(2);
          double y = m.getArgAsDouble(3);
          double theta = m.getArgAsDouble(4);
          double GAIN = 2;
          mtx.lock();
          data[id].time = time;
          data[id].pos.x = x + GAIN * (x - prev_data[id].pos.x);
          data[id].pos.y = y + GAIN * (y - prev_data[id].pos.y);
          data[id].pos.theta = theta + GAIN * (theta - prev_data[id].pos.theta);
          mtx.unlock();
          prev_data[id].time = time;
          prev_data[id].pos.x = x;
          prev_data[id].pos.y = y;
          prev_data[id].pos.theta = theta;
        } else if (m.getAddress() == "/robot/shot") {
          int id = m.getArgAsInt32(0);
          bool shot = m.getArgAsBool(1);
          mtx.lock();
          data[id].operation.shot = shot;
          mtx.unlock();
        }
      }
    }
  });
  th.detach();
}

void MRPMMainReceiver::update() {
}

RobotData MRPMMainReceiver::getData(int _id) {
  mtx.lock();
  RobotData tmp_data = data[_id];
  mtx.unlock();
  return tmp_data;
}
