#include "mob.h"
#include "world.h"
#include "boxContactListener.h"
#include "sprite.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

#include <iostream>


Mob::Mob(ofVec2f center, World *world_ptr){
    this->center    = center;
    this->radius    = world_ptr->get_param_double("mob_radius");
    this->life      = world_ptr->get_param_double("mob_life");

    this->world_ptr = world_ptr;

    speed = world_ptr->get_param_double("mob_speed");
    state = MobState::MAY_ATTACK;

    string sprite_path = string(world_ptr->game_parametrs["sprite_root_folder"]) + 
        string(world_ptr->game_parametrs["mob_sprite_filename"]);
    string sprite_dead_path = string(world_ptr->game_parametrs["sprite_root_folder"]) + 
        string(world_ptr->game_parametrs["mob_dead_sprite_filename"]);
    sprite.parse_sprite_file(8, 1, 48, 48, 1, 1, sprite_path.c_str(), 0.2);
    dead_sprite.set_single_image_sprite(sprite_dead_path.c_str());
    sprite.set_frame_number_random();

    box_init(center);
}


// box2d fixture initialize routine
void Mob::box_init(ofVec2f center){
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x, center.y);
    box = world_ptr->box2d_world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;

    dynamicBox.m_p.Set(0, 0);
    dynamicBox.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    // fixtureDef.density = 15.0f;
    // fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = EntityCategory::MOB;
    // collide enttities
    fixtureDef.filter.maskBits = EntityCategory::BUILDINGS | EntityCategory::MOB 
            | EntityCategory::BULLET | EntityCategory::PLAYER ;
    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Mob::update_state(){
    ofVec2f p1 = world_ptr->player->get_center();
    b2Vec2 p2 = box->GetPosition();
    speed_dir.set(p1.x - p2.x, p1.y - p2.y);
    // speed_dir.normalize();

}

void Mob::update(){
    if (state == MobState::DEAD)
        box->SetLinearVelocity(b2Vec2(0, 0));
    else
        box->SetLinearVelocity(b2Vec2(speed_dir.x, speed_dir.y));
    // box->ApplyForce(b2Vec2(speed_dir.x, speed_dir.y), b2Vec2(0, 0), true);
}

void Mob::display(){
    b2Vec2 position = box->GetPosition();
    b2Vec2 screen_coord = world_ptr->transformeBoxToScreenCoorditane(position);

    if (state == MobState::DEAD){
        dead_sprite.display(screen_coord,b2Vec2(0,1));
        return;
    }

    if (state == MobState::MAY_ATTACK)
        ofSetColor(255, 0, 0);
    else if (state == MobState::ATTACKING)
        ofSetColor(255, 255, 0);

    // ofDrawCircle(screen_coord.x, screen_coord.y, radius * World::WORLD_RESOLUTION);
    sprite.display(screen_coord, World::of2box(speed_dir));
}

void Mob::take_damage(int damage){
    if (state == MobState::DEAD)
        return;

    life -= damage;
    if (life <= 0){
        become_dead();
        life = 0;
    }
}

void Mob::become_dead(){
    state = MobState::DEAD;

    // change box2d object category to 'dead_mob' (not collide with player)
    b2Fixture* f = box->GetFixtureList();
    b2Filter filter = f->GetFilterData();
    filter.categoryBits = EntityCategory::DEAD_MOB;
    f->SetFilterData(filter);
}

bool Mob::is_dead(){
    return state == MobState::DEAD;
}

void Mob::make_damage(){
    if (state == MobState::DEAD)
        return;

    world_ptr->player->take_damage(damage);

    state = MobState::ATTACKING;
}

void Mob::collision_event(worldEntity *collision_entity){
    Player *pl = dynamic_cast<Player*>(collision_entity);
    if (pl != nullptr){
        make_damage();
    }   
}