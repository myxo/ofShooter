#include "player.h"
#include "ofApp.h"
#include "world.h"
#include "movingEntity.h"
#include "boxContactListener.h"
#include "sprite.h"

#include "ofMain.h"

#include <stdio.h>
#include "Box2D/Box2D.h"

Player::Player(ofVec2f center, World *world_ptr){
    player_init(center, world_ptr);
}

Player::Player(LevelObject &lObject, World *world_ptr){
    ofVec2f center = world_ptr->camera->transformeScreenToBoxCoorditane(ofVec2f(lObject.x0, lObject.y0));
    player_init(center, world_ptr);
}

Player::~Player(){}

void Player::player_init(ofVec2f center, World *world_ptr){
    try{
        this->center    = center;
        this->radius    = world_ptr->game_parameters.getDouble("player_radius");
        this->life      = world_ptr->game_parameters.getDouble("player_life");
        this->world_ptr = world_ptr;
        this->state     = PlayerState::STILL;

        speed_dir.set(0, 0);
        speed = 10;
        MAX_LIFE = life;

        string sprite_path = string(world_ptr->game_parameters.getString("sprite_root_folder")) + 
            string(world_ptr->game_parameters.getString("player_sprite_filename"));
        sprite.parse_sprite_file(8, 1, 32, 54, 1, 1, sprite_path.c_str(), 0.4);
    } catch (std::exception &e){
        cout << "ERROR in player constructor: " << e.what() << endl;
    }

    box_init();
}

void Player::box_init(){
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x, center.y);
    box = world_ptr->box2d_world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;

    dynamicBox.m_p.Set(0, 0);
    dynamicBox.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.filter.categoryBits = EntityCategory::PLAYER;
    fixtureDef.filter.maskBits = EntityCategory::BUILDINGS | EntityCategory::MOB;

    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Player::update(){
    box->SetLinearVelocity(b2Vec2(speed_dir.x * speed, speed_dir.y * speed));
}


void Player::display(){
    ofSetColor(0, 0, 255);

    ofVec2f screen_coord = get_center_screen();
    ofVec2f heading(ofGetAppPtr()->mouseX - screen_coord.x, ofGetAppPtr()->mouseY - screen_coord.y);

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
}


void Player::take_damage(int damage){
    if (life > 0){
        life -= damage;
    }
}

void Player::collision_event(worldEntity *collision_entity){
    // cout << "OOOOWOOOH\n";
    // Mob *m = dynamic_cast<Mob*>(collision_entity)
    // if (m != 0){

    // }
}



void Player::hud_display(){

}
