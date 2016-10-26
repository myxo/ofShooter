#include "ofMain.h"
#include "ofApp.h"
#include <exception>

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	try{
		ofRunApp(new ofApp());
	} catch (std::exception &e){
		cout << "main exception: " << e.what() << endl;
	}

}
