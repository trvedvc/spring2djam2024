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
    DrawCircleV(pos, 10,Fade(YELLOW,0.64));
    DrawCircleLinesV(pos, 10,BLACK);
}

bool Bullet::update(float &delta, vector<Enemy*> &enemies){
    
    for ( auto it = enemies.begin(); it != enemies.end(); it++) {
        if ( CheckCollisionCircles(pos, 10, (*it)->pos, 50) ){
            (*it)->health -= 1;
            (*it)->is_dying = true;
            return false;
        }
    }
    pos = Vector2Add(pos,Vector2Scale(dir,speed*delta));
    time += delta;
    return true;
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

void BulletVec::update(float &delta, vector<Enemy*> &enemies){
    
    /*for ( Bullet * bullet : bullets ) {
        bullet->update(delta, enemies);
    }*/
    for ( auto it = bullets.begin(); it != bullets.end(); ) {
        if ( !(*it)->update(delta, enemies) ) {
            delete (*it);
            bullets.erase(it);
        } else {it++;}
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