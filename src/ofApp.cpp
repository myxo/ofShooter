#include "ofApp.h"

#include "pistole.h"
#include "world.h"
#include "HUDScreen.h"

#include <stdio.h>
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    world       = std::make_shared<World>();
    hud_screen  = std::make_shared<HUDScreen>(*world);
    hud_debug   = std::make_shared<HUDDebug>(*world);

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    lum.allocate(ofGetWidth(), ofGetHeight(), GL_RED);

    mask_shader.load("../../src/mask.vert", "../../src/mask.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    world->update();
}

//-----------------,--------------------------------------------
void ofApp::draw(){
    lum.begin();
    ofSetColor(0);
    ofBackground(0);
    ofSetColor(255, 255, 255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 100);
    lum.end();

    fbo.begin();
    world->display();
    fbo.end();

    mask_shader.begin();
    // fbo.getTexture().setAlphaMask(lum.getTexture());
    mask_shader.setUniformTexture("texture", fbo.getTexture(), 1);
    mask_shader.setUniformTexture("shadow_map_texture", lum.getTexture(), 1);

    mask_shader.end();

    ofSetColor(255, 255, 255);
    fbo.draw(0,0);

    hud_screen->display();
    hud_debug->display();
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
