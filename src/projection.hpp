//
//  projection.hpp
//  MRPM3dProjection
//
//  Created by 小林由弥 on 2016/03/11.
//
//

#ifndef projection_hpp
#define projection_hpp

#include "ofMain.h"
#include "RobotData.h"
#include "EState.h"
#include "ETeam.h"
#include "Const.h"
#include <stdio.h>
#include <array>

const double root3 = sqrt(3);
/* screen size (default : WVGA) */
//const int screen_width = 1024;  //pixel
//const int screen_height = 768;
const int field_width = WIDTH_OF_FIELD;   //field size [mm]
const int field_height = HEIGHT_OF_FIELD;
const int screen_width = SCREEN_WIDTH;   //screen size of the projector [px]
const int screen_height = SCREEN_HEIGHT;
const int screen_width_total = ceil(field_width*scale);
const int screen_height_total = ceil(field_height*scale);
//const double scale = screen_width/static_cast<double>(900);  //  moved to const.h

/* set team color */
const std::array<ofColor,3> teamColor = {
  ofColor(0,131,255,255),
  ofColor(255,163,0,255),
  ofColor(255,255,255,255)
};
const std::array<ofColor,3> enhancedTeamColor = {
  ofColor(40,220,255,255),
  ofColor(255,190,40,255),
  ofColor(255,255,255,255)
};
const std::array<ofColor,3> killedColor = {
  ofColor(0,80,150,180),
  ofColor(180,70,180),
  ofColor(255,255,255,180)
};
const ofColor recoveryColor = ofColor(255,255,0);

class bullets{
  /* images are drawn by these functions */
public:
  inline void draw(int x, int y,int theta, ofImage &image, int width, int height){
    ofPushMatrix();
    {
      //ofTranslate(y*scale,x*scale);
      ofTranslate(y,x,3);
      ofRotate(theta*360/(2*M_PI));
      image.getTexture().draw(0,0,width,height);
    }
    ofPopMatrix();
  }
  
  inline void draw(int x, int y, int theta, ofImage &image){
    ofPushMatrix();
    {
      //ofTranslate(y*scale,x*scale);
      ofTranslate(y,x,3);
      ofRotate(theta*360/(2*M_PI));
      image.draw(0,0);
    }
    ofPopMatrix();
  }
  /*
   inline void draw(ofVec2f point, int theta, ofImage &image){
   ofPushMatrix();
   {
   ofTranslate(point);
   ofRotate(theta*360/(2*M_PI));
   image.draw(0,0);
   }
   ofPopMatrix();
   }
   */
  inline void draw(int x, int y, int theta, ETeam team){
    ofPushMatrix();
    ofPushStyle();
    {
      ofTranslate(y, x);
      ofRotate(theta*360/(2*M_PI));
      bulletFbo[team].draw(0,0);
    }
    ofPopStyle();
    ofPopMatrix();
  }
  
  void initBullet(int _id);
  ofFbo bulletFbo[3];
  
  //        inline ofTexture getTexture(){
  //            return bulletFbo.getTexture();
  //        }
  
  bullets(){
    for (int i = 0; i < 3; i++){
      initBullet(i);
    }
  }
};

class virtualWall{
  
public:
  void draw();
  void init();
  
  virtualWall(){
    
  }
  
};

class robotModel{
  /* variables */
public:
  //const int diameter_bottom = 58.8,diameter_top = 35.3,height_bottom = 1,height_top = 58.8;   //size of the robot
  const int diameter_bottom = diameter_bottom_ro,diameter_top = diameter_top_ro,height_bottom = height_bottom_ro,height_top = height_top_ro;   //size of the robot
  ofVec2f centerPoint;
  ofMesh top_mesh,side_mesh;
  ofVbo top_vbo,side_vbo;
  ETeam team;
  EState currentState;
private:
  std::array<ofVec3f,6> vertices_bottom;
  std::array<ofVec3f,6> vertices_top;
  
  /* functions */
public:
  void draw(int x, int y, float theta, const RobotData *robdata);
  void draw(int x, int y, float theta, ofImage &texture, const RobotData *robdata);
  void init(const ETeam _team);
  
