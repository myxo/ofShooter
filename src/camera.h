#pragma once

#include "world.h"
#include "worldEntity.h"

class Camera{
public:
    Camera(World *world_ptr_);
    ~Camera();

    void set_camera_by_point(ofVec2f box_point, ofVec2f screen_point);
    void set_camera_by_entity(const worldEntity &object, ofVec2f screen_point);
    void set_camera_center(const worldEntity &object);
    void push_matrix();
    void pop_matrix();

    b2Vec2 transformeBoxToScreenCoorditane(b2Vec2 coord);
    ofVec2f transformeBoxToScreenCoorditane(ofVec2f coord);
    b2Vec2 transformeScreenToBoxCoorditane(b2Vec2 coord);
    ofVec2f transformeScreenToBoxCoorditane(ofVec2f coord);

    void update();
// private:
public:
    int window_start_x = 0, window_start_y = 0; // for screen transition
    const int WINDOW_BOUND_TO_EXTEND_X = 100; // todo. rename + if screen is big, get 1/5 of window_width
    const int WINDOW_BOUND_TO_EXTEND_Y = 100; // todo. -//-
    int WORLD_RESOLUTION = 16; // pixels in meter


    World *world_ptr;
};