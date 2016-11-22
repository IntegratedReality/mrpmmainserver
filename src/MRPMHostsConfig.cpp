//
//  MRPMHostsConfig.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/28.
//
//

#include "MRPMHostsConfig.h"

#define WITH_NO_ROBOTS

#ifndef WITH_NO_ROBOTS
const std::vector<robotHostConfig>
hostsConfig::hostsList{
  //rpiHostName, isAI, operator HostName
  //若い番号から人間,AIの順番を要請
  {"mrpmpi1.local", RobotType::HUMAN, "127.0.0.1"}, 
  {"mrpmpi2.local", RobotType::HUMAN, "127.0.0.1"},
  {"mrpmpi3.local", RobotType::AI, "127.0.0.1"}, //Main PC
  {"mrpmpi4.local", RobotType::AI, "127.0.0.1"}
};
#else
const std::vector<robotHostConfig>
hostsConfig::hostsList{
  {"192.168.10.11", RobotType::HUMAN, "192.168.10.4"},
  {"192.168.10.9", RobotType::HUMAN, "192.168.10.7"},
  {"127.0.0.1", RobotType::AI, "127.0.0.1"},
  {"127.0.0.1", RobotType::AI, "127.0.0.1"}
};
#endif //WITH_NO_ROBOTS



const int hostsConfig::NUM_OF_ROBOT
= static_cast<int>(hostsConfig::hostsList.size());

const int hostsConfig::NUM_OF_HUMAN
= static_cast<int>
(std::count_if(hostsConfig::hostsList.begin(),
               hostsConfig::hostsList.end(),
               [](robotHostConfig c){
                 return c.robotType == RobotType::HUMAN;
               })
 );

const int hostsConfig::NUM_OF_AI
= static_cast<int>
(std::count_if(hostsConfig::hostsList.begin(),
               hostsConfig::hostsList.end(),
               [](robotHostConfig c){
                 return c.robotType == RobotType::AI;
               })
 );

