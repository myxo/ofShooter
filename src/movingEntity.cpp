#include "movingEntity.h"
#include "ofMain.h"
#include "world.h"

#include "Box2D/Box2D.h"

ofVec2f movingEntity::get_center_box() const{
    b2Vec2 p = box->GetPosition();
    ofVec2f center(p.x, p.y);
    return center;
}
ofVec2f movingEntity::get_center_screen() const{
    ofVec2f center = World::box2of(world_ptr->transformeBoxToScreenCoorditane(box->GetPosition()));
    return center;
}