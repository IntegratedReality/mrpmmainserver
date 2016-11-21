//
//  pjCalib.cpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/21.
//
//

#include "pjCalib.h"
#include "Const.h"

PJLattice::PJLattice()
{
  latticeLineColor = ofColor::orange;
  centerLineColor = ofColor::pink;
  wndWidth = ofGetWidth();
  wndHeight = ofGetHeight();
}

void PJLattice::drawVerticalLine(int x) {
  ofDrawLine(x, 0.f, x, wndHeight);
}

void PJLattice::drawHorizontalLine(int y) {
  ofDrawLine(0.f, y, wndWidth, y);
}

void PJLattice::draw() {
  static const int halfW = SCREEN_WIDTH / 2,
    halfH = SCREEN_HEIGHT / 2;
  if (isOn) {
    ofPushStyle();
    ofSetLineWidth(lineWidth);
    {
      int i{ 0 };
      while (i*unit < wndWidth) {
        if (i*unit == halfW || i*unit == halfW+SCREEN_WIDTH) {
          ofSetColor(centerLineColor);
        } else {
          ofSetColor(latticeLineColor);
        }
        drawVerticalLine(i*unit);
        ++i;
      }
    }
    {
      int i{ 0 };
      while (i*unit < wndHeight) {
        if (i*unit == halfH || i*unit == halfH+SCREEN_HEIGHT) {
          ofSetColor(centerLineColor);
        } else {
          ofSetColor(latticeLineColor);
        }
        drawHorizontalLine(i*unit);
        ++i;
      }
    }


    ofPopStyle();
  }
}

bool PJLattice::toggle() {
  isOn = !isOn;
  return isOn;
}
