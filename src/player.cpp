#include "player.h"
#include "ofApp.h"
#include "world.h"
#include "movingEntity.h"
#include "boxContactListener.h"
#include "sprite.h"

#include "ofMain.h"

#include <stdio.h>
#include "Box2D/Box2D.h"

Player::Player(ofVec2f center, double radius, int life, World *world_ptr){
    this->center    = center;
    this->radius    = radius;
    this->life      = life;
    this->world_ptr = world_ptr;

    speed_dir.set(0, 0);
    speed = 10;

    sprite.parse_sprite_file(8, 1, 32, 54, 1, 1, "/home/myxo/ssyp/of/shooter/data/shooterofzombones.png", 0.4);

    box_init();
}

void Player::box_init(){
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(center.x, center.y);
    box = world_ptr->box2d_world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;

    dynamicBox.m_p.Set(0, 0);
    dynamicBox.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 15.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = EntityCategory::PLAYER;
    fixtureDef.filter.maskBits = BUILDINGS | MOB;

    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Player::update(){
    // center += speed_dir * speed;
    box->SetLinearVelocity(b2Vec2(speed_dir.x * speed, speed_dir.y * speed));
}


void Player::display(){
    ofSetColor(0, 0, 255);

    b2Vec2 position = box->GetPosition();
    b2Vec2 screen_coord = world_ptr->transformeBoxToScreenCoorditane(position);
    // ofDrawCircle(screen_coord.x, screen_coord.y, radius * World::WORLD_RESOLUTION);
    b2Vec2 heading(ofGetAppPtr()->mouseX - screen_coord.x, ofGetAppPtr()->mouseY - screen_coord.y);

    if (state == PlayerState::MOVING){
        sprite.display(screen_coord, heading);
    } else if (state == PlayerState::STILL){
        sprite.set_frame_number(0);
        sprite.display_still(screen_coord, heading);
    }
}

void Player::change_speed_dir(const unsigned int key_pressed){
    speed_dir.set(0,0);

    static ofVec2f N_dir(0, -1), S_dir(0, 1), W_dir(-1, 0), E_dir(1, 0);

    if (key_pressed == 0){
        state = PlayerState::STILL;
    } else {
        state = PlayerState::MOVING;
    }

    if (key_pressed & W_KEY_PRESS) speed_dir += W_dir;  
    if (key_pressed & E_KEY_PRESS) speed_dir += E_dir;  
    if (key_pressed & N_KEY_PRESS) speed_dir += N_dir;
    if (key_pressed & S_KEY_PRESS) speed_dir += S_dir;

    // speed_dir = new_speed_dir;
}


void Player::take_damage(int damage){
    if (life > 0){
        life -= damage;
    }
}

void Player::collision_event(worldEntity *collision_entity){

    // Mob *m = dynamic_cast<Mob*>(collision_entity)
    // if (m != 0){

    // }
}

ofVec2f Player::get_center(){
    get_center_screen();
    return get_center_box();
}

void Player::hud_display(){

}