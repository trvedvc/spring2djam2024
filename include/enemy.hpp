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
        Rectangle frame_run_rec;
        int frame_speed;
        int current_run_frame;
        Vector2 shift_run_vector;

        Texture2D die;
        bool is_dying;
        Rectangle frame_die_rec;
        int current_die_frame;
        Vector2 shift_die_vector;
        bool is_dead;

        Texture2D eat;
        bool is_eating;
        Rectangle frame_eat_rec;
        int current_eat_frame;
        Vector2 shift_eat_vector;

        int facing;
        Color tint;

        Spinach * target;

        Enemy(Vector2 xy, Texture2D slug_run, Texture2D slug_die, Texture2D slug_eat);
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