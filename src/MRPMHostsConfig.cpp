//
//  MRPMHostsConfig.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/28.
//
//

#include "MRPMHostsConfig.h"

const std::vector<robotHostConfig>
hostsConfig::hostsList{
  //rpiHostName, isAI, operator HostName
  //若い番号から人間,AIの順番を要請
  {"raspberrypi.local", RobotType::HUMAN, "PE25.local"},
  {"mrpmpi1.local", RobotType::HUMAN, "PE26.local"},
  {"mrpmpi2.local", RobotType::HUMAN, "PE27.local"},
  {"mrpmpi3.local", RobotType::AI, "mrpmpi3.local"},
  {"mrpmpi4.local", RobotType::AI, "mrpmpi4.local"},
  {"mrpmpi5.local", RobotType::AI, "mrpmpi5.local"}
};


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

