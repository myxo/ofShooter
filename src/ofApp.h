#pragma once

#include "ofMain.h"
#include "world.h"
#include "HUDScreen.h"
#include "HUDDebug.h"

#define N_KEY_PRESS 0x1
#define S_KEY_PRESS 0x2
#define W_KEY_PRESS 0x4
#define E_KEY_PRESS 0x8


class ofApp : public ofBaseApp{
	public:
		unsigned int key_pressed = 0;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		std::shared_ptr<World> 		world;
		std::shared_ptr<HUDScreen> 	hud_screen;
		std::shared_ptr<HUDDebug>	hud_debug;

		ofShader mask_shader;
		ofFbo fbo, lum;

};
