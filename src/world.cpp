#include "world.h"
#include "player.h"
#include "pistole.h"
#include "boxContactListener.h"
#include "bulletFactory.h"
#include "utils.h"
#include "building.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

#include <iostream>
#include <string>
#include <algorithm>


World::World(){
    b2Vec2 gravity(0.0f, 0.0f);
    box2d_world = std::make_shared<b2World>(gravity);
    CL = new ContactListener();
    box2d_world->SetContactListener(CL);
    
    game_parametrs = parse_config_file("../data/game_parametrs");

    player          = std::make_shared<Player>(ofVec2f(0, 0), this);
    bullet_factory  = std::make_shared<BulletFactory>(this);
    
    building_array.push_back(std::make_shared<Building>(this));
    building_array[0]->building_from_file("../data/building");

    for (int i = 0; i < MOB_MAX; i++){
        mob_array.push_back(std::make_shared<Mob>(ofVec2f(std::rand()%30-15, std::rand()%30-15), this));
    }

    tile.load("../../data/bg.png");


    // w = new Wall(ofVec2f(-10, 0), ofVec2f(10, 0), this);
}

World::~World(){
    delete CL;
    bullet_array.clear();
}

void World::update(){
    // box2d_world.update();
    box2d_world->ClearForces();

    player->update();

    for (auto mob: mob_array){
        mob->update_state();
    }

    for (auto mob: mob_array){
        mob->update();
    }

    for (auto bullet: bullet_array){
        bullet->update();
    }

    box2d_world->Step(1/60., 10, 10);
    
    bullet_cleanup();
}

void World::gun_fire(ofVec2f mouse_screen){
    // if (player->ready_to_fire()){
    //     bullet_factory->create_bullets(mouse_screen);
    // }
    bullet_factory->fire(mouse_screen);
}

void World::bullet_cleanup(){
    for (auto i = bullet_array.begin(); i != bullet_array.end(); ){
        if ((*i)->state == BulletState::NOT_EXIST){
            i = bullet_array.erase(i);
        } else{
            ++i;
        }
    }
}

void World::display(){
    update_window_boundary();
    display_tile_background(tile);

    // ofPushMatrix();
    // ofTranslate(window_start_x, window_start_y);

    // for (auto mob: mob_array){
    //     mob->display();
    // }

    // draw dead mob first
    for_each(mob_array.begin(), mob_array.end(), [](auto &mob){ if (mob->state == MobState::DEAD) mob->display(); });
    for_each(mob_array.begin(), mob_array.end(), [](auto &mob){ if (mob->state != MobState::DEAD) mob->display(); });

    for (auto bullet: bullet_array){
        bullet->display();
    }


    for (auto building: building_array){
        building->display();
    }

    player->display();

    // ofPopMatrix();
}



b2Vec2 World::transformeBoxToScreenCoorditane(b2Vec2 coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = coord.x * WORLD_RESOLUTION + w/2 - window_start_x;
    coord.y = coord.y * WORLD_RESOLUTION + h/2 - window_start_y;
    return coord;
}


b2Vec2 World::transformeScreenToBoxCoorditane(b2Vec2 coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = (coord.x - w/2 + window_start_x) / WORLD_RESOLUTION;
    coord.y = (coord.y - h/2 + window_start_y) / WORLD_RESOLUTION;
    return coord;
}


ofVec2f World::transformeBoxToScreenCoorditane(ofVec2f coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = coord.x * WORLD_RESOLUTION + w/2 - window_start_x;
    coord.y = coord.y * WORLD_RESOLUTION + h/2 - window_start_y;
    return coord;
}


ofVec2f World::transformeScreenToBoxCoorditane(ofVec2f coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = (coord.x - w/2 + window_start_x) / WORLD_RESOLUTION;
    coord.y = (coord.y - h/2 + window_start_y) / WORLD_RESOLUTION;
    return coord;
}


ofVec2f World::box2of(b2Vec2 a){
    return ofVec2f(a.x, a.y);
}
b2Vec2 World::of2box(ofVec2f a){
    return b2Vec2(a.x, a.y);
}

// Change window_start if player go to corner of the window
void World::update_window_boundary(){
    auto p_center = player->get_center_screen();
    // int pixel_offset = player->speed;// * WORLD_RESOLUTION;

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

void World::display_tile_background(ofImage tile){
    int h = tile.getHeight(), w = tile.getWidth();
    ofSetColor(255,255,255);
    for (int i = -1; i < ofGetWidth() / w + 2; i++){
        for (int j = -1; j < ofGetHeight() / h + 2; j++){
            tile.draw(i*w - (window_start_x % w), j*h - (window_start_y % h));
        }
    }
}

// void World::generate_tile_background(const char* filename){
//     ofImage tile;
//     tile.load(filename);
//     int h = tile.GetHeight(), w = tile.GetWidth();
//     background_image.allocate(ofGetWidth() + w, ofGetHeight() + h, OF_IMAGE_COLOR); // TODO. make accurate allocation

//     for (int i = 0; i < background_image.getPixels().size(); i++){
//         background_image.getPixels()[i] = 
//     }

//     img.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT); img.width = 320;
// }

double World::get_param_double(string key){
    return stod(game_parametrs[key]);
}