  robotModel(){
    /* set a 3D-model */
    vertices_bottom[0] = ofVec3f(0, -diameter_bottom, height_bottom);
    vertices_bottom[1] = ofVec3f(0.5*diameter_bottom*root3, -0.5*diameter_bottom, height_bottom);
    vertices_bottom[2] = ofVec3f(0.5*diameter_bottom*root3, 0.5*diameter_bottom, height_bottom);
    vertices_bottom[3] = ofVec3f(0, diameter_bottom, height_bottom);
    vertices_bottom[4] = ofVec3f(-0.5*diameter_bottom*root3, 0.5*diameter_bottom, height_bottom);
    vertices_bottom[5] = ofVec3f(-0.5*diameter_bottom*root3, -0.5*diameter_bottom, height_bottom);
    
    vertices_top[0] = ofVec3f(0, -diameter_top, height_top);
    vertices_top[1] = ofVec3f(0.5*diameter_top*root3, -0.5*diameter_top, height_top);
    vertices_top[2] = ofVec3f(0.5*diameter_top*root3, 0.5*diameter_top, height_top);
    vertices_top[3] = ofVec3f(0, diameter_top, height_top);
    vertices_top[4] = ofVec3f(-0.5*diameter_top*root3, 0.5*diameter_top, height_top);
    vertices_top[5] = ofVec3f(-0.5*diameter_top*root3, -0.5*diameter_top, height_top);
    
    top_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    side_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
  }
};

class pointObject{
  /* variables */
public:
  //const int diameter = 68.5,height_bottom = 1,height_top = 76.4;     //size of the point object
  const int diameter = diameter_po,height_bottom = height_bottom_po,height_top = height_top_po;
  
  ofVec2f centerPoint;
  float angle;
  ofMesh mesh;
  ofVbo vbo;
  int texture_scale = 0;
  
private:
  std::array<ofVec3f,7> vertices;    //オブジェクトの形状(固定)
  
  /* functions */
public:
  void init(int x, int y, float theta);
  void draw(int score);
  void draw(ofImage &texture, int score);
  void draw(ofShader &shader, int score);
  inline void setTextureScale(int scale){ //引数は％(デフォルト100) テクスチャの調整機能は必要に応じて実装
    texture_scale = (scale/100) - 1;
  }
  
  pointObject() {
    /* set a 3D-model */
    vertices[1] = ofVec3f(0, -diameter, height_bottom);
    vertices[2] = ofVec3f(0.5*diameter*root3, -0.5*diameter, height_bottom);
    vertices[3] = ofVec3f(0.5*diameter*root3, 0.5*diameter, height_bottom);
    vertices[4] = ofVec3f(0, diameter, height_bottom);
    vertices[5] = ofVec3f(-0.5*diameter*root3, 0.5*diameter, height_bottom);
    vertices[6] = ofVec3f(-0.5*diameter*root3, -0.5*diameter, height_bottom);
    
    mesh.addTexCoord(ofVec2f(0,0));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(0.5,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(0.5,1));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(0.5,1));
    mesh.addTexCoord(ofVec2f(1,1));
  }
};

class PMClass{
public:  
  /* texture, effects */
  ofImage textureImg;
  ofImage pointObjectTexture;
  ofImage backGroundImg;
  ofImage virtualWallTexture;
  ofFbo backGroundFbo;
  ofShader fieldShader;
  ofShader objectShader;
  ofShader alphaShader;
  ofShader robotShader;
  
  /* 3Dobjects */
  std::array<pointObject,3> p_object;
  std::array<robotModel,6> robot;
  
  /* effect, bullet */
  bullets bullet;
  ofImage bulletImg;  //ここに置く？
  
  /* text */
  std::array<ofTrueTypeFont,51> font;
  
  /* time control */
  float startTime;
  float currentTime;
  float time;
  
  /* cameras */
  std::array<ofCamera,4> cam;
  std::array<ofRectangle,4> viewPort;
  std::array<ofVec2f,4> viewPortPosition;
  std::array<bool,4> bConfPort;
  std::array<bool,4> bConfShade;
  
