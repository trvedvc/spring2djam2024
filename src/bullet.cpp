#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/bullet.hpp"

using namespace std;

//Bullet Logic 
Bullet::Bullet(Vector2 xy,Vector2 facing){
    pos = xy;
    speed = 500;
    dir = facing;
}

void Bullet::draw(){
    DrawCircle(pos.x, pos.y, 10, BLUE);
}


void Bullet::update(float &delta){
    pos = Vector2Add(pos,Vector2Scale(dir,speed*delta));
    time +=delta;
}


void Bullet::redefine(Vector2 xy,Vector2 facing){
    pos = xy;
    dir = Vector2Normalize(facing);
    time=0;
}


BulletVec::BulletVec() {}
BulletVec::~BulletVec() {
    for ( Bullet * bullet : bullets ) {
        delete bullet;
    }
}
void BulletVec::add(Vector2 xy,Vector2 facing){
    
    bullets.push_back(new Bullet(xy,facing));
}

void BulletVec::update(float &delta){
    
    for ( Bullet * bullet : bullets ) {
        bullet->update(delta);
    }
    if(!bullets.empty()){
        if((bullets[0]->time)>1.5){
            bullets.erase(bullets.begin());
        }
    }
}

void BulletVec::draw() {
    for ( Bullet * bullet : bullets ) {
        bullet->draw();
    }
}