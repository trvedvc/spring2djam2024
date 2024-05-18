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

    dmg = 1;
    reload_time = 1;
    reload = reload_time;
    can_shoot = true;

    money = 0;

    seeds = 5;
    plant_CD = 0.5;
    remaining_plant_CD = 0;
    can_plant = true;
}

Player::~Player() {}

void Player::update(float &delta, SpinachVec &spinach_vec) {
    if ( remaining_plant_CD < 0 ) {
        can_plant = true;
    } else {
        remaining_plant_CD -= delta;
    }

    for ( Spinach * spinach : spinach_vec.spinaches ) {
        if ( CheckCollisionCircles(pos, 10, spinach->pos, 10) && spinach->state == 1) {
            spinach->picked = true;
        }
    }

    if ( reload < 0 ) {
        can_shoot = true;
    } else {
        reload -= delta;
    }
}

void Player::move(const float &delta) {
    dir = Vector2Normalize(dir);
    pos = Vector2Add(pos, Vector2Scale(dir,speed*delta));
}

void Player::draw() {
    DrawCircle(pos.x, pos.y, 10, WHITE);
}

void Player::plant(SpinachVec &spinach_vec,Vector2 plantpos) {
    if (can_plant && seeds > 0) {
        bool spaceforplant = true;
        for ( Spinach * spinach : spinach_vec.spinaches ) {
            if((spinach->pos.x == plantpos.x)&&(spinach->pos.y == plantpos.y))
                {spaceforplant=false;}
            }
            if(spaceforplant){
                spinach_vec.add(new Spinach(plantpos));
                can_plant = false;
                remaining_plant_CD = plant_CD;
                seeds -= 1;
            }
    }
}

void Player::shoot(BulletVec &bullet_vec, Vector2 &facing) {
    if ( can_shoot ) {
        bullet_vec.add(pos, facing);
        can_shoot = false;
        reload = reload_time;
    } 
}
