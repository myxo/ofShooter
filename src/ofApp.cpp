#include "ofApp.h"

#include "pistole.h"
#include "world.h"
#include "HUDScreen.h"

#include <stdio.h>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(150);

    world       = std::make_shared<World>();
    hud_screen  = std::make_shared<HUDScreen>(*world);
    hud_debug   = std::make_shared<HUDDebug>(*world);

    mask_fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    world->update();
}

//-----------------,--------------------------------------------
void ofApp::draw(){
    // ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    world->display();
    hud_screen->display();
    hud_debug->display();

    // mask_fbo.begin();
    // // ofSetColor(0, 0, 0, 0);
    // // ofClear(0, 0, 0, 0);
    // // ofDrawRectangle(0, 0, 1024,768);
    // ofSetColor(255, 255, 255, 255);
    // ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 100, 100);
    // mask_fbo.end();

    // // ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    // ofSetColor(255, 255, 255);
    // mask_fbo.draw(0, 0);
    // ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT)     key_pressed |= W_KEY_PRESS;
    if (key == OF_KEY_RIGHT)    key_pressed |= E_KEY_PRESS;
    if (key == OF_KEY_UP)       key_pressed |= N_KEY_PRESS;
    if (key == OF_KEY_DOWN)     key_pressed |= S_KEY_PRESS;


    if (key == 'a')     key_pressed |= W_KEY_PRESS;
    if (key == 'd')     key_pressed |= E_KEY_PRESS;
    if (key == 'w')     key_pressed |= N_KEY_PRESS;
    if (key == 's')     key_pressed |= S_KEY_PRESS;

    world->player->change_speed_dir(key_pressed);

    if (key == '1')     world->bullet_factory->change_gun(1);
    if (key == '2')     world->bullet_factory->change_gun(2);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_LEFT)     key_pressed ^= W_KEY_PRESS;
    if (key == OF_KEY_RIGHT)    key_pressed ^= E_KEY_PRESS;
    if (key == OF_KEY_UP)       key_pressed ^= N_KEY_PRESS;
    if (key == OF_KEY_DOWN)     key_pressed ^= S_KEY_PRESS;

    if (key == 'a')     key_pressed ^= W_KEY_PRESS;
    if (key == 'd')     key_pressed ^= E_KEY_PRESS;
    if (key == 'w')     key_pressed ^= N_KEY_PRESS;
    if (key == 's')     key_pressed ^= S_KEY_PRESS;


    world->player->change_speed_dir(key_pressed);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    world->gun_fire(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
