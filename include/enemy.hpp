#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "raylib.h"

#include "spinach.hpp"

using namespace std;

class Enemy {
    public:
        Vector2 pos;
        float speed;
        Vector2 dir;

        Spinach * target;

        Enemy(Vector2 xy);
        ~Enemy();

        void update(float &delta, SpinachVec & spinach_vec);
        void move(const float &delta);
        void draw();
};

class EnemyVec {
    public:
        vector<Enemy*> enemies;
        

        EnemyVec();
        ~EnemyVec();
        
        void add(Enemy * enemy);
        void update(float &delta, SpinachVec & spinach_vec);
        void move(float &delta);
        void draw();
        //void collision_check(SpinachVec & spinach_vec);
};

#endif