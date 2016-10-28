#include "mob.h"
#include "world.h"
#include "boxContactListener.h"
#include "sprite.h"
#include "utils.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

#include <iostream>

Mob::Mob(ofVec2f center, World *world_ptr){
    mob_init(center, world_ptr);
}

Mob::Mob(LevelObject &lObject, World *world_ptr){
    ofVec2f center = world_ptr->camera->transformeScreenToBoxCoorditane(ofVec2f(lObject.x0, lObject.y0));
    mob_init(center, world_ptr);
}

Mob::~Mob(){}


void Mob::mob_init(ofVec2f center, World *world_ptr){
    try{
        this->center    = center;
        this->radius    = world_ptr->game_parameters.getDouble("mob_radius");
        // this->speed     = world_ptr->game_parameters.getDouble("mob_speed");
        this->max_speed = world_ptr->game_parameters.getDouble("mob_speed");
        this->life      = world_ptr->game_parameters.getInt("mob_life");
        this->damage    = world_ptr->game_parameters.getInt("mob_damage");
        this->resting_time = world_ptr->game_parameters.getInt("mob_rest_time_ms");
        this->attack_radius = world_ptr->game_parameters.getDouble("mob_attack_radius");

        MAX_LIFE = life;

        this->world_ptr = world_ptr;

        speed = world_ptr->game_parameters.getDouble("mob_speed");
        state = MobState::MAY_ATTACK;

        string sprite_path = string(world_ptr->game_parameters.getString("sprite_root_folder")) + 
            string(world_ptr->game_parameters.getString("mob_sprite_filename"));
        string sprite_dead_path = string(world_ptr->game_parameters.getString("sprite_root_folder")) + 
            string(world_ptr->game_parameters.getString("mob_dead_sprite_filename"));
        sprite.parse_sprite_file(8, 1, 48, 48, 1, 1, sprite_path.c_str(), 0.2);
        dead_sprite.set_single_image_sprite(sprite_dead_path.c_str());
        sprite.set_frame_number_random();
    } catch (std::exception &e){
        cout << "ERROR in mob constructor: " << e.what() << endl;
    }

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
    fixtureDef.filter.categoryBits = EntityCategory::MOB;
    // collide with
    fixtureDef.filter.maskBits = EntityCategory::BUILDINGS | EntityCategory::MOB 
            | EntityCategory::BULLET | EntityCategory::PLAYER ;
    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Mob::update_state(){
    if (state == MobState::DEAD)
        return;
    
    ofVec2f p1 = world_ptr->player->get_center_box();
    ofVec2f p2 = get_center_box();
    speed_dir.set(p1.x - p2.x, p1.y - p2.y);
    speed_dir.limit(max_speed);

    if (get_time_shift_ms(attack_time) > resting_time){
        state = MobState::MAY_ATTACK;
    }

    if (p2.distance(p1) - world_ptr->player->radius < attack_radius){
        make_damage();
    }
}

void Mob::update(){
    if (state == MobState::DEAD)
        box->SetLinearVelocity(b2Vec2(0, 0));
    else
        box->SetLinearVelocity(b2Vec2(speed_dir.x, speed_dir.y));

}

void Mob::display(){
    ofVec2f screen_coord = get_center_screen();

    if (state == MobState::DEAD){
        dead_sprite.display(screen_coord, ofVec2f(0,1));
        return;
    }

    if (state == MobState::MAY_ATTACK)
        ofSetColor(255, 0, 0);
    else if (state == MobState::ATTACKING)
        ofSetColor(255, 255, 0);

    sprite.display(screen_coord, speed_dir);
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

    if (state != MobState::MAY_ATTACK){
        return;
    }

    attack_time = chrono::steady_clock::now();
    world_ptr->player->take_damage(damage);
    // state = MobState::ATTACKING; // TODO make attacking animation
    state = MobState::REST;
}

void Mob::collision_event(worldEntity *collision_entity){
    // Player *pl = dynamic_cast<Player*>(collision_entity);
    // if (pl != nullptr){
    //     make_damage();
    // }   
}