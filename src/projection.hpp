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
#include "RobotData.h"
#include "EState.h"
#include <stdio.h>
#include <array>
#include <cmath>

const double root3 = sqrt(3);
/* screen size (default : XGA) */
const int screen_width = 1024;
const int screen_height = 768;
//const int screen_width = 1800;
//const int screen_height = 1350;
const double scale = 0.57;

/* set team color */
const std::array<ofColor,3> teamColor = {
    ofColor(0,191,255,255),
    ofColor(255,163,0,255),
    ofColor(255,255,255,255)
};
const std::array<ofColor,3> enhancedTeamColor = {
    ofColor(40,220,255,255),
    ofColor(255,190,40,255),
    ofColor(255,255,255,255)
};
const std::array<ofColor,3> killedColor = {
    ofColor(0,80,150,180),
    ofColor(180,70,180),
    ofColor(255,255,255,180)
};
const ofColor recoveryColor = ofColor(255,255,0);

class bullets{
	/* images are drawn by these functions */
	public:
		inline void draw(int x, int y,int theta, ofImage &image, int width, int height){
			ofPushMatrix();
			{
				//ofTranslate(y*scale,x*scale);
                ofTranslate(y,x,3);
				ofRotate(theta*360/(2*M_PI));
				image.getTexture().draw(0,0,width,height);
			}
			ofPopMatrix();
		}
    
        inline void draw(int x, int y, int theta, ofImage &image){
            ofPushMatrix();
            {
                //ofTranslate(y*scale,x*scale);
                ofTranslate(y,x,3);
                ofRotate(theta*360/(2*M_PI));
                image.draw(0,0);
            }
            ofPopMatrix();
        }
/*
		inline void draw(ofVec2f point, int theta, ofImage &image){
			ofPushMatrix();
			{
				ofTranslate(point);
				ofRotate(theta*360/(2*M_PI));
				image.draw(0,0);
			}
			ofPopMatrix();
		}
*/
		inline void draw(int x, int y, int theta){
			ofPushMatrix();
			ofPushStyle();
			{
				ofTranslate(y*scale, x*scale);
				ofRotate(theta*360/(2*M_PI));
				/* of上で弾を作成して表示する場合はここに記述 */
				ofDrawCircle(y*scale, x*scale, 20);
			}
			ofPopStyle();
			ofPopMatrix();
		}
    
        void createBullet(ofColor &color);

		bullets(){
		}
};

class virtualWall{

    public:
    void draw(ofVec2f coord);
    virtualWall(){
        
    }

};

class robotModel{
	/* variables */
	public:
		//const int diameter_bottom = 58.8,diameter_top = 35.3,height_bottom = 1,height_top = 58.8;   //size of the robot
		const int diameter_bottom = 68.8,diameter_top = 35.3,height_bottom = 1,height_top = 61.8;   //size of the robot
		ofVec2f centerPoint;
		ofMesh top_mesh,side_mesh;
		ofVbo top_vbo,side_vbo;
        ETeam team;
        EState currentState;
	private:
		std::array<ofVec3f,6> vertices_bottom;
		std::array<ofVec3f,6> vertices_top;

    /* functions */
	public:
		void draw(int x, int y, float theta, const RobotData *robdata);
		void draw(int x, int y, float theta, ofImage &texture, const RobotData *robdata);
		void init(const ETeam _team);

		robotModel(){
			/* set a 3D-model */
			vertices_bottom[0] = ofVec3f(0, -diameter_bottom, height_bottom);
			vertices_bottom[1] = ofVec3f(0.5*diameter_bottom*root3, -0.5*diameter_bottom, height_bottom);
			vertices_bottom[2] = ofVec3f(0.5*diameter_bottom*root3, 0.5*diameter_bottom, height_bottom);
			vertices_bottom[3] = ofVec3f(0, diameter_bottom, height_bottom);
			vertices_bottom[4] = ofVec3f(-0.5*diameter_bottom*root3, 0.5*diameter_bottom, height_bottom);
			vertices_bottom[5] = ofVec3f(-0.5*diameter_bottom*root3, -0.5*diameter_bottom, height_bottom);

			vertices_top[0] = ofVec3f(0, -diameter_top, height_top);
			vertices_top[1] = ofVec3f(0.5*diameter_top*root3, -0.5*diameter_top, height_top);
			vertices_top[2] = ofVec3f(0.5*diameter_top*root3, 0.5*diameter_top, height_top);
			vertices_top[3] = ofVec3f(0, diameter_top, height_top);
			vertices_top[4] = ofVec3f(-0.5*diameter_top*root3, 0.5*diameter_top, height_top);
			vertices_top[5] = ofVec3f(-0.5*diameter_top*root3, -0.5*diameter_top, height_top);

			top_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			side_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            
		}
};

