//
//  pjCalib.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/21.
//
//

#include "pjCalib.h"

PJLattice::PJLattice()
{
  lineColor=ofColor::orange;
  wndWidth=ofGetWidth();
  wndHeight=ofGetHeight();
}

void PJLattice::drawVerticalLine(int x){
  ofDrawLine(x, 0.f, x, wndHeight);
}

void PJLattice::drawHorizontalLine(int y){
  ofDrawLine(0.f, y, wndWidth, y);
}

void PJLattice::draw(){
  if(isOn){
    ofSetColor(lineColor);
    {
      int i{0};
      while(i*unit<wndWidth){
        drawVerticalLine(i*unit);
        ++i;
      }
    }
    {
      int i{0};
      while(i*unit<wndHeight){
        drawHorizontalLine(i*unit);
        ++i;
      }
    }
  }
}

bool PJLattice::toggle(){
  isOn = !isOn;
  return isOn;
}
