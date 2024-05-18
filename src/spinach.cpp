#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/spinach.hpp"

using namespace std;

// ----------------------------------------------- Spinach class
Spinach::Spinach(Vector2 xy) {
    pos = xy;
    health = 1;
}

Spinach::~Spinach() {}

void Spinach::draw() {
    DrawCircle(pos.x, pos.y, 10, GREEN);
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

void SpinachVec::update() {
    for ( auto it = spinaches.begin(); it != spinaches.end(); ) {
        if ( (*it)->health <= 0 ) {
            delete *it;
            it = spinaches.erase(it);
        } else {it++;}
    }
}