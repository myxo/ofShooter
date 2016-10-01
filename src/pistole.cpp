#include "pistole.h"
#include "world.h"


Pistole::Pistole(ofVec2f center, ofVec2f speed_dir, World *world_ptr) : movingEntity(){
    this->world_ptr = world_ptr;
    this->speed_dir = speed_dir;
    state = BulletState::EXIST;

    damage = 50;

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
    fixtureDef.density = 0.05f;
    fixtureDef.friction = 0.1f;

    fixtureDef.filter.categoryBits = EntityCategory::BULLET;
    fixtureDef.filter.maskBits = BUILDINGS | MOB;
    box->CreateFixture(&fixtureDef);

    box->SetUserData(this);
}

void Pistole::update(){
    box->SetLinearVelocity(b2Vec2(speed_dir.x, speed_dir.y));
}


void Pistole::display(){
    if (state == BulletState::EXIST){
        ofSetColor(50, 50, 200);
        b2Vec2 position = box->GetPosition();
        b2Vec2 screen_coord = World::transformeBoxToScreenCoorditane(position);
        ofDrawCircle(screen_coord.x, screen_coord.y, radius * World::WORLD_RESOLUTION);
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
    }
}