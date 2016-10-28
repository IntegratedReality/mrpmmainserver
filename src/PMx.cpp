#include "PMx.h"

void PMx::setup() {
  /* initialize oF */
  ofBackground(0);
  PM.initializeProjection();  //this function includes configurations of oF
  
  //    /* set point objects(x,y,theta) */
  //    PM.p_object[0].init(screen_height/2,screen_width/4, 2); //(x,y,theta)
  //    PM.p_object[1].init(screen_height,screen_width/2, 1);
  //    PM.p_object[2].init(screen_height*1.5,screen_width*0.75, 0.5);
  
  /* load images if needed */
  //	PM.textureImg.load("281.gif");
  PM.textureImg.load("pattern.png");
  PM.pointObjectTexture.load("texture.jpg");  //example texture
  PM.bulletImg.load("blue.png");  //image for bullet
  PM.backGroundImg.load("bg.jpg");
  PM.virtualWallTexture.load("mesh.jpg");
  //PM.createFieldBgFbo();
  
  PM.fieldShader.load("test.vert", "water.frag");
  PM.objectShader.load("test.vert", "cloud.frag");
  PM.alphaShader.load("texture.vert","alpha.frag");
  PM.robotShader.load("test.vert","robot.frag");
  
  /* load font */
  for (int i = 1; i < 50; i++){
    PM.font[i].load("Arial.ttf",i);
  }
  
  PM.startTime = ofGetElapsedTimef();
}

