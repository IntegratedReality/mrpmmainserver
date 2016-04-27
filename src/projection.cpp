//
//  projection.cpp
//  MRPM3dProjection
//
//  Created by 小林由弥 on 2016/03/11.
//
//

#include "projection.hpp"

void PMClass::initializeProjection(){
	ofEnableSmoothing();
	ofEnableDepthTest();
	glEnable(GL_POINT_SMOOTH);
	ofSetVerticalSync(true);
	ofEnableNormalizedTexCoords();  //textureを持つあらゆるクラスの設定を変更し干渉するので注意
}

//void PMClass::createFieldBgFbo(){
//    backGroundFbo.allocate(screen_height*2, screen_width);
//    
////    backGroundFbo.begin();
////        // write here if you create a background in this program (ex. animations)
////        ofDisableNormalizedTexCoords();
////        backGroundImg.getTexture().draw(0, 0, screen_height*2, screen_width);
////        ofEnableNormalizedTexCoords();
////    backGroundFbo.end();
//}

void pointObject::draw(){
	ofPushMatrix();
	ofTranslate(centerPoint);
	ofRotateZ(angle);
	vbo.draw(GL_TRIANGLE_FAN, 0, 8);
	ofPopMatrix();
}

void pointObject::draw(ofImage &texture){
	ofPushMatrix();
	ofTranslate(centerPoint);
	ofRotateZ(angle);
	texture.bind();
	vbo.draw(GL_TRIANGLE_FAN, 0, 8);
	texture.unbind();
    ofPushStyle();
        ofSetColor(35, 106, 250);
        mesh.drawWireframe();
    ofPopStyle();
	ofPopMatrix();
}


void pointObject::init(int x, int y, float theta){
	centerPoint = ofVec2f(x,y);
	angle = (theta / 2 * M_PI) * 360;
	vertices[0] = ofVec3f(0,0,height_top);
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

	/* translate等を使わない場合(使ったほうが良さそう) */
	//    for (int i = 0; i < 7; i++){
	//        mesh.addVertex(ofVec3f(vertices[i].x + x, vertices[i].y + y, vertices[i].z));
	//    }
	//    mesh.addVertex(ofVec3f(vertices[1].x + x, vertices[1].y + y, vertices[1].z));

	/* 原点に設置しておき、描画時に毎回移動させる */
	for (int i = 0; i < 7; i++){
		mesh.addVertex(ofVec3f(vertices[i].x, vertices[i].y, vertices[i].z));
	}
	mesh.addVertex(ofVec3f(vertices[1].x, vertices[1].y, vertices[1].z));

	mesh.addTexCoord(ofVec2f(0.5,0));
	mesh.addTexCoord(ofVec2f(1,1));
	mesh.addTexCoord(ofVec2f(0,1));
	mesh.addTexCoord(ofVec2f(1,0));
	mesh.addTexCoord(ofVec2f(0,1));
	mesh.addTexCoord(ofVec2f(1,0));
	mesh.addTexCoord(ofVec2f(0,1));

	vbo.setMesh(mesh,GL_STREAM_DRAW);
}

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

void robotModel::draw(int x, int y, float theta, ofImage &texture){

	ofPushMatrix();
	ofTranslate(y*scale,x*scale);
	ofRotateZ(-theta*360/(2*M_PI));
	texture.bind();
	side_vbo.drawElements(GL_TRIANGLE_STRIP,14);
	top_vbo.drawElements(GL_TRIANGLE_STRIP,6);
	texture.unbind();
    ofPushStyle();
        ofSetLineWidth(2);
        ofSetColor(35, 106, 250);
        top_mesh.drawWireframe();
//        side_mesh.drawWireframe();
    ofPopStyle();
	ofPopMatrix();
}

void robotModel::draw(int x, int y, float theta){
	ofPushMatrix();
	ofTranslate(y*scale,x*scale);
	ofRotateZ(-theta*360/(2*M_PI));
	side_mesh.draw();
	top_vbo.drawElements(GL_TRIANGLE_STRIP,6);
	ofPopMatrix();
}

void robotModel::init(){
	for (int i = 0; i < 6; i++){
		top_mesh.addVertex(ofVec3f(vertices_top[i].x, vertices_top[i].y, vertices_top[i].z));
		side_mesh.addVertex(ofVec3f(vertices_top[i].x, vertices_top[i].y, vertices_top[i].z));
	}
	for (int i = 0; i < 6; i++){
		side_mesh.addVertex(ofVec3f(vertices_bottom[i].x, vertices_bottom[i].y, vertices_bottom[i].z));
	}
	/* 上部の板 */
	top_mesh.addIndex(0);
	top_mesh.addIndex(5);
	top_mesh.addIndex(1);
	top_mesh.addIndex(4);
	top_mesh.addIndex(2);
	top_mesh.addIndex(3);

	//テクスチャは正方形とする
	top_mesh.addTexCoord(ofVec2f(0.5,0));
	top_mesh.addTexCoord(ofVec2f(0.9,0.25));
	top_mesh.addTexCoord(ofVec2f(0.9,0.75));
	top_mesh.addTexCoord(ofVec2f(0.5,1));
	top_mesh.addTexCoord(ofVec2f(0.1,0.75));
	top_mesh.addTexCoord(ofVec2f(0.1,0.25));

	/* 伸びずに表示される例 */
	//    top_mesh.addTexCoord(ofVec2f(0.5,0));
	//    top_mesh.addTexCoord(ofVec2f(0.9,0.25));
	//    top_mesh.addTexCoord(ofVec2f(0.9,0.75));
	//    top_mesh.addTexCoord(ofVec2f(0.5,1));
	//    top_mesh.addTexCoord(ofVec2f(0.1,0.75));
	//    top_mesh.addTexCoord(ofVec2f(0.1,0.25));

	/* triangle_stripで側面を作っている */
	side_mesh.addIndex(6);
	side_mesh.addIndex(0);
	side_mesh.addIndex(7);
	side_mesh.addIndex(1);
	side_mesh.addIndex(8);
	side_mesh.addIndex(2);
	side_mesh.addIndex(9);
	side_mesh.addIndex(3);
	side_mesh.addIndex(10);
	side_mesh.addIndex(4);
	side_mesh.addIndex(11);
	side_mesh.addIndex(5);
	side_mesh.addIndex(6);
	side_mesh.addIndex(0);

	side_mesh.addTexCoord(ofVec2f(0.8,0));
	side_mesh.addTexCoord(ofVec2f(0.2,0));
	side_mesh.addTexCoord(ofVec2f(0.8,0));
	side_mesh.addTexCoord(ofVec2f(0.2,0));
	side_mesh.addTexCoord(ofVec2f(0.8,0));
	side_mesh.addTexCoord(ofVec2f(0.2,0));
	side_mesh.addTexCoord(ofVec2f(1,1));
	side_mesh.addTexCoord(ofVec2f(0,1));
	side_mesh.addTexCoord(ofVec2f(1,1));
	side_mesh.addTexCoord(ofVec2f(0,1));
	side_mesh.addTexCoord(ofVec2f(1,1));
	side_mesh.addTexCoord(ofVec2f(0,1));

	top_vbo.setMesh(top_mesh, GL_DYNAMIC_DRAW);  //注意 : static_drawで良いのか不明
	side_vbo.setMesh(side_mesh, GL_DYNAMIC_DRAW);
}
