//
//  projection.hpp
//  MRPM3dProjection
//
//  Created by 小林由弥 on 2016/03/11.
//
//

#ifndef projection_hpp
#define projection_hpp

#include "ofMain.h"
#include <stdio.h>
#include <array>
#include <cmath>

const double root3 = sqrt(3);
/* screen size (default : XGA) */
const int screen_width = 1024;
const int screen_height = 768;


class bullets{
	public:
		inline void draw(int x, int y,int theta, ofImage &image){
			ofPushMatrix();
			{
				ofTranslate(x,y);
				ofRotate(theta*360/(2*M_PI));
				image.draw(0,0);
			}
			ofPopMatrix();
		}

		inline void draw(ofVec2f point, int theta, ofImage &image){
			ofPushMatrix();
			{
				ofTranslate(point);
				ofRotate(theta*360/(2*M_PI));
				image.draw(0,0);
			}
			ofPopMatrix();
		}

		inline void draw(int x, int y, int theta){
			ofPushMatrix();
			ofPushStyle();
			{
				ofTranslate(x, y);
				ofRotate(theta*360/(2*M_PI));
				/* of上で弾を作成して表示する場合はここに記述 */
				ofDrawCircle(x, y, 20);
			}
			ofPopStyle();
			ofPopMatrix();
		}

		bullets(){
		}
};

class robotModel{
	/* variables */
	public:
		const int radius_bottom = 80,radius_top = 40,height_bottom = 20,height_top = 120;   //size of the robot
		ofVec2f centerPoint;
		ofMesh top_mesh,side_mesh;
		ofVbo top_vbo,side_vbo;
	private:
		std::array<ofVec3f,6> vertices_bottom;
		std::array<ofVec3f,6> vertices_top;

		/* functions */
	public:
		void draw(int x, int y, float theta);
		void draw(int x, int y, float theta, ofImage &texture);
		void init();

		robotModel(){
			/* set a 3D-model */
			vertices_bottom[0] = ofVec3f(0, -radius_bottom, height_bottom);
			vertices_bottom[1] = ofVec3f(0.5*radius_bottom*root3, -0.5*radius_bottom, height_bottom);
			vertices_bottom[2] = ofVec3f(0.5*radius_bottom*root3, 0.5*radius_bottom, height_bottom);
			vertices_bottom[3] = ofVec3f(0, radius_bottom, height_bottom);
			vertices_bottom[4] = ofVec3f(-0.5*radius_bottom*root3, 0.5*radius_bottom, height_bottom);
			vertices_bottom[5] = ofVec3f(-0.5*radius_bottom*root3, -0.5*radius_bottom, height_bottom);

			vertices_top[0] = ofVec3f(0, -radius_top, height_top);
			vertices_top[1] = ofVec3f(0.5*radius_top*root3, -0.5*radius_top, height_top);
			vertices_top[2] = ofVec3f(0.5*radius_top*root3, 0.5*radius_top, height_top);
			vertices_top[3] = ofVec3f(0, radius_top, height_top);
			vertices_top[4] = ofVec3f(-0.5*radius_top*root3, 0.5*radius_top, height_top);
			vertices_top[5] = ofVec3f(-0.5*radius_top*root3, -0.5*radius_top, height_top);

			top_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			side_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		}
};

class pointObject{
	/* variables */
	public:
		const int radius = 80,height_bottom = 3,height_top = 110;     //size of the point object

		ofVec2f centerPoint;
		float angle;
		ofMesh mesh;
		ofVbo vbo;
		int texture_scale = 0;

	private:
		std::array<ofVec3f,7> vertices;    //オブジェクトの形状(固定)

		/* functions */
	public:
		void init(int x, int y, float theta);
		void draw();
		void draw(ofImage &texture);
		inline void setTextureScale(int scale){ //引数は％(デフォルト100) テクスチャの調整機能は必要に応じて実装
			texture_scale = (scale/100) - 1;
		}

		pointObject() {
			/* set a 3D-model */
			vertices[1] = ofVec3f(0, -radius, height_bottom);
			vertices[2] = ofVec3f(0.5*radius*root3, -0.5*radius, height_bottom);
			vertices[3] = ofVec3f(0.5*radius*root3, 0.5*radius, height_bottom);
			vertices[4] = ofVec3f(0, radius, height_bottom);
			vertices[5] = ofVec3f(-0.5*radius*root3, 0.5*radius, height_bottom);
			vertices[6] = ofVec3f(-0.5*radius*root3, -0.5*radius, height_bottom);

			mesh.addTexCoord(ofVec2f(0,0));
			mesh.addTexCoord(ofVec2f(0,1));
			mesh.addTexCoord(ofVec2f(0.5,1));
			mesh.addTexCoord(ofVec2f(1,1));
			mesh.addTexCoord(ofVec2f(0.5,1));
			mesh.addTexCoord(ofVec2f(0,1));
			mesh.addTexCoord(ofVec2f(0.5,1));
			mesh.addTexCoord(ofVec2f(1,1));
		}
};

class PMClass{
	public:

		/* texture, effects */
		ofImage textureImg;
		ofImage pointObjectTexture;

		/* 3Dobjects */
		std::array<pointObject,3> p_object;
		std::array<robotModel,6> robot;

		/* effect, bullet */
		bullets bullet;
		ofImage bulletImg;  //ここに置く？

		/* cameras */
		std::array<ofCamera,2> cam;
		std::array<ofRectangle,2> viewPort;
		ofVec2f viewPortPosition1;
		ofVec2f viewPortPosition2;
		bool bConfPort1 = false;
		bool bConfPort2 = false;
		double camAngle;
		int projectorHeight;

		void initializeProjection();

		PMClass(){
			//--
			/* set up viewPorts */
			viewPortPosition1.x = 0;
			viewPortPosition1.y = 0;
			viewPortPosition2.x = 0;
			viewPortPosition2.y = screen_height;

			viewPort[0].setSize(screen_width,screen_height);
			viewPort[1].setSize(screen_width,screen_height);
			viewPort[0].setPosition(viewPortPosition1.x, viewPortPosition1.y);
			viewPort[1].setPosition(viewPortPosition2.x, viewPortPosition2.y);

			//---
			/* set up projector position */
			projectorHeight = 1550;
			cam[0].setPosition(ofVec3f(screen_height/2,screen_width/2,projectorHeight));
			cam[1].setPosition(ofVec3f(screen_height*1.5,screen_width/2,projectorHeight));
			cam[0].roll(90);
			cam[1].roll(90);
			/* カメラの視野の広さ(角度) */
			camAngle = 31.5;
			cam[0].setFov(camAngle);   //35.45
			cam[1].setFov(camAngle);
			cout << "cam0 : " << cam[0].getX() << ":" << cam[0].getY() << ":" << cam[0].getZ() << endl;
			cout << "cam1 : " << cam[1].getX() << ":" << cam[1].getY() << ":" << cam[1].getZ() << endl;
			//---

			/* initialize robots */
			for (int i = 0; i < 6; i++){
				robot[i].init();
			}
			/* set point objects(x,y,theta) */
			p_object[0].init(screen_height/2,screen_width/4, 2); //(x,y,theta)
			p_object[1].init(screen_height,screen_width/2, 1);
			p_object[2].init(screen_height*1.5,screen_width*0.75, 0.5);

			bulletImg.setAnchorPercent(0.5, 0.5);   //中心で指定できるように
		}
};

#endif /* projection_hpp */
