#pragma once 

#include "ofxBox2D.h"

class SysBox2D {
	public:
		static ofxBox2d* getInstance() {
			static ofxBox2d box2d;
			return &box2d;
		}
	private:
		SysBox2D();
};
