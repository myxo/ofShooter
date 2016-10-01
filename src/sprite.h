#pragma once

#include "ofMain.h"
#include "Box2D/Box2D.h"


using namespace std;


class Sprite{
public:
    Sprite();
    
    void display(b2Vec2 position, b2Vec2 heading, double scaleX = 1.0, double scaleY = 1.0);
    void display_still(b2Vec2 position, b2Vec2 heading, double scaleX = 1.0, double scaleY = 1.0);

    void parse_sprite_file(int col, int row, int sizeX, int sizeY, int offset, 
            int separation, const char* filename, double animationSpeed = 1.0);
    void set_single_image_sprite(const char* filename);

    void set_frame_number(int n);
private:
    vector<unique_ptr<ofImage>> frames;
    int frame_total, frame_number;
    double animationSpeed; 

};