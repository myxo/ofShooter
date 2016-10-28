#include "building.h"
#include "worldEntity.h"
#include "world.h"

#include <fstream>

Building::Building(World *world_ptr_) : worldEntity(){
    world_ptr = world_ptr_;
}

Building::~Building(){}


void Building::box_init(){
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(0, 0); // maybe left up corner?
    box = world_ptr->box2d_world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    b2Vec2 vertices[8];
    for (size_t i = 0; i < vertex.size(); i++){
        vertices[i].Set(vertex[i].x, vertex[i].y); 
    }
    shape.Set(vertices, vertex.size());
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.filter.categoryBits = EntityCategory::BUILDINGS;
    // collide with
    fixtureDef.filter.maskBits = EntityCategory::PLAYER | EntityCategory::MOB | EntityCategory::BULLET;

    box->CreateFixture(&fixtureDef);
    box->SetUserData(this);
}


// deprecated
void Building::building_from_file(const char* filename){
    ifstream f(filename);

    if (!f.is_open()){
        std::cout << "ERROR: build_from_file, file < " << filename << " > cannot be open\n";
    }
    string line;

    while(getline(f, line)){
        std::istringstream iss(line);
        double v1, v2;
        if (! (iss >> v1 >> v2)){ break; }

        vertex.push_back(ofVec2f(v1, v2));
    }

    box_init();
}


// TODO make polygon (not rect)
void Building::build_from_level_object(const LevelObject &object){
    ofVec2f v[4] = { ofVec2f(object.x0, object.y0)
                , ofVec2f(object.x0, object.y0 + object.height)
                , ofVec2f(object.x0 + object.width, object.y0 + object.height)
                , ofVec2f(object.x0 + + object.width, object.y0)};
    // counterclockwise order
    vertex.push_back(world_ptr->camera->transformeScreenToBoxCoorditane(v[3]));
    vertex.push_back(world_ptr->camera->transformeScreenToBoxCoorditane(v[2]));
    vertex.push_back(world_ptr->camera->transformeScreenToBoxCoorditane(v[1]));
    vertex.push_back(world_ptr->camera->transformeScreenToBoxCoorditane(v[0]));

    box_init();
}

ofVec2f Building::get_vertex_screen_coord(int i){
    ofVec2f res = get_center_box() + vertex[i];
    return world_ptr->camera->transformeBoxToScreenCoorditane(res);
}

void Building::display(){
    // ofSetColor(0, 0, 0);
    // ofVec2f v0 = get_vertex_screen_coord(0);
    // for (size_t i = 2; i < vertex.size(); i++){
    //     ofVec2f v1 = get_vertex_screen_coord(i-1);
    //     ofVec2f v2 = get_vertex_screen_coord(i);
    //     ofDrawTriangle(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y);
    // }
}

void Building::collision_event(worldEntity *collision_entity){}