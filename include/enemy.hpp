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

        int health;

        int frame_counter;
        Texture2D run;
        Rectangle frame_rec;
        int frame_speed;
        int current_frame;
        Vector2 shift_vector;
        int facing;
        Color tint;

        Spinach * target;

        Enemy(Vector2 xy, Texture2D slug_run);
        ~Enemy();

        bool update(SpinachVec & spinach_vec);
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
};

#endif