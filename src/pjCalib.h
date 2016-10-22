//
//  pjCalib.h
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/21.
//
//

#pragma once
#include "ofMain.h"

class PJLattice{
    const double unit=60.0;
    //unit:格子間隔
    
    const int lineWidth=3;
    ofColor lineColor;
    int wndWidth,wndHeight;
    
    void drawVerticalLine(int x);
    void drawHorizontalLine(int y);
    bool isOn{false};
public:
    PJLattice();
    void draw();
    bool toggle();
};
