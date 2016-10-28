#pragma once

#include "ofMain.h"
#include "Box2D/Box2D.h"


using namespace std;


class Sprite{
public:
    Sprite();
    Sprite(int seed_);
    
    void display(ofVec2f position, ofVec2f heading, double scaleX = 1.0, double scaleY = 1.0);
    void display_still(ofVec2f position, ofVec2f heading, double scaleX = 1.0, double scaleY = 1.0);

    void parse_sprite_file(int col, int row, int sizeX, int sizeY, int offset, 
            int separation, const char* filename, double animationSpeed = 1.0);
    void set_single_image_sprite(const char* filename);

    void set_frame_number(int n);
    void set_frame_number_random();

    void change_seed();
    void change_seed(int seed);
private:
    vector<shared_ptr<ofImage>> frames;
    int frame_total, frame_number, seed = 0;
    double animationSpeed; 

};



class TileSet{
public:
    shared_ptr<ofImage> get_image_pointer(int tile_id);
    void read_from_file(const char* filename, int tilewidth, int tileheight, int tilecount, int columns, int gap, int offset);

    void draw_tileset(int x, int y);
private:
    vector<ofImage> tiles;
    int tileWidth, tileHeight;
};