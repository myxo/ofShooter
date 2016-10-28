#include "sprite.h"

using namespace std;

Sprite::Sprite(){}

// Warning. TODO. If call this method second time it may be mess. think what should I do in this case. 
void Sprite::parse_sprite_file(int col, int row, int sizeX, int sizeY, int offset, int separation,
                const char* filename, double animationSpeed){
    this->animationSpeed = animationSpeed;
    this->frame_total = col * row; // TODO what if it not fill the rect?
    this->frame_number = 0;

    ofImage source;
    source.load(filename);

    int k = 0;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            frames.push_back(make_unique<ofImage>());
            frames[k++]->cropFrom(source, j*(sizeX+separation) + offset, i*(sizeY+separation) + offset, 
                sizeX - offset, sizeY - offset);
        }
    }
}

void Sprite::set_single_image_sprite(const char* filename){
    frames.push_back(make_shared<ofImage>());
    frames[0]->load(filename);

    frame_total     = 1;
    frame_number    = 0;
    animationSpeed  = 1.0;
}
    
void Sprite::display(ofVec2f position, ofVec2f heading, double scaleX, double scaleY){
    display_still(position, heading, scaleX, scaleY);

    frame_number++;
    if (frame_number >= (int)(frame_total / animationSpeed)){
        frame_number = 0;
    }

}

void Sprite::display_still(ofVec2f position, ofVec2f heading, double scaleX, double scaleY){
    ofPushMatrix();
    ofTranslate(position.x, position.y);

    ofVec2f e(1,0);
    double angle = e.angle(heading) - 90;
    
    ofRotate(angle);

    int index = (int) (frame_number * animationSpeed + seed) % frame_total;
    int sizeX = frames.at(index)->getWidth(), sizeY = frames[index]->getHeight();
    ofSetColor(255, 255, 255);
    frames[index]->draw(-sizeX/2, -sizeY/2, sizeX*scaleX, sizeY*scaleY);

    ofPopMatrix();
}

void Sprite::set_frame_number(int n){
    frame_number = n;
}

void Sprite::set_frame_number_random(){
    frame_number = std::rand() % frame_total;
}


// void Sprite::change_seed(){
//     seed = std::rand() % frame_total;
// }
// void Sprite::change_seed(int seed_){
//     seed = seed_;
// }



shared_ptr<ofImage> TileSet::get_image_pointer(int tile_id){
    return make_shared<ofImage>((tiles.at(tile_id)));
}

// offset - x and y offset from begining
void TileSet::read_from_file(const char* filename, int tilewidth, int tileheight, int tilecount, int columns, int gap, int offset){
    ofImage source;
    source.load(filename);
    tileWidth = tilewidth;
    tileHeight = tileheight;

    for (int i = 0; i < tilecount; i++){
        tiles.push_back(ofImage());
        int x = (i % columns) * (tilewidth + gap) + offset;
        int y = (i / columns) * (tileheight + gap) + offset;
        tiles[i].cropFrom(source, x, y, tilewidth, tileheight);
    }
}


// For debug purpose only!
void TileSet::draw_tileset(int x, int y){
    for (size_t i = 0; i < tiles.size(); i++){
        tiles[i].draw((tileWidth + 2) * i + x, y);
    }
}