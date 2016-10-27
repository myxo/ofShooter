#include <stdlib.h>
#include <iostream>
#include <stdexcept>

#include "level.h"

#include "tinyxml2.h"

using namespace std;

int LevelObject::get_property_int(string name){
    return stoi(properties[name]);
}

double  LevelObject::get_property_double(string name){
    return stod(properties[name]);
}

string  LevelObject::get_property_string(string name){
    return properties[name];
}




Level::Level() {}

// TODO throw exeption if there are no such object???
LevelObject Level::get_object(string name){
    for (auto object : object_array){
        if (object.name == name){
            return object;
        }
    }
    return LevelObject();
}


vector<LevelObject> Level::get_objects(string name){
    // TODO check if there are some function for this
    vector<LevelObject> array;
    for (auto object : object_array){
        if (object.name == name){
            array.push_back(object);
        }
    }
    return array;
}


// TODO mae propper transition from texture to screen coord
void Level::display(int x, int y){
    ofSetColor(255, 255, 255);
    static_background.draw(x, y);
}


// TODO check if I could allocate frame buffer logically inly once
void Level::make_static_background_texture(){
    static_background.allocate(width*tile_width, height*tile_height, GL_RGBA);
    static_background.begin();

    ofSetColor(255, 255, 255);
    for (auto layer: layer_array){
        int k = 0;
        for (int j = 0; j < height; j++){
            for (int i = 0; i < width; i++){
                layer.tiles[k++]->draw(i*tile_width, j*tile_height);
            }
        }
    }

    static_background.end();
}

// TODO make propper error handler + make universal (check tmx spec)
// + check for vector copy
void Level::load_from_file(const char* filename){
    using namespace tinyxml2;

    XMLDocument xmlDoc;
    auto errId = xmlDoc.LoadFile(filename);
    if (errId != 0){
        throw std::invalid_argument("Cannot open level tmx file");
    }

    XMLElement * pMap = xmlDoc.FirstChildElement("map");
    if (pMap == nullptr) {
        throw string("No map section. XML level file is broken");
    }
    
    pMap->QueryIntAttribute("width", &width);
    pMap->QueryIntAttribute("height", &height);
    pMap->QueryIntAttribute("tilewidth", &tile_width);
    pMap->QueryIntAttribute("tileheight", &tile_height);


    // parse tileset TODO check for multiple tileset + check gap and offset + firstgid
    XMLElement *tileset_ptr = pMap->FirstChildElement("tileset");
    int tileWidth, tileHeight, tileCount, columns;
    tileset_ptr->QueryIntAttribute("tilewidth", &tileWidth);
    tileset_ptr->QueryIntAttribute("tileheight", &tileHeight);
    tileset_ptr->QueryIntAttribute("tilecount", &tileCount);
    tileset_ptr->QueryIntAttribute("columns", &columns);

    int spacing = 0, margin = 0;
    if (tileset_ptr->Attribute("spacing") != NULL) {
        tileset_ptr->QueryIntAttribute("spacing", &spacing);
    }
    if (tileset_ptr->Attribute("margin") != NULL) {
        tileset_ptr->QueryIntAttribute("margin", &margin);
    }

    XMLElement *image_ptr = tileset_ptr->FirstChildElement("image");
    string image_filename = image_ptr->Attribute("source");
    string image_root = string("../../data/");
    // TODO add multiple tileset (should be easy)
    // may throw exception
    tileset.read_from_file((image_root + image_filename).c_str(), tileWidth, tileHeight, tileCount, columns, spacing, margin);




    // parse layers
    XMLElement *layer_ptr = pMap->FirstChildElement("layer");
    if (layer_ptr == nullptr){
        throw string("No layer section. XML level file is broken.");
    }

    while(layer_ptr != nullptr){
        Layer l;
        XMLElement *data_ptr = layer_ptr->FirstChildElement("data");
        if (data_ptr == nullptr){
            throw string("No data section with Layer section. XML level file is broken.");
        }
        XMLElement *tile_ptr = data_ptr->FirstChildElement("tile");
        if (tile_ptr == nullptr){
            throw string("No tile section with Layer section. XML level file is broken.");
        }
        while(tile_ptr != nullptr){
            int gid;
            tile_ptr->QueryIntAttribute("gid", &gid);
            l.tiles.push_back(tileset.get_image_pointer(gid-1));

            tile_ptr = tile_ptr->NextSiblingElement("tile");
        }
        layer_array.push_back(l);
        layer_ptr = layer_ptr->NextSiblingElement("layer");
    }


    // parse objects
    XMLElement *object_group_ptr = pMap->FirstChildElement("objectgroup");
    // if (object_group_ptr == nullptr){
    //     cout << "ERROR object_group_ptr == null";
    // }
    while (object_group_ptr != nullptr){
        XMLElement *object_ptr = object_group_ptr->FirstChildElement("object");
        if (object_ptr == nullptr){
            throw string("No Object section with ObjectGroup section. XML level file is broken.");
        }

        while (object_ptr != nullptr){
            LevelObject obj;
            // string name;
            if (object_ptr->Attribute("name") != NULL){
                obj.name = object_ptr->Attribute("name");
            }

            if (object_ptr->Attribute("type") != NULL){
                obj.type = object_ptr->Attribute("type");
            }
            obj.x0 = stod(object_ptr->Attribute("x"));
            obj.y0 = stod(object_ptr->Attribute("y"));
            obj.width = stod(object_ptr->Attribute("width"));
            obj.height = stod(object_ptr->Attribute("height"));

            object_array.push_back(obj);
            object_ptr = object_ptr->NextSiblingElement("object");
        }

        object_group_ptr = object_group_ptr->NextSiblingElement("objectgroup");
    }
}