#pragma once

constexpr int FPS = 60;
constexpr double TIME_PER_FRAME = 1.0 / FPS;

constexpr int GAME_DURATION_MSEC = 3*60*1000;

constexpr int WIDTH_OF_FIELD = 1600;
constexpr int HEIGHT_OF_FIELD = 2400;
constexpr int SCREEN_WIDTH = 480;   //screen size of the projector [px]
constexpr int SCREEN_HEIGHT = 800;
constexpr double scale = SCREEN_WIDTH/static_cast<double>(900);  //  convert from [mm] to [pix]  ( [pix] / [mm] )  900 means the width of projection area [mm]

constexpr double SCALE_SIM = 0.25;

constexpr int RADIUS_OF_ROBOT = 100;
constexpr int MARGIN_OF_COLLISION = 30;

constexpr int NUM_OF_POINT_OBJ = 3;
constexpr int RADIUS_OF_POINT_OBJ = 125;
constexpr int POINT_OBJ_0_X = WIDTH_OF_FIELD / 2;
constexpr int POINT_OBJ_0_Y = HEIGHT_OF_FIELD / 2;
constexpr int POINT_OBJ_1_X = WIDTH_OF_FIELD / 2 - WIDTH_OF_FIELD / 4;
constexpr int POINT_OBJ_1_Y = HEIGHT_OF_FIELD / 2 - HEIGHT_OF_FIELD / 4;
constexpr int POINT_OBJ_2_X = WIDTH_OF_FIELD / 2 + WIDTH_OF_FIELD / 4;
constexpr int POINT_OBJ_2_Y = HEIGHT_OF_FIELD / 2 + HEIGHT_OF_FIELD / 4;

//projection

//point object
constexpr int diameter_po = 70.5;
constexpr int height_bottom_po = 1;
constexpr int height_top_po = 110;
//robot
constexpr int diameter_bottom_ro = 58.8;
constexpr int diameter_top_ro = 35.3;
constexpr int height_bottom_ro = 1;
constexpr int height_top_ro = 61.8;   //size of the robot


//in
constexpr int PORT_MAINRCV = 8000;

//out
constexpr int PORT_ROBOT = 8000;
constexpr int PORT_OPERATOR = 8001;

extern bool sim;
