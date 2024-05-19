#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/spinach.hpp"

using namespace std;

#define PLANTING 0
#define GROWING1 1
#define GROWING2 2
#define SIZE 32

vector<Color> colors = {LIME, GREEN};

// ----------------------------------------------- Spinach class
Spinach::Spinach(Vector2 xy, Texture2D spinach_texture) {
    pos = xy;
    rec = {pos.x,pos.y,SIZE,SIZE};
    health = 1;
    picked = false;

    texture = spinach_texture;
    phase = PLANTING;
    cur_frame = 0;
    frame_rec = {0,0,96,96};
    frame_counter = 0;
    frame_speed = 8;
    is_growing = true;
    tint = WHITE;

}

Spinach::~Spinach() {}

void Spinach::draw() {
    //DrawRectangleRec(rec,colors[state]);
    if (is_growing) {
        frame_counter++;
        if ( frame_counter >= 60/frame_speed) {            
            frame_rec.x = cur_frame*frame_rec.width;
            frame_rec.y = phase*frame_rec.height;

            frame_counter = 0;
            cur_frame++;
            if (cur_frame > 4) {
                is_growing = false;
                cur_frame = 0;
            }
        }
    }
    DrawTextureRec(texture, frame_rec, Vector2Subtract(pos,{48,48}), tint);
    //DrawTexture(texture,pos.x,pos.y,WHITE);
}

void Spinach::grow() {
    if ( phase < 2 ) {
        phase += 1;
        is_growing = true;
    }
}


// ----------------------------------------------- SpinachVec class
SpinachVec::SpinachVec() {}
SpinachVec::~SpinachVec() {
    for ( Spinach * spinach : spinaches ) {
        delete spinach;
    }
}

void SpinachVec::add(Spinach * spinach) {
    spinaches.push_back(spinach);
}

void SpinachVec::draw() {
    for ( Spinach * spinach : spinaches ) {
        spinach->draw();
    }
}

void SpinachVec::grow() {
    for ( Spinach * spinach : spinaches ) {
        spinach->grow();
    }
}

void SpinachVec::update() {
    for ( auto it = spinaches.begin(); it != spinaches.end(); ) {
        if ( (*it)->health <= 0 || (*it)->picked ) {
            delete *it;
            it = spinaches.erase(it);
        } else {it++;}
    }
}