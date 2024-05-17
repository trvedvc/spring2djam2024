#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/spinach.hpp"

using namespace std;

// ----------------------------------------------- Spinach class
Spinach::Spinach(Vector2 xy) {
    pos = xy;
}

Spinach::~Spinach() {}

void Spinach::draw() {
    DrawCircle(pos.x, pos.y, 10, GREEN);
}


// ----------------------------------------------- SpinachVec class
SpinachVec::SpinachVec() {}
SpinachVec::~SpinachVec() {
    for ( Spinach * spinach : spinach_vec ) {
        delete spinach;
    }
}

void SpinachVec::add(Spinach * spinach) {
    spinach_vec.push_back(spinach);
}

void SpinachVec::draw() {
    for ( Spinach * spinach : spinach_vec ) {
        spinach->draw();
    }
}