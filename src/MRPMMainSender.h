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
    
    void sendToOneRobot
    (int _id,
     MRPMPackMainToRobot& _p);
    void sendToCtrlrsStart();
    void sendToCtrlrsEnd();
    void sendToCtrlrsSync(MRPMPackMainToCtrlr& _p);
    void sendToCtrlrsAssignSignal();
    void sendToOneAI(Position& _pos);
    void sendToAIsSparse(MRPMPackMainToAI& _p);
    
private:
    std::vector<ofxOscSender>
    sendersToRobots,
    sendersToCtrlrs,
    sendersToAIs;
};
