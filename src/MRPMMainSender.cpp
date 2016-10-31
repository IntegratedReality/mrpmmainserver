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
template <>
void addArg<bool>(ofxOscMessage& _m, bool _arg) {
  _m.addBoolArg(_arg);
}
template <>
void addArg<std::string&>(ofxOscMessage& _m, std::string& _arg){
  _m.addStringArg(_arg);
}


void MRPMMainSender::init() {
  sendersToRobots.reserve(hostsConfig::NUM_OF_ROBOT);
  for(auto& t:hostsConfig::hostsList){
    ofxOscSender sender;
    sender.setup(t.rpiHostName, PORT_ROBOT);
    sendersToRobots.push_back(sender);
  }
  
  sendersToCtrlrs.reserve(hostsConfig::NUM_OF_HUMAN);
  for(auto& t:hostsConfig::hostsList){
    if(t.robotType == RobotType::HUMAN){
      ofxOscSender sender;
      sender.setup(t.operatorHostName, PORT_OPERATOR);
      sendersToCtrlrs.push_back(sender);
    }
  }
  
  sendersToAIs.reserve(hostsConfig::NUM_OF_AI);
  for(auto& t:hostsConfig::hostsList){
    if(t.robotType == RobotType::AI){
      ofxOscSender sender;
      sender.setup(t.operatorHostName, PORT_OPERATOR);
      sendersToCtrlrs.push_back(sender);
    }
  }
}

void MRPMMainSender::sendToOneRobot
(int _id,
 MRPMPackMainToRobot& _p){
  
  //各ロボットそれぞれだけに、各動作
  //(前進・後退・信地回転)が可能か通達する
  
  ofxOscMessage m;
  m.setAddress("/main/toRobot");
  
  addArg(m,_p.time);
  addArg(m,_p.pos.x);
  addArg(m,_p.pos.y);
  addArg(m,_p.pos.theta);
  for(auto& p: _p.permissions){
    addArg(m, p);
  }

  sendersToRobots[_id].sendMessage(m);
}

void MRPMMainSender::sendToCtrlrs(MRPMPackMainToCtrlr& _p){
  
  ofxOscMessage m;
  m.setAddress("/main/toCtrlr/bullets");
  size_t bulletsNum = _p.positionsVec.size();
  
  //int 弾のカウント,
  //double 位置x, 位置y, 速度x, 速度y, ....
  addArg(m, static_cast<int>(bulletsNum));
  for(size_t i = 0; i<bulletsNum; ++i){
    addArg(m, _p.positionsVec[i].x);
    addArg(m, _p.positionsVec[i].y);
    addArg(m, _p.velocitiesVec[i].x);
    addArg(m, _p.velocitiesVec[i].y);
  }
  
  //全Ctrlrに送信
  for(auto& s: sendersToCtrlrs){
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToCtrlrsAssignSignal(){
  auto& list=hostsConfig::hostsList;
  for(int i=0; i<hostsConfig::NUM_OF_HUMAN; ++i){
    ofxOscMessage m;
    m.setAddress("/main/toCtrlr/assign");
    addArg(m, i);
    addArg(m, list[i].rpiHostName);
    
    sendersToCtrlrs[i].sendMessage(m);
  }
}

void MRPMMainSender::sendToOneAI(Position& _pos){
  ofxOscMessage m;
  m.setAddress("/main/toAI/yourpos");
  addArg(m, _pos.x);
  addArg(m, _pos.y);
  addArg(m, _pos.theta);
  for(auto& s: sendersToAIs){
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToAIsSparse(MRPMPackMainToAI& _p){
  ofxOscMessage m1, m2;
  
  m1.setAddress("/main/toAI/allpos");
  for(Position& e:_p.robsPos){
    addArg(m1, e.x);
    addArg(m1, e.y);
    addArg(m1, e.theta);
  }
  
  m2.setAddress("/main/toAI/POowner");
  for(auto& e:_p.POowners){
    addArg(m2, e);
  }
  
  for(auto& s: sendersToAIs){
    s.sendMessage(m1);
    s.sendMessage(m2);
  }
}