class pointObject{
	/* variables */
	public:
		//const int diameter = 68.5,height_bottom = 1,height_top = 76.4;     //size of the point object
		const int diameter = 68.5,height_bottom = 1,height_top = 110;

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
		void draw(int score);
		void draw(ofImage &texture, int score);
        void draw(ofShader &shader, int score);
		inline void setTextureScale(int scale){ //引数は％(デフォルト100) テクスチャの調整機能は必要に応じて実装
			texture_scale = (scale/100) - 1;
		}

		pointObject() {
			/* set a 3D-model */
			vertices[1] = ofVec3f(0, -diameter, height_bottom);
			vertices[2] = ofVec3f(0.5*diameter*root3, -0.5*diameter, height_bottom);
			vertices[3] = ofVec3f(0.5*diameter*root3, 0.5*diameter, height_bottom);
			vertices[4] = ofVec3f(0, diameter, height_bottom);
			vertices[5] = ofVec3f(-0.5*diameter*root3, 0.5*diameter, height_bottom);
			vertices[6] = ofVec3f(-0.5*diameter*root3, -0.5*diameter, height_bottom);

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
        void createFieldBgFbo();

		/* texture, effects */
		ofImage textureImg;
		ofImage pointObjectTexture;
        ofImage backGroundImg;
        ofFbo backGroundFbo;
        ofShader fieldShader;
        ofShader objectShader;
        ofShader alphaShader;
        ofShader robotShader;

		/* 3Dobjects */
		std::array<pointObject,3> p_object;
		std::array<robotModel,6> robot;

		/* effect, bullet */
		bullets bullet;
		ofImage bulletImg;  //ここに置く？
    
        /* text */
        std::array<ofTrueTypeFont,35> font;
    
        /* time control */
        float startTime;
        float currentTime;
        float time;

		/* cameras */
		std::array<ofCamera,2> cam;
		std::array<ofRectangle,2> viewPort;
		ofVec2f viewPortPosition1;
		ofVec2f viewPortPosition2;
		bool bConfPort1 = false;
		bool bConfPort2 = false;
        bool bConfShade1 = false;
        bool bconfShade2 = false;
        bool bShowFieldFrame = true;
		double camAngle;
		int projectorHeight;
        int shadeWidth1 = 0;
        int shadeWidth2 = 0;

		void initializeProjection();

		PMClass(){
			//--
			/* set up viewPorts */
			viewPortPosition1.x = 15;
			viewPortPosition1.y = -30;
			viewPortPosition2.x = 16;
			viewPortPosition2.y = screen_height-34;

			viewPort[0].setSize(screen_width,screen_height);
			viewPort[1].setSize(screen_width,screen_height);
			viewPort[0].setPosition(viewPortPosition1.x, viewPortPosition1.y);
			viewPort[1].setPosition(viewPortPosition2.x, viewPortPosition2.y);

			//---
			/* set up projector position */
			projectorHeight = 2700;
			cam[0].setPosition(ofVec3f(screen_height/2,screen_width/2,projectorHeight));
			cam[1].setPosition(ofVec3f(screen_height*1.5,screen_width/2,projectorHeight));
			cam[0].roll(90);
			cam[1].roll(90);
			/* カメラの視野の広さ(角度) */
			camAngle = 18;
			cam[0].setFov(camAngle);
			cam[1].setFov(camAngle);
			cout << "cam0 : " << cam[0].getX() << ":" << cam[0].getY() << ":" << cam[0].getZ() << endl;
			cout << "cam1 : " << cam[1].getX() << ":" << cam[1].getY() << ":" << cam[1].getZ() << endl;
			//---

			/* set point objects(x,y,theta) */
			p_object[0].init(screen_height/2,screen_width/4, 2); //(x,y,theta)
			p_object[1].init(screen_height,screen_width/2, 1);
			p_object[2].init(screen_height*1.5,screen_width*0.75, 0.5);

			bulletImg.setAnchorPercent(0.5, 0.5);   //中心で指定できるように
		}
};

#endif /* projection_hpp */
