//
//  MRPMHostsConfig.h
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/28.
//

#pragma once
#include "ofMain.h"

//hostname, isAI
struct robotHostConfig{
    std::string rpiHostName;
    bool isAI;
    std::string operatorHostName;
};


struct hostsConfig{
    static const std::vector<robotHostConfig> hostsList;
    
    
    static const int NUM_OF_ROBOT;
    static const int NUM_OF_HUMAN;
    static const int NUM_OF_AI;
};



