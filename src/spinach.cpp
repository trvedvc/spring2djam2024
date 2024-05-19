#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/spinach.hpp"

using namespace std;

#define GROWING 0
#define GROWN 1
#define SIZE 64

vector<Color> colors = {LIME, GREEN};

// ----------------------------------------------- Spinach class
Spinach::Spinach(Vector2 xy) {
    pos = xy;
    rec = {pos.x,pos.y,SIZE,SIZE};
    health = 1;
    state = GROWING;
    picked = false;
}

Spinach::~Spinach() {}

void Spinach::draw() {
    DrawRectangleRec(rec,colors[state]);
}

void Spinach::grow() {
    if (state == GROWING) state = GROWN;
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