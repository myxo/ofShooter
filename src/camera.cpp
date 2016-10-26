#include "camera.h"


Camera::Camera(World *world_ptr_) : world_ptr(world_ptr_){

}

Camera::~Camera(){}


void Camera::update(){
    auto p_center = world_ptr->player->get_center_screen();

    if (p_center.x < WINDOW_BOUND_TO_EXTEND_X){
        window_start_x += p_center.x - WINDOW_BOUND_TO_EXTEND_X;
    } else if (p_center.x > ofGetWidth() - WINDOW_BOUND_TO_EXTEND_X){
        window_start_x += p_center.x - (ofGetWidth() - WINDOW_BOUND_TO_EXTEND_X);
    }

    if (p_center.y < WINDOW_BOUND_TO_EXTEND_Y){
        window_start_y += p_center.y - WINDOW_BOUND_TO_EXTEND_Y;
    } else if (p_center.y > ofGetHeight() - WINDOW_BOUND_TO_EXTEND_Y){
        window_start_y += p_center.y - (ofGetHeight() - WINDOW_BOUND_TO_EXTEND_Y);
    }
}


void Camera::set_camera_by_point(ofVec2f box_point, ofVec2f screen_point){
    window_start_x = box_point.x * WORLD_RESOLUTION - screen_point.x;
    window_start_y = box_point.y * WORLD_RESOLUTION - screen_point.y;
}

void Camera::set_camera_by_entity(worldEntity const *object, ofVec2f screen_point){
    ofVec2f box_point = object->get_center_box();
    set_camera_by_point(box_point, screen_point);
}

void Camera::set_camera_center(worldEntity const *object){
    set_camera_by_entity(object, ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
}


void Camera::push_matrix(){}
void Camera::pop_matrix(){}



b2Vec2 Camera::transformeBoxToScreenCoorditane(b2Vec2 coord){
    coord.x = coord.x * WORLD_RESOLUTION - window_start_x;
    coord.y = coord.y * WORLD_RESOLUTION - window_start_y;
    return coord;
}


b2Vec2 Camera::transformeScreenToBoxCoorditane(b2Vec2 coord){
    coord.x = (coord.x + window_start_x) / WORLD_RESOLUTION;
    coord.y = (coord.y + window_start_y) / WORLD_RESOLUTION;
    return coord;
}


ofVec2f Camera::transformeBoxToScreenCoorditane(ofVec2f coord){
    coord.x = coord.x * WORLD_RESOLUTION - window_start_x;
    coord.y = coord.y * WORLD_RESOLUTION - window_start_y;
    return coord;
}


ofVec2f Camera::transformeScreenToBoxCoorditane(ofVec2f coord){
    coord.x = (coord.x + window_start_x) / WORLD_RESOLUTION;
    coord.y = (coord.y + window_start_y) / WORLD_RESOLUTION;
    return coord;
}
