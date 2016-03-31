#pragma once

enum EDirection {
	NO_INPUT,
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT
};

struct Operation {
	EDirection direction;
	bool shot;
};

