#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"

#include "../include/enemy.hpp"

using namespace std;

Enemy::Enemy(Vector2 xy) {
    pos = xy;
    speed = 60;
    dir = Vector2{0,0};
    health = 2;
}

Enemy::~Enemy() {}

bool Enemy::update(SpinachVec &spinachVec) {
    if (health <= 0) return false;
     
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
        }
    } else {
        dir = Vector2{0,0};
    }
    return true;
}

void Enemy::move(const float &delta) {
    dir = Vector2Normalize(dir);
    pos = Vector2Add(pos, Vector2Scale(dir,speed*delta));
}

void Enemy::draw() {
    DrawCircle(pos.x, pos.y, 10, RED);
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
