#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/bullet.hpp"

using namespace std;

Player::Player(Vector2 xy,Texture2D idlePassed,Texture2D runningPassed) {
    pos = xy;
    speed = 250;
    dir = {0,0};

    dmg = 1;
    reload_time = 1;
    reload = reload_time;
    can_shoot = true;

    frame_counter=0;
    current_frame=0;
    idle=idlePassed;
    running=runningPassed;
    frame_rec = {0,0,164,160};
    frame_speed = 6;
    shift_vector = Vector2{frame_rec.width/2,frame_rec.height/2};
    tint = WHITE;

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
        if ( CheckCollisionCircles(pos, 50, spinach->pos, 50) && spinach->phase == 2) {
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
    frame_counter++;
     if (frame_counter >= (60/frame_speed))
        {
            frame_counter = 0;
            current_frame++;
            if (current_frame > 4) current_frame = 0;
            frame_rec.x = current_frame*frame_rec.width;
        }
    DrawTextureRec(idle,frame_rec,Vector2Subtract(pos,shift_vector),tint);
}

void Player::plant(SpinachVec &spinach_vec,Vector2 plantpos, Texture2D spinach_texture) {
    if (can_plant && seeds > 0) {
        bool spaceforplant = true;
        for ( Spinach * spinach : spinach_vec.spinaches ) {
            if((spinach->pos.x == plantpos.x)&&(spinach->pos.y == plantpos.y))
                {spaceforplant=false;}
            }
            if(spaceforplant){
                spinach_vec.add(new Spinach(plantpos, spinach_texture));
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
