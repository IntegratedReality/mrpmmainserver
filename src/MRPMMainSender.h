#pragma once

#include "Const.h"
#include "ofxOsc.h"
#include "ETeam.h"
#include "EState.h"

#include "dataPack.h"

class MRPMMainSender {
public:
    void init();
    
    void sendToRobots(PackMainToRobot _p);
    void sendToCtrlrs(PackMainToCtrlr _p);
    
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
    sendersToCtrlrs;
};
