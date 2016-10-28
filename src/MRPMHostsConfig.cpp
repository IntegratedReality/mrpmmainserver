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
  {"mrpmpi0.local", false, "PE25.local"},
  {"mrpmpi1.local", false, "PE26.local"},
  {"mrpmpi2.local", false, "PE27.local"},
  {"mrpmpi3.local", true, "mrpmpi3.local"},
  {"mrpmpi4.local", true, "mrpmpi4.local"},
  {"mrpmpi5.local", true, "mrpmpi5.local"}
};


const int hostsConfig::NUM_OF_ROBOT
= static_cast<int>(hostsConfig::hostsList.size());

const int hostsConfig::NUM_OF_HUMAN
= static_cast<int>
(std::count_if(hostsConfig::hostsList.begin(),
               hostsConfig::hostsList.end(),
               [](robotHostConfig c){
                 return !c.isAI;
               })
 );

const int hostsConfig::NUM_OF_AI
= static_cast<int>
(std::count_if(hostsConfig::hostsList.begin(),
               hostsConfig::hostsList.end(),
               [](robotHostConfig c){
                 return c.isAI;
               })
 );

