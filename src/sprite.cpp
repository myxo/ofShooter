#include "sprite.h"

using namespace std;

Sprite::Sprite(){}


// Warning. If call this method second time it may be mess. think what should I do in this case. 
void Sprite::parse_sprite_file(int col, int row, int sizeX, int sizeY, int offset, int separation,
                const char* filename, double animationSpeed){
    this->animationSpeed = animationSpeed;
    this->frame_total = col * row; // TODO what if it not fill to the rect?
    this->frame_number = 0; // TODO make random (c++ 11 way)

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
    frames.push_back(make_unique<ofImage>());
    frames[0]->load(filename);

    frame_total     = 1;
    frame_number    = 0;
    animationSpeed  = 1.0;
}
    
void Sprite::display(b2Vec2 position, b2Vec2 heading, double scaleX, double scaleY){
    display_still(position, heading, scaleX, scaleY);

    frame_number++;
    if (frame_number >= frame_total / animationSpeed)
        frame_number = 0;

}

void Sprite::display_still(b2Vec2 position, b2Vec2 heading, double scaleX, double scaleY){
    ofPushMatrix();
    ofTranslate(position.x, position.y);

    ofVec2f v1(1,0);
    ofVec2f v2(heading.x,heading.y); // TODO go to ofVec2f in all situation
    double angle = v1.angle(v2) - 90;
    
    ofRotate(angle);

    int index = (int) (frame_number * animationSpeed) % frame_total;
    int sizeX = frames[index]->getWidth(), sizeY = frames[index]->getHeight();
    frames[index]->draw(-sizeX/2, -sizeY/2, sizeX*scaleX, sizeY*scaleY); // TODO think how scale better be used

    ofPopMatrix();
}

void Sprite::set_frame_number(int n){
    frame_number = n;
}