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
		void drawPO(int _id);
		void drawRobot(double _x, double _y, double _theta, const RobotData *_data);
		void drawImg(double _x, double _y, double _theta, ofImage &_img);

	private:
		PMx() {};
		PMClass PM;

		// for one camera
		void _drawField();
		void _drawPO(int _id);
		void _drawRobot(double _x, double _y, double _theta, const RobotData *_data);
		void _drawImg(double _x, double _y, double _theta, ofImage &_img);
};