void PMx::keyPressed(int key) {
  //pjlattice toggle by 'L' key
  //added by sakabe
  if (key=='l'){
    pjlattice.toggle();
  }
  
  /* simple calibration utils */
  
  //position of the view port
  if (key == 49){ //'1'
    for (int i = 1; i < 4; i++){
      PM.bConfPort[i] = false;
    }
    PM.bConfPort[0] = !PM.bConfPort[0];
    cout << "bConfPort1 : " << PM.bConfPort[0] << endl;
  }
  if (key == 50){ //'2'
    PM.bConfPort[0] = false;
    PM.bConfPort[2] = false;
    PM.bConfPort[3] = false;
    PM.bConfPort[1] = !PM.bConfPort[1];
    cout << "bConfPort2 : " << PM.bConfPort[1] << endl;
  }
  if (key == 51){ //'3'
    PM.bConfPort[0] = false;
    PM.bConfPort[1] = false;
    PM.bConfPort[3] = false;
    PM.bConfPort[2] = !PM.bConfPort[2];
    cout << "bConfPort3 : " << PM.bConfPort[2] << endl;
  }
  if (key == 52){ //'4'
    for (int i = 0; i < 3; i++){
      PM.bConfPort[i] = false;
    }
    PM.bConfPort[3] = !PM.bConfPort[3];
    cout << "bConfPort4 : " << PM.bConfPort[3] << endl;
  }
  
  //adjust the shade of overlaps
  if (key == 53){ //'5'
    PM.bConfShade1 = !PM.bConfShade1;
    PM.bConfPort[0] = false;
    PM.bConfPort[1] = false;
    PM.bconfShade2 = false;
    cout << "bConfShade1 : " << PM.bConfShade1 << endl;
  }
  if (key == 54){ //'6'
    PM.bconfShade2 = !PM.bconfShade2;
    PM.bConfPort[0] = false;
    PM.bConfPort[1] = false;
    PM.bConfShade1 = false;
    cout << "bConfShade2 : " << PM.bconfShade2 << endl;
  }
  
  if (key == 'f'){
    PM.bShowFieldFrame = !PM.bShowFieldFrame;
  }
  
  if (PM.bConfPort[0]){
    if (key == OF_KEY_RIGHT){
      PM.viewPortPosition[0].x += 1;
      PM.viewPort[0].setPosition(PM.viewPortPosition[0].x, PM.viewPortPosition[0].y);
      cout << "position1(x) : " << PM.viewPortPosition[0].x << endl;
    }
    if (key == OF_KEY_LEFT){
      PM.viewPortPosition[0].x -= 1;
      PM.viewPort[0].setPosition(PM.viewPortPosition[0].x, PM.viewPortPosition[0].y);
      cout << "position1(x) : " << PM.viewPortPosition[0].x << endl;
    }
    if (key == OF_KEY_UP){
      PM.viewPortPosition[0].y -= 1;
      PM.viewPort[0].setPosition(PM.viewPortPosition[0].x, PM.viewPortPosition[0].y);
      cout << "position1(x) : " << PM.viewPortPosition[0].y << endl;
    }
    if (key == OF_KEY_DOWN){
      PM.viewPortPosition[0].y += 1;
      PM.viewPort[0].setPosition(PM.viewPortPosition[0].x, PM.viewPortPosition[0].y);
      cout << "position1(x) : " << PM.viewPortPosition[0].y << endl;
    }
  }
  else if (PM.bConfPort[1]){
    if (key == OF_KEY_RIGHT){
      PM.viewPortPosition[1].x += 1;
      PM.viewPort[1].setPosition(PM.viewPortPosition[1].x, PM.viewPortPosition[1].y);
      cout << "position2(x) : " << PM.viewPortPosition[1].x << endl;
    }
    if (key == OF_KEY_LEFT){
      PM.viewPortPosition[1].x -= 1;
      PM.viewPort[1].setPosition(PM.viewPortPosition[1].x, PM.viewPortPosition[1].y);
      cout << "position2(x) : " << PM.viewPortPosition[1].x << endl;
    }
    if (key == OF_KEY_UP){
      PM.viewPortPosition[1].y -= 1;
      PM.viewPort[1].setPosition(PM.viewPortPosition[1].x, PM.viewPortPosition[1].y);
      cout << "position2(y) : " << PM.viewPortPosition[1].y << endl;
    }
    if (key == OF_KEY_DOWN){
      PM.viewPortPosition[1].y += 1;
      PM.viewPort[1].setPosition(PM.viewPortPosition[1].x, PM.viewPortPosition[1].y);
      cout << "position2(y) : " << PM.viewPortPosition[1].y << endl;
    }
  }
  else if (PM.bConfPort[2]){
    if (key == OF_KEY_RIGHT){
      PM.viewPortPosition[2].x += 1;
      PM.viewPort[2].setPosition(PM.viewPortPosition[2].x, PM.viewPortPosition[2].y);
      cout << "position3(x) : " << PM.viewPortPosition[2].x << endl;
    }
    if (key == OF_KEY_LEFT){
      PM.viewPortPosition[2].x -= 1;
      PM.viewPort[2].setPosition(PM.viewPortPosition[2].x, PM.viewPortPosition[2].y);
      cout << "position3(x) : " << PM.viewPortPosition[2].x << endl;
    }
    if (key == OF_KEY_UP){
      PM.viewPortPosition[2].y -= 1;
      PM.viewPort[2].setPosition(PM.viewPortPosition[2].x, PM.viewPortPosition[2].y);
      cout << "position3(y) : " << PM.viewPortPosition[2].y << endl;
    }
    if (key == OF_KEY_DOWN){
      PM.viewPortPosition[2].y += 1;
      PM.viewPort[2].setPosition(PM.viewPortPosition[2].x, PM.viewPortPosition[2].y);
      cout << "position3(y) : " << PM.viewPortPosition[2].y << endl;
    }
  }
  else if (PM.bConfPort[3]){
    if (key == OF_KEY_RIGHT){
      PM.viewPortPosition[3].x += 1;
      PM.viewPort[3].setPosition(PM.viewPortPosition[3].x, PM.viewPortPosition[3].y);
      cout << "position4(x) : " << PM.viewPortPosition[3].x << endl;
    }
    if (key == OF_KEY_LEFT){
      PM.viewPortPosition[3].x -= 1;
      PM.viewPort[3].setPosition(PM.viewPortPosition[3].x, PM.viewPortPosition[3].y);
      cout << "position4(x) : " << PM.viewPortPosition[3].x << endl;
    }
    if (key == OF_KEY_UP){
      PM.viewPortPosition[3].y -= 1;
      PM.viewPort[3].setPosition(PM.viewPortPosition[3].x, PM.viewPortPosition[3].y);
      cout << "position4(y) : " << PM.viewPortPosition[3].y << endl;
    }
    if (key == OF_KEY_DOWN){
      PM.viewPortPosition[3].y += 1;
      PM.viewPort[3].setPosition(PM.viewPortPosition[3].x, PM.viewPortPosition[3].y);
      cout << "position4(y) : " << PM.viewPortPosition[3].y << endl;
    }
  }
  else if (PM.bConfShade1){
    switch (key) {
      case OF_KEY_UP:
        PM.shadeWidth1 += 1;
        cout << "shade1 : " << PM.shadeWidth1 << endl;
        break;
      case OF_KEY_DOWN:
        PM.shadeWidth1 -= 1;
        cout << "shade1 : " << PM.shadeWidth1 << endl;
      default:
        break;
    }
  }
  else if (PM.bconfShade2){
    switch (key) {
      case OF_KEY_UP:
        PM.shadeWidth2 += 1;
        cout << "shade2 : " << PM.shadeWidth2 << endl;
        break;
      case OF_KEY_DOWN:
        PM.shadeWidth2 -= 1;
        cout << "shade2 : " << PM.shadeWidth2 << endl;
        
      default:
        break;
    }
  }
  else {
    if (key == OF_KEY_RIGHT){
      PM.camAngle += 0.5;
      for (int i = 0; i < 4; i++){
        PM.cam[i].setFov(PM.camAngle);
      }
      cout << "camAngle : " << PM.camAngle << endl;
    }
    if (key == OF_KEY_LEFT){
      PM.camAngle -= 0.5;
      for (int i = 0; i < 4; i++){
        PM.cam[i].setFov(PM.camAngle);
      }
      cout << "camAngle : " << PM.camAngle << endl;
    }
  }
}

