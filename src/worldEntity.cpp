#include "worldEntity.h"
#include "world.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

size_t worldEntity::obj_count = 0;

worldEntity::worldEntity(){
        obj_id = obj_count++;
}

worldEntity::~worldEntity(){}

ofVec2f worldEntity::get_center_box() const{
    b2Vec2 p = box->GetPosition();
    ofVec2f center(p.x, p.y);
    return center;
}

ofVec2f worldEntity::get_center_screen() const{
    ofVec2f center = World::box2of(world_ptr->camera->transformeBoxToScreenCoorditane(box->GetPosition()));
    return center;
}