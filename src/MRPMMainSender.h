#pragma once

#include "Const.h"
#include "ofxOsc.h"
#include "ETeam.h"
#include "EState.h"

#include "dataPack.h"
#include "MRPMHostsConfig.h"

class MRPMMainSender {
public:
    void init();
    
    void sendToRobots(MRPMPackMainToRobot _p);
    void sendToCtrlrs(MRPMPackMainToCtrlr _p);
    void sendToAIs(MRPMPackMainToAI _p);
    
    //deprecated
    void sendData
    (int _id,
     int _time,
     double _x,
     double _y,
     double _theta,
     double _HP,
     double _EN,
     EState _state);
    //_EN:弾発射に必要なエネルギー
    
    //deprecated
    void sendPOOwner(int _id, ETeam _team);
private:
    std::vector<ofxOscSender>
    sendersToRobots,
    sendersToCtrlrs,
    sendersToAIs;
};
