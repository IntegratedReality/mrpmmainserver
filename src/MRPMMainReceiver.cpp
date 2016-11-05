#include "MRPMMainReceiver.h"
#include <thread>
#include <mutex>
#include <iostream>
#include<algorithm>

using namespace std;

std::mutex mtx;

void MRPMMainReceiver::resetAckReceived(){
  std::fill(ackReceived.begin(), ackReceived.end(), false);
}

bool MRPMMainReceiver::haveAllCtrlrsEntried(){
  return std::all_of
  (ackReceived.begin(),
   ackReceived.end(),
   [](bool a){return a;});
}

void MRPMMainReceiver::init() {
  
  data.resize(hostsConfig::NUM_OF_ROBOT);
  prev_data.resize(hostsConfig::NUM_OF_ROBOT);
  ackReceived.resize(hostsConfig::NUM_OF_HUMAN);
  resetAckReceived();
  
  receiver.setup(PORT_MAINRCV);
  auto th = std::thread([this]{
    while (1) {
      if (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        auto addr = m.getAddress();
        if (addr == "/camera/position") {
          int id = m.getArgAsInt32(0);
          int time = m.getArgAsInt32(1);
          double x = m.getArgAsDouble(2);
          double y = m.getArgAsDouble(3);
          double theta = m.getArgAsDouble(4);
          double GAIN = 0;
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
        } else if (addr == "/operator/shot") {
          int id = m.getArgAsInt32(0);
          bool shot = m.getArgAsBool(1);
          mtx.lock();
          data[id].operation.shot = shot;
          mtx.unlock();
        } else if ( addr =="/operator/ack"){
          int id = m.getArgAsInt32(0);
          ackReceived[id] = true;
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
