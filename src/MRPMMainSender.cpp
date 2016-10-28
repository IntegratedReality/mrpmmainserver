#include "MRPMMainSender.h"

template <typename T>
void addArg(ofxOscMessage& _m, T _arg){
  _m.addStringArg(ofToString(_arg));
};
template <>
void addArg<int>(ofxOscMessage& _m, int _arg) {
  _m.addInt32Arg(_arg);
}
template <>
void addArg<double>(ofxOscMessage& _m, double _arg) {
  _m.addDoubleArg(_arg);
}


const std::initializer_list<std::string> robotList{
  "mrpmpi0.local",
  "mrpmpi1.local",
  "mrpmpi2.local",
  "mrpmpi3.local",
  "mrpmpi4.local",
  "mrpmpi5.local"};
  
const std::initializer_list<std::string> ctrlrList{
  "PE25.local",
  "PE26.local",
  "PE27.local",
};


void MRPMMainSender::init() {
  for(auto& t:robotList){
    ofxOscSender sender;
    sender.setup(t, PORT);
    sendersToRobots.push_back(sender);
  }
  for(auto& t:ctrlrList){
    ofxOscSender sender;
    sender.setup(t, PORT);
    sendersToCtrlrs.push_back(sender);
  }
}

void MRPMMainSender::sendToRobots(PackMainToRobot _p){
  ofxOscMessage m;
  m.setAddress("/main/foobar");
  
  
  for(auto& s: sendersToRobots){  //全台に同じ情報が必要か?
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToCtrlrs(PackMainToCtrlr _p){
  ofxOscMessage m;
  m.setAddress("/main/bazbaz");
  for(auto& s: sendersToCtrlrs){  //全台に同じ情報が必要か?
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendData
(int _id,
 int _time,
 double _x,
 double _y,
 double _theta,
 double _HP,
 double _EN,
 EState _state) {
  std::cerr << "sendData() is deprecated" << std::endl;
  ofxOscMessage m;
  m.setAddress("/main/position");
  m.addInt32Arg(_id);
  m.addInt32Arg(_time);
  m.addDoubleArg(_x);
  m.addDoubleArg(_y);
  m.addDoubleArg(_theta);
  m.addDoubleArg(_HP);
  m.addDoubleArg(_EN);
  m.addInt32Arg((int)_state);
//  
//  for(auto& s: senders){
//    s.sendMessage(m);
//  }
}

void MRPMMainSender::sendPOOwner(int _id, ETeam _team) {
  std::cerr<<"sendPOOwner() is deprecated" << std::endl;
  ofxOscMessage m;
  m.setAddress("/main/poowner");
  m.addInt32Arg(_id);
  m.addInt32Arg((int)_team);
//  
//  for(auto& s: senders){
//    s.sendMessage(m);
//  }
}
