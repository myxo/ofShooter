#include "world.h"
#include "player.h"
#include "pistole.h"
#include "boxContactListener.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

#include "iostream"


World::World(){
    b2Vec2 gravity(0.0f, 0.0f);
    // bool doSleep = true;
    box2d_world = std::make_shared<b2World>(gravity);
    // box2d_world.setGravity(0,0);
    CL = new ContactListener();
    box2d_world->SetContactListener(CL);

    player = std::make_shared<Player>(ofVec2f(0, 0), 0.8, 30, this);

    for (int i = 0; i < MOB_MAX; i++){
        mob_array.push_back(std::make_shared<Mob>(ofVec2f(std::rand()%20-10, std::rand()%20-10), 0.7, 20, this));
    }

    tile.load("/home/myxo/ssyp/of/shooter/data/bg.png");

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

// TODO make proper bullet factory
void World::gun_fire(ofVec2f mouse_screen){
    ofVec2f mouse_box = box2of(transformeScreenToBoxCoorditane(b2Vec2(mouse_screen.x, mouse_screen.y)));
    ofVec2f player_center = player->get_center_box();
    ofVec2f speed_dir(mouse_box.x - player_center.x, mouse_box.y - player_center.y);
    speed_dir.normalize();
    player_center += (speed_dir * 0.5);
    speed_dir *= 35.0; // TODO remove magic numbers

    bullet_array.push_back(std::make_shared<Pistole>(player_center, speed_dir, this));
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

    for (auto mob: mob_array){
        mob->display();
    }

    for (auto bullet: bullet_array){
        bullet->display();
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