#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.windowMode = OF_FULLSCREEN;
	settings.decorated = false;
	settings.width = 1024;
	settings.height = 768 * 2;
	settings.resizable = false;

	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
