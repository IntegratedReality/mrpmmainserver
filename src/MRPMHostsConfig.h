//
//  MRPMHostsConfig.h
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/28.
//

#pragma once
#include "ofMain.h"

enum class RobotType: uint8_t{
    HUMAN,
    AI
};

struct robotHostConfig{
    std::string rpiHostName;
    RobotType robotType;
    std::string operatorHostName;
};


struct hostsConfig{
    static const std::vector<robotHostConfig> hostsList;
    
    
    static const int NUM_OF_ROBOT;
    static const int NUM_OF_HUMAN;
    static const int NUM_OF_AI;
};



