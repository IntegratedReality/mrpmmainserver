//
//  Operation.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/28.
//
//
#include "Operation.h"

void disableForward(permsAry& ary){
  for(int i:{1,2,8}){
    //TOP, TOP_RIGHT, TOP_LEFT
    ary[i] = false;
  }
}

void disableBackward(permsAry& ary){
  for(int i:{4,5,6}){
    //BOTTOM_RIGHT,BOTTOM,BOTTOM_LEFT
    ary[i] = false;
  }
}

void disablePivotTurn(permsAry& ary){
  for(int i:{3,7}){
    //RIGHT,LEFT
    ary[i] = false;
  }
}

void disableAll(permsAry& ary){
  for(auto& e:ary){
    e = false;
  }
}
void enableAll(permsAry& ary){
  for(auto& e:ary){
    e = true;
  }
}
