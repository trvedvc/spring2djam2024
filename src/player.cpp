#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/bullet.hpp"

using namespace std;

Player::Player(Vector2 xy) {
    pos = xy;
    speed = 250;
    dir = Vector2{0,0};

    plant_CD = 0.5;
    remaining_plant_CD = 0;
    can_plant = true;
}

Player::~Player() {}

void Player::update(float &delta) {
    if ( remaining_plant_CD < 0 ) {
        can_plant = true;
    } else {
        remaining_plant_CD -= delta;
    }
}

void Player::move(const float &delta) {
    dir = Vector2Normalize(dir);
    pos = Vector2Add(pos, Vector2Scale(dir,speed*delta));
}

void Player::draw() {
    DrawCircle(pos.x, pos.y, 10, WHITE);
}

void Player::plant(SpinachVec &spinach_vec) {
    if (can_plant) {
        spinach_vec.add(new Spinach(pos));
        can_plant = false;
        remaining_plant_CD = plant_CD;
    }
}