  bool bConfShade1 = false;
  bool bconfShade2 = false;
  bool bShowFieldFrame = false;
  double camAngle;
  int projectorHeight;
  int shadeWidth1 = 0;
  int shadeWidth2 = 0;
  
  void initializeProjection();
  
  PMClass(){
    //--
    // set up viewPorts
    // 0: left top screen, 1: right top, 2: left bottom, 3: right bottom
    viewPortPosition[0].x = 0;
    viewPortPosition[0].y = 0;
    viewPortPosition[1].x = screen_width;
    viewPortPosition[1].y = 0;
    viewPortPosition[2].x = 0;
    viewPortPosition[2].y = screen_height;
    viewPortPosition[3].x = screen_width;
    viewPortPosition[3].y = screen_height;
    
    // init view ports
    for(int i =0; i < 4; i++){
      viewPort[i].setSize(screen_width,screen_height);
      viewPort[i].setPosition(viewPortPosition[i].x, viewPortPosition[i].y);
    }
    
    //---
    /* set up projector position */
    projectorHeight = ceil(1000.0/scale);
    cam[0].roll(90);    //to rotate cam around z-axis
    cam[1].roll(90);
    cam[2].roll(90);
    cam[3].roll(90);
    cam[0].setPosition(ofVec3f(screen_height/2.0,screen_width/2.0,projectorHeight));    // coordinate is (y,x,z) (why?)
    cam[1].setPosition(ofVec3f(screen_height/2.0,screen_width_total - screen_width/2.0,projectorHeight));
    cam[2].setPosition(ofVec3f(screen_height_total - screen_height/2.0,screen_width/2.0,projectorHeight));
    cam[3].setPosition(ofVec3f(screen_height_total - screen_height/2.0,screen_width_total - screen_width/2.0,projectorHeight));
    
    /* カメラの視野の広さ(角度) */
    camAngle = 24;
    for(int i = 0; i < 4; i++){
      cam[i].setFov(camAngle);
    }
    cout << "cam0 : " << cam[0].getX() << ":" << cam[0].getY() << ":" << cam[0].getZ() << endl;
    cout << "cam1 : " << cam[1].getX() << ":" << cam[1].getY() << ":" << cam[1].getZ() << endl;
    cout << "cam2 : " << cam[2].getX() << ":" << cam[2].getY() << ":" << cam[2].getZ() << endl;
    cout << "cam3 : " << cam[3].getX() << ":" << cam[3].getY() << ":" << cam[3].getZ() << endl;
    cout << "port1 width : " << viewPort[0].getWidth() << endl;
    cout << "port2 width : " << viewPort[1].getWidth() << endl;
    cout << "port3 width : " << viewPort[2].getWidth() << endl;
    cout << "port4 width : " << viewPort[3].getWidth() << endl;
    cout << "port1 height : " << viewPort[0].getHeight() << endl;
    cout << "port2 height : " << viewPort[1].getHeight() << endl;
    cout << "port3 height : " << viewPort[2].getHeight() << endl;
    cout << "port4 height : " << viewPort[3].getHeight() << endl;
    cout << "position : " << cam[0].getZAxis() << ", " << cam[1].getZAxis() << ", " << cam[2].getZAxis() << ", " << cam[3].getZAxis() << endl;
    //---
    
    /* set point objects(x,y,theta) */
//    p_object[1].init(screen_height_total/4,screen_width_total/4, 2); //(x,y,theta)
//    p_object[0].init(screen_height_total/2,screen_width_total/2, 1);
//    p_object[2].init(screen_height_total*0.75,screen_width_total*0.75, 0.5);
    p_object[1].init(POINT_OBJ_1_Y*scale,POINT_OBJ_1_X*scale, 0); //(x,y,theta)   values are defined in const.h
    p_object[0].init(POINT_OBJ_0_Y*scale,POINT_OBJ_0_X*scale, 0);
    p_object[2].init(POINT_OBJ_2_Y*scale,POINT_OBJ_2_X*scale, 0);

    
    bulletImg.setAnchorPercent(0.5, 0.5);   //中心で指定できるように
  }
};

#endif /* projection_hpp */
