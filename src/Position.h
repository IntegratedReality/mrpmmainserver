#pragma once

class Position {
	public:
		double x, y, theta; // mm mm rad
		Position():Position(0, 0, 0) {}
		Position(double _x, double _y, double _theta):x(_x), y(_y), theta(_theta) {}
};
