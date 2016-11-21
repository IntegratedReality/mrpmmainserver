#include "MRPMMainSender.h"

template <typename T>
void addArg(ofxOscMessage& _m, T _arg) {
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
void addArg<std::string&>(ofxOscMessage& _m, std::string& _arg) {
  _m.addStringArg(_arg);
}

template <typename T>
void addArg(ofxOscMessage& _m, std::string&& _key, T _arg) {
  addArg(_m, _key);
  addArg(_m, _arg);
}


void MRPMMainSender::init() {
  sendersToRobots.reserve(hostsConfig::NUM_OF_ROBOT);
  for (auto& t : hostsConfig::hostsList) {

    try
    {
      ofxOscSender sender;
      sender.setup(t.rpiHostName, PORT_ROBOT);
      sendersToRobots.push_back(sender);
    }
    catch (...) {
      std::cerr << "OscSender Setup Error!!" << std::endl;
    }
  }

  sendersToCtrlrs.reserve(hostsConfig::NUM_OF_HUMAN);
  for (auto& t : hostsConfig::hostsList) {
    if (t.robotType == RobotType::HUMAN) {

      try {
        ofxOscSender sender;
        sender.setup(t.operatorHostName, PORT_OPERATOR);
        sendersToCtrlrs.push_back(sender);
      }
      catch (...) {
        std::cerr << "OscSender Setup Error!!" << std::endl;
      }
    }
  }

  sendersToAIs.reserve(hostsConfig::NUM_OF_AI);
  for (auto& t : hostsConfig::hostsList) {
    if (t.robotType == RobotType::AI) {
      try {
        ofxOscSender sender;
        sender.setup(t.operatorHostName, PORT_OPERATOR);
        sendersToCtrlrs.push_back(sender);
      }
      catch (...) {
        std::cerr << "OscSender Setup Error!!" << std::endl;
      }
    }
  }
}

void MRPMMainSender::sendToOneRobot
(int _id,
  MRPMPackMainToRobot& _p) {

  //各ロボットそれぞれだけに、各動作
  //(前進・後退・信地回転)が可能か通達する

  ofxOscMessage m;
  m.setAddress("/main/toRobot");

  addArg(m, _p.time);
  addArg(m, _p.pos.x);
  addArg(m, _p.pos.y);
  addArg(m, _p.pos.theta);
  for (auto& p : _p.permissions) {
    addArg(m, p);
  }

  sendersToRobots[_id].sendMessage(m);
}

void MRPMMainSender::sendToCtrlrsStart() {
  ofxOscMessage m;
  m.setAddress("/main/toCtrlr/start");
  addArg(m, true);

  //全Ctrlrに送信
  for (auto& s : sendersToCtrlrs) {
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToCtrlrsEnd() {
  ofxOscMessage m;
  m.setAddress("/main/toCtrlr/end");
  addArg(m, true);

  //全Ctrlrに送信
  for (auto& s : sendersToCtrlrs) {
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToCtrlrsSync(MRPMPackMainToCtrlr& _p) {

  ofxOscMessage m;
  m.setAddress("/main/toCtrlr/sync");

  auto& p = _p.robsData;
  for (int i = 0; i < p.size(); ++i) {
    //key "00" for each robot
    addArg(m, ofToString(i) + "0");
    //value "(x)/(y)/..."
    addArg(m,
      ofToString(p[i].pos.x) + "/" +
      ofToString(p[i].pos.y) + "/" +
      ofToString(p[i].pos.theta) + "/" +
      ofToString(p[i].toRespawn) + "/" +
      ofToString(p[i].HP) + "/" +
      ofToString(p[i].EN)
    );
  }


  {
    auto& b = _p.bulletsPos;
    static std::vector<int> counts(hostsConfig::NUM_OF_ROBOT);
    for (auto& c : counts) { c = 0; }
    for (auto& e : b) {
      //key "01" for each bullet
      addArg(m, ofToString(e.second)
        + ofToString(++counts[e.second]));
      //value "(x)/(y)/(rot)"
      addArg(m,
        ofToString(e.first.x) + "/" +
        ofToString(e.first.y) + "/" +
        ofToString(e.first.theta)
      );
    }
  }

  //common data key"90"
  addArg(m, "90");
  //value "(time)/(score)"
  addArg(m,
    ofToString(_p.timeSec) + "/" +
    ofToString(_p.score)
  );

  //全Ctrlrに送信
  for (auto& s : sendersToCtrlrs) {
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToCtrlrsAssignSignal() {
  auto& list = hostsConfig::hostsList;
  for (int i = 0; i < hostsConfig::NUM_OF_HUMAN; ++i) {
    ofxOscMessage m;
    m.setAddress("/main/toCtrlr/assign");
    addArg(m, i);
    addArg(m, list[i].rpiHostName);

    sendersToCtrlrs[i].sendMessage(m);
  }
}

void MRPMMainSender::sendToOneAI(Position& _pos) {
  ofxOscMessage m;
  m.setAddress("/main/toAI/yourpos");
  addArg(m, _pos.x);
  addArg(m, _pos.y);
  addArg(m, _pos.theta);
  for (auto& s : sendersToAIs) {
    s.sendMessage(m);
  }
}

void MRPMMainSender::sendToAIsSparse(MRPMPackMainToAI& _p) {
  ofxOscMessage m1, m2, m3;

  m1.setAddress("/main/toAI/allpos");
  for (Position& e : _p.robsPos) {
    addArg(m1, e.x);
    addArg(m1, e.y);
    addArg(m1, e.theta);
  }

  m2.setAddress("/main/toAI/POowner");
  for (auto& e : _p.POowners) {
    addArg(m2, e);
  }

  m3.setAddress("/main/toAI/gameState");
  addArg(m3, static_cast<int>(_p.gameState));

  for (auto& s : sendersToAIs) {
    s.sendMessage(m1);
    s.sendMessage(m2);
    s.sendMessage(m3);
  }
}
