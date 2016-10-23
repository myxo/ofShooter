#include <stdlib.h>
#include <iostream>

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
void Level::display(){
    ofSetColor(255, 255, 255);
    static_background.draw(0, 0);
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
        cout << "ERROR in load_from_file\n";
    }

    // XMLElement * pMap = xmlDoc.FirstChildElement("map");
    XMLElement * pMap = xmlDoc.FirstChildElement("map");
    if (pMap == nullptr) cout << "ERROR pMap = nullptr\n";
    // XMLElement *
    
    pMap->QueryIntAttribute("width", &width);
    pMap->QueryIntAttribute("height", &height);
    pMap->QueryIntAttribute("tilewidth", &tile_width);
    pMap->QueryIntAttribute("tileheight", &tile_height);


    // parse tileset TODO check for multiple tileset + check gap and offset
    XMLElement *tileset_ptr = pMap->FirstChildElement("tileset");
    int tileWidth, tileHeight, tileCount, columns;
    tileset_ptr->QueryIntAttribute("tilewidth", &tileWidth);
    tileset_ptr->QueryIntAttribute("tileheight", &tileHeight);
    tileset_ptr->QueryIntAttribute("tilecount", &tileCount);
    tileset_ptr->QueryIntAttribute("columns", &columns);

    XMLElement *image_ptr = tileset_ptr->FirstChildElement("image");
    string image_filename = image_ptr->Attribute("source");
    string image_root = string("../../data/");
    tileset.read_from_file((image_root + image_filename).c_str(), tileWidth, tileHeight, tileCount, columns);




    // parse layers
    XMLElement *layer = pMap->FirstChildElement("layer");
    if (layer == nullptr){
        cout << "ERROR in layer read\n";
    }

    while(layer != nullptr){
        Layer l;
        XMLElement *data_ptr = layer->FirstChildElement("data");
        if (data_ptr == nullptr){
            cout << "ERROR data_ptr == null";
        }
        XMLElement *tile_ptr = data_ptr->FirstChildElement("tile");
        if (tile_ptr == nullptr){
            cout << "ERROR tile_ptr == null";
        }
        while(tile_ptr != nullptr){
            int gid;
            tile_ptr->QueryIntAttribute("gid", &gid);
            l.tiles.push_back(tileset.get_image_pointer(gid-1));

            tile_ptr = tile_ptr->NextSiblingElement("tile");
        }
        layer_array.push_back(l);
        layer = layer->NextSiblingElement("layer");
    }


    // parse objects
    XMLElement *object_group = pMap->FirstChildElement("objectgroup");
    if (object_group == nullptr){
        cout << "ERROR object_group == null";
    }
    XMLElement *object = object_group->FirstChildElement("object");

    while (object != nullptr){
        LevelObject obj;
        // string name;
        obj.name = object->Attribute("name");

        if (object->Attribute("type") != NULL){
            obj.type = object->Attribute("type");
        }
        obj.x0 = stod(object->Attribute("x"));
        obj.y0 = stod(object->Attribute("y"));
        obj.width = stod(object->Attribute("width"));
        obj.height = stod(object->Attribute("height"));

        object_array.push_back(obj);
        object = object->NextSiblingElement("object");
    }


    //debug print

    // cout << width << " " << height << " " << tile_width << " " << tile_height << "\n";
    // for  (auto l : layer_array){
    //     cout << "layer:\n";
    //     for (int tile: l.tiles){
    //         cout << tile << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "-----------------\n";
    // for (auto obj: object_array){
    //     cout << "object " << obj.name << " " << obj.type << endl;
    //     cout << obj.x0 << " " << obj.y0 << " " << obj.width << " " << obj.height << endl;
    //     //cout << obj.properties << "\n\n";

    //     for (const auto &p: obj.properties){
    //         cout << "p[" << p.first << "] = " << p.second << endl;
    //     }
    //     cout << endl;
    // }
}