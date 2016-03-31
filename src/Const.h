#pragma once

constexpr int FPS = 30;
constexpr double TIME_PER_FRAME = 1.0 / FPS;

constexpr int WIDTH_OF_FIELD = 2700;
constexpr int HEIGHT_OF_FIELD = 1820;
constexpr double SCALE = 0.25;

constexpr int NUM_OF_ROBOT = 6;
constexpr int RADIUS_OF_ROBOT = 100;

constexpr int NUM_OF_POINT_OBJ = 3;
constexpr int RADIUS_OF_POINT_OBJ = 125;
constexpr int POINT_OBJ_0_X = WIDTH_OF_FIELD / 2;
constexpr int POINT_OBJ_0_Y = HEIGHT_OF_FIELD / 2;
constexpr int POINT_OBJ_1_X = WIDTH_OF_FIELD / 2 - WIDTH_OF_FIELD / 4;
constexpr int POINT_OBJ_1_Y = HEIGHT_OF_FIELD / 2 - HEIGHT_OF_FIELD / 4;
constexpr int POINT_OBJ_2_X = WIDTH_OF_FIELD / 2 + WIDTH_OF_FIELD / 4;
constexpr int POINT_OBJ_2_Y = HEIGHT_OF_FIELD / 2 + HEIGHT_OF_FIELD / 4;
