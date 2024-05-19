#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/enemy.hpp"

using namespace std;

Enemy::Enemy(Vector2 xy, Texture2D slug_run, Texture2D slug_die, Texture2D slug_eat) {
    pos = xy;
    speed = 60;
    dir = Vector2{0,0};
    health = 2;

    frame_counter=0;

    run= slug_run;
    current_run_frame=0;
    frame_run_rec = {0,0,(float)run.width/4,(float)run.height};
    frame_speed = 6;
    shift_run_vector = Vector2{frame_run_rec.width/2,frame_run_rec.height/2};

    die = slug_die;
    is_dying = false;
    current_die_frame=0;
    frame_die_rec = {0,0,(float)die.width/8,(float)die.height};
    shift_die_vector = Vector2{frame_die_rec.width/2,frame_die_rec.height/2};
    is_dead = false;

    eat = slug_eat;
    is_eating = false;
    current_eat_frame=0;
    frame_eat_rec = {0,0,(float)eat.width/11,(float)eat.height};
    shift_eat_vector = Vector2{frame_eat_rec.width/2,frame_eat_rec.height/2};

    tint = DARKBLUE;
}

Enemy::~Enemy() {}

bool Enemy::update(SpinachVec &spinachVec) {
    if (is_dead) return false;
     
    if (!spinachVec.spinaches.empty()) {
        auto it = spinachVec.spinaches.begin();
        target = (*it);
        dir = Vector2Subtract((*it)->pos, pos);
        it++;
        for ( ; it != spinachVec.spinaches.end(); it++) {
            if ( Vector2Length(Vector2Subtract((*it)->pos, pos)) < Vector2Length(dir) ) {
                dir = Vector2Subtract((*it)->pos, pos);
                target = (*it);
            }
        }

        if (CheckCollisionCircles(pos, 1, target->pos, 1)) {
            target->health -= 1;
            is_eating = true;
        }
    } else {
        dir = Vector2{0,0};
    }
    return true;
}

void Enemy::move(const float &delta) {
    if (!is_eating && !is_dying) {
        dir = Vector2Normalize(dir);
        pos = Vector2Add(pos, Vector2Scale(dir,speed*delta));
    }
}

void Enemy::draw() {    
    frame_counter++; 
    
    if (is_dying) {
        if (frame_counter >= (60/frame_speed))
        {
            frame_counter = 0;
            current_die_frame++;
            if (current_die_frame > 11) {
                current_die_frame = 0;
                is_dead = true;
            }
            frame_die_rec.x = current_die_frame*frame_die_rec.width;
        }
        frame_die_rec.width = abs(frame_die_rec.width);
        frame_die_rec.width *= dir.x <= 0 ? 1 : -1;  
        DrawTextureRec(die,frame_die_rec,Vector2Subtract(pos,shift_die_vector),tint);
    }

    if (is_eating) {
        if (frame_counter >= (60/frame_speed))
        {
            frame_counter = 0;
            current_eat_frame++;
            if (current_eat_frame > 11) {
                current_eat_frame = 0;
                is_eating = false;
            }
            frame_eat_rec.x = current_eat_frame*frame_eat_rec.width;
        }
        frame_eat_rec.width = abs(frame_eat_rec.width);
        frame_eat_rec.width *= dir.x <= 0 ? 1 : -1;  
        DrawTextureRec(eat,frame_eat_rec,Vector2Subtract(pos,shift_eat_vector),tint);
    }

    //run
    if ( !is_dying && !is_eating) {
        if (frame_counter >= (60/frame_speed))
        {
            frame_counter = 0;
            current_run_frame++;
            if (current_run_frame > 3) current_run_frame = 0;
            frame_run_rec.x = current_run_frame*frame_run_rec.width;
        }
        frame_run_rec.width = abs(frame_run_rec.width);
        frame_run_rec.width *= dir.x <= 0 ? 1 : -1;  
        DrawTextureRec(run,frame_run_rec,Vector2Subtract(pos,shift_run_vector),tint);
    }
    //DrawCircle(pos.x, pos.y, 10, RED);
}

// ----------------------------------------------- EnemyVec class
EnemyVec::EnemyVec() {}
EnemyVec::~EnemyVec() {
    for ( Enemy * enemy : enemies ) {
        delete enemy;
    }
}

void EnemyVec::add(Enemy * enemy) {
    enemies.push_back(enemy);
}

void EnemyVec::update(float &delta, SpinachVec &spinach_vec) {
    /*for ( Enemy * enemy : enemies ) {
        enemy->update(delta, spinach_vec);
    }*/
    for ( auto it = enemies.begin(); it != enemies.end();) {
        if(!(*it)->update(spinach_vec)) {
            delete (*it);
            enemies.erase(it);
        } else {
            it++;
        }
    }
}

void EnemyVec::move(float &delta) {
    for ( Enemy * enemy : enemies ) {
        enemy->move(delta);
    }
}

void EnemyVec::draw() {
    for ( Enemy * enemy : enemies ) {
        enemy->draw();
    }
}
