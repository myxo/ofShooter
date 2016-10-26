#pragma once

#include "sprite.h"

#include <vector>
#include <map>

using namespace std;

class LevelObject{
public:
    int     get_property_int(string name);
    double  get_property_double(string name);
    string  get_property_string(string name);

    string name, type;
    double x0, y0, width, height;
    map<string, string> properties;

    shared_ptr<Sprite> sprite;
};

struct Layer{
    // void display();

    vector<shared_ptr<ofImage>> tiles;
    int opacity;
};


// TODO makor refactor (var names)
class Level{
public:
    Level();
    void load_from_file(const char* filename);
    LevelObject get_object(string name);
    vector<LevelObject> get_objects(string name);
    void make_static_background_texture();
    void display(int x, int y);

private:
    vector<LevelObject> object_array;
    vector<Layer>       layer_array;

    TileSet tileset;
    ofFbo static_background;

    int width, height, tile_width, tile_height;
};