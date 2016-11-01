#pragma once

#include "RobotData.h"
#include "ETeam.h"
#include "projection.hpp"
#include "pjCalib.h"

class PMx {
public:
    static PMx* getInstance() {
        static PMx instance;
        return &instance;
    }
    
    void setup();
    void keyPressed(int key);
    void drawField();
    void drawTextureField();
    void drawShaderField();
    void drawPO(int _id, int state);
    void initRobot(int _id, ETeam team);
    void drawRobot(double _x, double _y, double _theta, const RobotData *_data);
    void drawImg(double _x, double _y, double _theta, ofImage &_img, float duration = 0.0, float time = 0.0);   //unit of duration is [ms]
    void drawImg(double _x, double _y, double _theta, ofImage &_img, int width, int height,  float duration = 0, float time = 0.0);
    void drawBullet(double _x, double _y, double _theta, ETeam team, float duration = 0, float time = 0.0);
    void drawBullet(double _x, double _y, double _theta, int width, int height,  float duration = 0, float time = 0.0);
    void drawText(string content,int x,int y,int size = 24, ofColor textColor=ofColor(255,255,255));
    void drawTextField(ofColor bgColor=ofColor(0,0,0,200));
    void drawVWall(int x1,int y1, int w, int h);
    
    inline void drawLatticeIfNeeded(){
        pjlattice.draw();
    }
private:
    PMx() {};
    PMClass PM;
    PJLattice pjlattice;    //歪み観察用格子
    
    // for one camera
    void _drawField();
    void _drawTextureField();
    void _drawShaderField();
    void _drawPO(int _id, int state);
    void _drawRobot(double _x, double _y, double _theta, const RobotData *_data);
    void _drawImg(double _x, double _y, double _theta, ofImage &_img, float duration, float time);
    void _drawBulletTexture(double _x, double _y, double _theta, ETeam team, float duration=0, float time=0.0);
    void _drawImg(double _x, double _y, double _theta, ofImage &_img, int width, int height, float duration, float time);
    void _drawText(string content,int x,int y,int size, ofColor textColor);
    void _drawTextField(ofColor bgColor);
};
