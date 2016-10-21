#pragma once

#include "EItem.h"
#include "Position.h"
#include "CollisionObject.h"
#include "ofxBox2d.h"

class Item : public CollisionObject {
public:
  void init(Position _pos, EItem _item);
  void update();
  void draw();
  
  bool getDeleteFlag() {return deleteFlag;}
  
  virtual void collisionListner(CollisionObject *other);
  virtual int getValue();
private:
  int x, y, radius;
  EItem itemType;
  bool deleteFlag;
  ofxBox2dCircle b2dCircle;
};
