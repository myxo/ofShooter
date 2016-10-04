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
}

//--------------------------------------------------------------
void ofApp::update(){
    world->update();
}

//-----------------,--------------------------------------------
void ofApp::draw(){
    world->display();
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
    // ofVec2f mouse_box_coord = World::box2of(world->transformeScreenToBoxCoorditane(b2Vec2(x, y)));
    ofVec2f mouse(x, y);
    // ofVec2f player_center = world->player->get_center_screen();
    // ofVec2f speed_dir(mouse.x - player_center.x, mouse.y - player_center.y);
    //ofVec2f speed_dir =  World::box2of(World::transformeScreenToBoxCoorditane(screen_speed_dir));
    world->gun_fire(mouse);
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
