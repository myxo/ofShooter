#include <exception>

#include "pistole.h"
#include "world.h"

#include "ofMain.h"



Pistole::Pistole(ofVec2f center, ofVec2f speed_dir, World *world_ptr) : movingEntity(){
    this->world_ptr = world_ptr;
    this->speed_dir = speed_dir;
    state = BulletState::EXIST;
    try{
        radius = world_ptr->game_parameters.getDouble("pistole_bullet_radius");
        damage = world_ptr->game_parameters.getDouble("pistole_bullet_damage");
    } catch (std::exception& e){
        cout << "Error in pistole constructor: " << e.what() << endl;
    }

    init_box(center);

    box->SetLinearVelocity(b2Vec2(speed_dir.x, speed_dir.y));
}

Pistole::~Pistole(){
    box->GetWorld()->DestroyBody( box );
}

void Pistole::init_box(ofVec2f center){
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x, center.y);
    bodyDef.bullet = true;
    box = world_ptr->box2d_world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;

    dynamicBox.m_p.Set(0, 0);
    dynamicBox.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.filter.categoryBits = EntityCategory::BULLET;
    fixtureDef.filter.maskBits = EntityCategory::BUILDINGS | EntityCategory::MOB;
    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Pistole::update(){
    box->SetLinearVelocity(b2Vec2(speed_dir.x, speed_dir.y));
    auto pos = get_center_screen();
    if(pos.x > 2 * ofGetWidth() || pos.y > 2 * ofGetHeight()     // TODO this is just some euristic 
        || pos.x < -ofGetWidth() || pos.y < -ofGetHeight()){     // think how it would be better 
        state = BulletState::NOT_EXIST;
    }
}


void Pistole::display(){
    if (state == BulletState::EXIST){
        ofSetColor(50, 50, 200);
        b2Vec2 position = box->GetPosition();
        b2Vec2 screen_coord = world_ptr->camera->transformeBoxToScreenCoorditane(position); // TODO add sprite???
        // draw in double size (overwise its hard to see them)
        ofDrawCircle(screen_coord.x, screen_coord.y, 2*radius * 16); // TODO add sprite!! and no magic number 
    }
}


void Pistole::make_damage(Mob *mob){
    mob->take_damage(damage);
    state = BulletState::NOT_EXIST;
}

void Pistole::collision_event(worldEntity *collision_entity){
    Mob *mob = dynamic_cast<Mob*>(collision_entity);

    if (mob != 0){
        make_damage(mob);
        return;
    }

    Building *building = dynamic_cast<Building*>(collision_entity);
    if (building != 0){
        state = BulletState::NOT_EXIST;
    }
}