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
#include "Operation.h"
#include "Const.h"
#include "EMode.h"

struct MRPMPackMainToRobot {
  int time;
  Position pos;
  permsAry permissions; //EDirectionの数だけ用意した
};

struct MRPMPackMainToCtrlr{
  std::vector<RobotData> robsData;
  std::vector<std::pair<Position, int>> bulletsPos;
  int timeSec;
  int score;
};

struct MRPMPackMainToAI{
  std::vector<Position> robsPos;
  std::array<int, NUM_OF_POINT_OBJ> POowners;
  EMode gameState;
};
