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
    try{
        b2Vec2 gravity(0.0f, 0.0f);
        box2d_world = std::make_shared<b2World>(gravity);
        CL = new ContactListener();
        box2d_world->SetContactListener(CL);
        
        game_parameters.parse_config_file("../data/game_parameters");

        bullet_factory  = std::make_shared<BulletFactory>(this);
        level           = std::make_shared<Level>();
        camera          = std::make_shared<Camera>(this);
        
        level->load_from_file("../data/level_0.tmx");
        level->make_static_background_texture();
        
        LevelObject p_object = level->get_object("player");
        player = std::make_shared<Player>(p_object, this);

        vector<LevelObject> b_object_vector = level->get_objects(string("building"));
        for (auto build_object: b_object_vector){
            building_array.push_back(std::make_shared<Building>(this));
            building_array.back()->build_from_level_object(build_object);
        }

        vector<LevelObject> m_object_vector = level->get_objects(string("enemy"));
        for (size_t i = 0; i < m_object_vector.size() && i < MOB_MAX; i++){
            LevelObject &l_object = m_object_vector[i];
            mob_array.push_back(std::make_shared<Mob>(l_object, this));
        }

    } catch (string e){
        cout << "ERROR in world constrctor: " << e << endl;
        exit(1);
    } catch(std::exception &e){
        cout << "ERROR in world constrctor: " << e.what() << endl;
        exit(1);
    }

    camera->set_camera_center(player.get());
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
    camera->update();
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

    // TODO fix it!!!
    level->display(-camera->window_start_x, -camera->window_start_y);
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


    // for (auto building: building_array){
    //     building->display();
    // }

    player->display();

    // ofPopMatrix();
}




ofVec2f World::box2of(b2Vec2 a){
    return ofVec2f(a.x, a.y);
}
b2Vec2 World::of2box(ofVec2f a){
    return b2Vec2(a.x, a.y);
}

// void World::display_tile_background(ofImage tile){
//     int h = tile.getHeight(), w = tile.getWidth();
//     ofSetColor(255,255,255);
//     for (int i = -1; i < ofGetWidth() / w + 2; i++){
//         for (int j = -1; j < ofGetHeight() / h + 2; j++){
//             tile.draw(i*w - (window_start_x % w), j*h - (window_start_y % h));
//         }
//     }
// }