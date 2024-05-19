#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/bullet.hpp"
#include "../include/gun.hpp"
#define M_PI 3.14159265358979323846

using namespace std;

Player::Player(Vector2 xy,Texture2D idlePassed,Texture2D runningPassed,Sound shot_s_pass) {
    pos = xy;
    speed = 250;
    dir = {0,0};

    dmg = 1;
    reload_time = 1;
    reload = reload_time;
    can_shoot = true;

    frame_counter=0;
    current_frame_idle=0;
    current_frame_running=0;
    idle=idlePassed;
    running=runningPassed;
    frame_rec_idle = {0,0,-164,160};
    frame_rec_running={0,0,132,160};
    frame_speed = 6;
    shift_vector = Vector2{frame_rec_idle.width/2,-frame_rec_idle.height/2};
    tint = WHITE;

    shot_s_nr=shot_s_pass;

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
    //cout << pos.x << ' ' << pos.y << endl;
    if (CheckCollisionPointRec(pos,{-1920, -1080, 2*1920, 2*1080})) {
        dir = Vector2Normalize(dir);
        pos = Vector2Add(pos, Vector2Scale(dir,speed*delta));
    } else {
        if (pos.x <= -1920) { pos.x = -1919;}
        if (pos.x >= 1920) { pos.x = 1919;}
        if (pos.y <= -1080) { pos.y = -1079;}
        if (pos.y >= 1080) { pos.y = 1079;}
    }
}
void Player::draw() {
    frame_counter++;
     if (frame_counter >= (60/frame_speed))
        {
            frame_counter = 0;
            current_frame_idle++;
            current_frame_running++;
            if (current_frame_idle > 4) {current_frame_idle = 0;}
            if (current_frame_running>5) {current_frame_running=0;}
            frame_rec_idle.x = current_frame_idle*frame_rec_idle.width;
            frame_rec_running.x = current_frame_idle*frame_rec_running.width;
        }
    if(abs(dir.x)>0||abs(dir.y)>0){
        if(dir.x>0&&dir.y==0){
            frame_rec_running.width=132;
        }
        else if(dir.y==0){
            frame_rec_running.width=-132;
        }

        DrawTextureRec(running,frame_rec_running,Vector2Add(pos,shift_vector),tint);
        }
    else{
        if(frame_rec_running.width>0){
            frame_rec_idle.width=164;
        }
        else{
            frame_rec_idle.width=-164;
        }
        DrawTextureRec(idle,frame_rec_idle,Vector2Add(pos,shift_vector),tint);
        }
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

void Player::shoot(BulletVec &bullet_vec, Vector2 &facing,Gun gun) {
    if ( can_shoot ) {
        Vector2 muzzle ={0,0};
        Vector2 shot_dir ={0,0};
        if(abs(gun.angle)<M_PI/8){ //left
            muzzle={pos.x-318,pos.y};
            shot_dir ={-1,0};
        }
        else if((gun.angle>3*M_PI/8)&&(gun.angle<5*M_PI/8)){//Down
            muzzle={pos.x,pos.y+313};
            shot_dir ={0,1};
        }
        else if(abs(gun.angle)>7*M_PI/8){ //right
            muzzle={pos.x+318,pos.y};
            shot_dir ={1,0};
        }
        else if((gun.angle<-3*M_PI/8)&&(gun.angle>-5*M_PI/8)){//Up
            muzzle={pos.x,pos.y-313};
            shot_dir ={0,-1};
        }
        else if((gun.angle<-5*M_PI/8)&&(gun.angle>-7*M_PI/8)){ //top right
            muzzle={pos.x+258,pos.y-283};
            shot_dir =Vector2Normalize({1,-1});
        }
        else if((gun.angle>5*M_PI/8)&&(gun.angle<7*M_PI/8)){ //bottom right
             muzzle={pos.x+258,pos.y+283};
             shot_dir =Vector2Normalize({1,1});
        }
        else if((gun.angle>M_PI/8)&&(gun.angle<3*M_PI/8)){ // bottom left
             muzzle={pos.x-258,pos.y+283};
             shot_dir =Vector2Normalize({-1,1});
        }
        else if((gun.angle<-M_PI/8)&&(gun.angle>-3*M_PI/8)){ //topleft
            muzzle={pos.x-258,pos.y-283}; 
            shot_dir =Vector2Normalize({-1,-1});
        }

        PlaySound(shot_s_nr);

        bullet_vec.add(muzzle,shot_dir);

        can_shoot = false;
        reload = reload_time;
    } 
}
