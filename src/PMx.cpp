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
  PM.pointObjectTexture.load("texture.jpg");  //example texture
  PM.bulletImg.load("blue.png");  //image for bullet
  PM.backGroundImg.load("bg.jpg");
  PM.virtualWallTexture.load("mesh.jpg");
  
  /* load shaders */
  PM.fieldShader.load("test.vert", "water.frag");
  
  /* load font */
  for (int i = 1; i < 51; i++){
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
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawField();
    PM.cam[i].end();
  }
}

void PMx::drawFieldTexture() {
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawFieldTexture();
    PM.cam[i].end();
  }
}

void PMx::drawShaderField(){
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawShaderField();
    PM.cam[i].end();
  }
  
}

void PMx::drawPO(int _id, int state) {
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawPO(_id, state);
    PM.cam[i].end();
  }
}

void PMx::drawRobot(double _x, double _y, double _theta, const RobotData *_data) {
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawRobot(_x, _y, _theta, _data);
    PM.cam[i].end();
  }
}

void PMx::drawImg(double _x, double _y, double _theta, ofImage &_img, float _duration, float _time) {
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawImg(_x, _y, _theta, _img, _duration, _time);
    PM.cam[i].end();
  }
}

/* when you want to change the texture size */
void PMx::drawImg(double _x, double _y, double _theta, ofImage &_img, int _width, int _height, float _duration, float _time) {
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawImg(_x, _y, _theta, _img, _width, _height, _duration, _time);
    PM.cam[i].end();
  }
}

void PMx::drawBullet(double _x, double _y, double _theta,ETeam team, float _duration, float _time){
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    ofPushMatrix();
    ofTranslate(0, 0, 2);
    _drawBulletTexture(_y*scale, _x*scale, _theta, team);
    ofPopMatrix();
    PM.cam[i].end();
  }
}

void PMx::drawBullet(double _x, double _y, double _theta ,int _width, int _height, float _duration, float _time){

  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    ofPushMatrix();
    ofTranslate(0, 0, 2);
    _drawImg(_x, _y, _theta, PM.bulletImg, _width, _height, _duration, _time);
    ofPopMatrix();
    PM.cam[i].end();
  }
  
}

void PMx::drawText(string content, int x, int y, int size, ofColor textColor){
  //        ofTranslate(0, 0, 600);
  if (size > 51){
    size = 50;
  }
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawText(content, x, y, size, textColor);
    PM.cam[i].end();
  }
  
}

void PMx::drawTextField(ofColor bgColor){
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    _drawTextField(bgColor);
    PM.cam[i].end();
  }
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
  
  for (int i = 0; i < 4; i++){
    PM.cam[i].begin(PM.viewPort[i]);
    ofPopStyle();
    ofFill();
    ofDrawRectangle(y, x, w, h);
    ofNoFill();
    PM.cam[i].end();
  }
  
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
  
//  ofPushStyle();
//  ofSetColor(255, 255, 255);
//    ofDrawRectangle(0, 0, screen_height_total, screen_width_total);
//  ofPopStyle();
  PM.fieldShader.begin();
  PM.fieldShader.setUniform1f("time", PM.time);
  PM.fieldShader.setUniform2f("resolution", ofVec2f(screen_height_total, screen_width_total));
  ofDrawRectangle(0, 0, screen_height_total, screen_width_total);
  PM.fieldShader.end();
  if (PM.bShowFieldFrame){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, 0, 1);
    ofSetColor(0,0,0,64);
    ofFill();
    ofDrawRectangle(screen_height_total*0.5 - PM.shadeWidth1, 0, PM.shadeWidth1*2, screen_width*2);  //compensate the brightness of overlaped areas
    ofDrawRectangle(0, screen_width_total*0.5 - PM.shadeWidth2, screen_height*2, PM.shadeWidth2*2);  //compensate the brightness of overlaped areas
    ofPopStyle();
    ofPopMatrix();
  }
//  ofNoFill();
//  ofPushStyle();
//  ofSetColor(50, 50, 250);
//  ofDrawRectangle(0,0,1,screen_height,screen_width);
//  ofDrawRectangle(screen_height,0,1,screen_height,screen_width);
//  ofPopStyle();
//  ofFill();
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

/* when you want to change the texture size */
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

void PMx::_drawText(string content, int x, int y, int size, ofColor textColor){
  if (size > 51){
    size = 50;
  }
  ofPushMatrix();
  ofPushStyle();
    ofSetColor(textColor);
    ofTranslate(PM.viewPortPosition[0].y + x, PM.viewPortPosition[0].x + y,112); //using z-index like layers
    ofRotateZ(90);
    PM.font[size].drawString(content, 0, 0);
  ofPopStyle();
  ofPopMatrix();
  
}

void PMx::_drawTextField(ofColor bgColor){
  ofPushMatrix();
  ofPushStyle();
    ofTranslate(0,0,111);
    ofNoFill();
    glLineWidth(5);
    ofSetColor(150,150,150);
    ofDrawRectangle(50,50,screen_height_total-100,screen_width_total-100);
    ofFill();
    ofSetColor(bgColor);
    ofDrawRectangle(50,50,screen_height_total-100,screen_width_total-100);  //今は暗くしているだけ、fboで作っておけばもっとリッチにできる
  ofPopStyle();
  ofPopMatrix();
}

