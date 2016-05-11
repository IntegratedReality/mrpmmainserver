#pragma once

#include "RobotData.h"
#include "projection.hpp"

class PMx {
	public:
		static PMx* getInstance() {
			static PMx instance;
			return &instance;
		}

		void setup();
		void keyPressed(int key);
		void drawField();
        void drawFieldTexture();
        void drawShaderField();
		void drawPO(int _id);
		void drawRobot(double _x, double _y, double _theta, const RobotData *_data);
		void drawImg(double _x, double _y, double _theta, ofImage &_img);
        void drawText(string content,int x,int y,int size = 24, ofColor textColor=ofColor(255,255,255));
        void drawTextField(ofColor bgColor=ofColor(0,0,0,150));

	private:
		PMx() {};
		PMClass PM;

		// for one camera
		void _drawField();
        void _drawFieldTexture();
        void _drawShaderField();
		void _drawPO(int _id);
		void _drawRobot(double _x, double _y, double _theta, const RobotData *_data);
		void _drawImg(double _x, double _y, double _theta, ofImage &_img);
};