void PMx::drawField() {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawField();
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawField();
  PM.cam[1].end();
}

void PMx::drawFieldTexture() {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawFieldTexture();
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawFieldTexture();
  PM.cam[1].end();
}

void PMx::drawShaderField(){
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawShaderField();
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawShaderField();
  PM.cam[1].end();
    
  // screen 3
  PM.cam[2].begin(PM.viewPort[2]);
  _drawShaderField();
  PM.cam[2].end();

  // screen 4
  PM.cam[3].begin(PM.viewPort[3]);
  _drawShaderField();
  PM.cam[3].end();
  
}

void PMx::drawPO(int _id, int state) {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawPO(_id, state);
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawPO(_id, state);
  PM.cam[1].end();
  
  // screen 3
  PM.cam[2].begin(PM.viewPort[2]);
  _drawPO(_id, state);
  PM.cam[2].end();
  
  // screen 4
  PM.cam[3].begin(PM.viewPort[3]);
  _drawPO(_id, state);
  PM.cam[3].end();
}

void PMx::drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawRobot(_x, _y, _theta, _data);
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawRobot(_x, _y, _theta, _data);
  PM.cam[1].end();
  
  // screen 3
  PM.cam[2].begin(PM.viewPort[2]);
  _drawRobot(_x, _y, _theta, _data);
  PM.cam[2].end();
  
  // screen 4
  PM.cam[3].begin(PM.viewPort[3]);
  _drawRobot(_x, _y, _theta, _data);
  PM.cam[3].end();
}

void PMx::drawImg(double _x, double _y, double _theta, ofImage &_img, float _duration, float _time) {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawImg(_x, _y, _theta, _img, _duration, _time);
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawImg(_x, _y, _theta, _img, _duration, _time);
  PM.cam[1].end();
}

/* when changes the texture size */
void PMx::drawImg(double _x, double _y, double _theta, ofImage &_img, int _width, int _height, float _duration, float _time) {
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  _drawImg(_x, _y, _theta, _img, _width, _height, _duration, _time);
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawImg(_x, _y, _theta, _img, _width, _height, _duration, _time);
  PM.cam[1].end();
}

