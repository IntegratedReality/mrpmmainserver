#pragma once

#include "Const.h"
#include "RobotData.h"
#include "ofxOscReceiver.h"
#include "MRPMHostsConfig.h"

class MRPMMainReceiver {
public:
    void init();
    void update();
    RobotData getData(int _id);
    
    void resetAckReceived();
    bool haveAllCtrlrsEntried();
private:
    ofxOscReceiver receiver;
    std::vector<RobotData> data;
    std::vector<RobotData> prev_data;
    
    std::vector<bool> ackReceived;
};
