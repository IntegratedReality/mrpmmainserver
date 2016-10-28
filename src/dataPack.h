//
//  dataPack.h
//  MRPMMainServer
//  OSC通信の関数に渡すためのデータ型構造体の宣言
//
//  Created by Naoya Sakabe on 2016/10/25.
//
//
#pragma once

#include "ofMain.h"
#include "Bullet.h"

struct MRPMPackMainToRobot {
  int time;
  double x;
  double y;
  double theta;
  std::array<bool,9> permissions; //EDirectionの数だけ用意した
};

struct MRPMPackMainToCtrlr{
  std::vector<Position> positionsVec;
  std::vector<ofVec2f> velocitiesVec;
};

struct MRPMPackMainToAI{
};