void PMx::drawBullet(double _x, double _y, double _theta,ETeam team, float _duration, float _time){
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  ofPushMatrix();
  ofTranslate(0, 0,5);
  _drawBulletTexture(_y*scale, _x*scale, _theta, team);
  ofPopMatrix();
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  ofPushMatrix();
  ofTranslate(0, 0,5);
  _drawBulletTexture(_y*scale, _x*scale, _theta, team);
  ofPopMatrix();
  PM.cam[1].end();
  
  // screen 3
  PM.cam[2].begin(PM.viewPort[2]);
  ofPushMatrix();
  ofTranslate(0, 0,5);
  _drawBulletTexture(_y*scale, _x*scale, _theta, team);
  ofPopMatrix();
  PM.cam[2].end();
  
  // screen 4
  PM.cam[3].begin(PM.viewPort[3]);
  ofPushMatrix();
  ofTranslate(0, 0,5);
  _drawBulletTexture(_y*scale, _x*scale, _theta, team);
  ofPopMatrix();
  PM.cam[3].end();
}

void PMx::drawBullet(double _x, double _y, double _theta ,int _width, int _height, float _duration, float _time){
  // screen 1
  PM.cam[0].begin(PM.viewPort[0]);
  ofTranslate(0, 0,10);
  ofDrawCircle(500, 300, 30);
  _drawImg(_x, _y, _theta, PM.bulletImg, _width, _height, _duration, _time);
  ofTranslate(0, 0,-10);
  PM.cam[0].end();
  
  // screen 2
  PM.cam[1].begin(PM.viewPort[1]);
  _drawImg(_x, _y, _theta, PM.bulletImg, _width, _height, _duration, _time);
  PM.cam[1].end();
}

/* initialize robot */
void PMx::initRobot(int _id, ETeam team){
  /* initialize robots */
  PM.robot[_id].init(team);
}

void PMx::drawVWall(int x, int y, int w, int h){
  //       ofDrawBox(x*scale, y*scale, 0, w, h, 10);
  //    PM.cam[0].begin(PM.viewPort[0]);
  //    ofSetColor(0,0,0,140);
  //    ofFill();
  //    ofDrawBox(x*scale, y*scale, 0, w, h, 10);
  //    PM.cam[0].end();
  //
  //    PM.cam[1].begin(PM.viewPort[1]);
  //    ofDrawBox(x*scale, y*scale, 0, w, h, 10);
  //    PM.cam[1].end();
  
  ofSetColor(255, 255, 255);
}


void PMx::_drawField() {
  ofNoFill();
  ofPushStyle();
  ofSetColor(50, 50, 250);
  ofDrawRectangle(0,0,screen_height,screen_width);
  ofDrawRectangle(screen_height,0,screen_height,screen_width);
  ofPopStyle();
  ofFill();
}

void PMx::_drawFieldTexture(){
  /* not necessarily create fbo here (should be written in ofApp::update) */
  PM.backGroundFbo.begin();
  ofDisableNormalizedTexCoords();
  PM.backGroundImg.getTexture().draw(0, 0, screen_height*2, screen_width);
  ofEnableNormalizedTexCoords();
  if (PM.bShowFieldFrame){
    ofNoFill();
    ofPushStyle();
    ofSetColor(50, 50, 250);
    ofDrawRectangle(0,0,1,screen_height,screen_width);
    ofDrawRectangle(screen_height,0,1,screen_height,screen_width);
    ofPopStyle();
    ofFill();
  }
  
  /* minimum example for animation */
  ofPushMatrix();
  ofTranslate(100,100,1);
  ofRotate(ofGetElapsedTimeMillis()%360);
  ofDrawRectangle(0, 0, 100, 100);
  ofPopMatrix();
  PM.backGroundFbo.end();
  
  PM.backGroundFbo.draw(0,0);
}

void PMx::_drawShaderField(){
  PM.currentTime = ofGetElapsedTimef();
  PM.time = PM.currentTime - PM.startTime;
  
  ofPushStyle();
  ofSetColor(255, 255, 255);
  ofDrawRectangle(-1000, -1000, -10, 10000, 10000);
  ofPopStyle();
  PM.fieldShader.begin();
  PM.fieldShader.setUniform1f("time", PM.time);
  PM.fieldShader.setUniform2f("resolution", ofVec2f(screen_height_total, screen_width_total));
  ofDrawRectangle(0, 0, screen_height_total, screen_width_total);
  PM.fieldShader.end();
  if (PM.bShowFieldFrame){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, 0, 1);
    ofSetColor(0,0,0,80);
    ofFill();
    ofDrawRectangle(screen_height_total - PM.shadeWidth1, 0, PM.shadeWidth1 + PM.shadeWidth2, screen_width_total);
    ofPopStyle();
    ofPopMatrix();
  }
  ofNoFill();
  ofPushStyle();
  ofSetColor(50, 50, 250);
//  ofDrawRectangle(0,0,1,screen_height,screen_width);
//  ofDrawRectangle(screen_height,0,1,screen_height,screen_width);
  ofPopStyle();
  ofFill();
}

void PMx::_drawPO(int _id, int state) {
  PM.p_object[_id].draw(PM.pointObjectTexture, state);
  //    PM.p_object[_id].draw(PM.objectShader);
}

void PMx::_drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
  PM.robot[_data->id].draw(_x, _y, _theta, PM.textureImg, _data);
}

void PMx::_drawImg(double _x, double _y, double _theta, ofImage &_img, float duration, float time) {
  ofDisableNormalizedTexCoords();
  if (duration == 0){
    PM.bullet.draw(_x, _y, _theta, _img);
  }
  else {
    PM.alphaShader.begin();
    PM.alphaShader.setUniformTexture("originTexture", _img.getTexture(), 1);
    PM.alphaShader.setUniform1f("time", static_cast<float>((time / duration)*1000));
    PM.bullet.draw(_x, _y, _theta, _img);
    PM.alphaShader.end();
  }
  ofEnableNormalizedTexCoords();
}

/* when changes the texture size */
void PMx::_drawImg(double _x, double _y, double _theta, ofImage &_img, int _width, int _height ,float duration, float time) {
  ofDisableNormalizedTexCoords();
  if (duration == 0){
    PM.bullet.draw(_x, _y, _theta, _img, _width, _height);
  }
  else {
    PM.alphaShader.begin();
    PM.alphaShader.setUniformTexture("originTexture", _img.getTexture(), 1);
    PM.alphaShader.setUniform1f("time", static_cast<float>((time / duration)*1000));
    PM.bullet.draw(_x, _y, _theta, _img, _width, _height);
    PM.alphaShader.end();
  }
  ofEnableNormalizedTexCoords();
}

void PMx::_drawBulletTexture(double _x, double _y, double _theta, ETeam team, float duration, float time){
  ofDisableNormalizedTexCoords();
  if (duration == 0){
    ofPushMatrix();
    ofTranslate(0, 0, 3);
    PM.bullet.bulletFbo[team].getTexture().draw(_x, _y,40,40);
    ofPopMatrix();
  }
  else {
    ofPushMatrix();
    ofTranslate(0, 0, 3);
    PM.alphaShader.begin();
    PM.alphaShader.setUniformTexture("originTexture", PM.bullet.bulletFbo[team].getTexture(), 1);
    PM.alphaShader.setUniform1f("time", static_cast<float>((time / duration)*1000));
    PM.bullet.bulletFbo[team].getTexture().draw(_x, _y);
    ofDrawCircle(_x,_y,30);
    PM.alphaShader.end();
    ofPopMatrix();
  }
  ofEnableNormalizedTexCoords();
}

void PMx::drawText(string content, int x, int y, int size, ofColor textColor){
  //        ofTranslate(0, 0, 600);
  if (size > 51){
    size = 50;
  }
  PM.cam[0].begin();
  ofPushMatrix();
  ofPushStyle();
  ofSetColor(textColor);
  ofTranslate(0,0,132);
  ofRotateZ(90);
  PM.font[size].drawString(content, PM.viewPortPosition[0].x*0.5 - 105 + x*0.3, -PM.viewPortPosition[0].y*0.5 - 50 - y*0.3);
  PM.font[size].drawString(content, 200, 200);
  ofPopStyle();
  ofPopMatrix();
  PM.cam[0].end();
  
}

void PMx::drawTextField(ofColor bgColor){
  PM.cam[0].begin();
  ofPushMatrix();
  ofPushStyle();
  ofTranslate(0,0,130);
  ofSetColor(bgColor);
  ofFill();
  ofDrawRectangle(-300,-300,768*2.5,1500);
  ofPopStyle();
  ofPopMatrix();
  PM.cam[0].end();
}

