#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"

#include "spinach.hpp"
#include "bullet.hpp"
#include "gun.hpp"

using namespace std;

class Player {
    public:
        Vector2 pos;
        float speed;
        Vector2 dir;
        

        int dmg;
        float reload_time;
        float reload;
        bool can_shoot;

        int frame_counter;
        Texture2D idle;
        Texture2D running;
        Rectangle frame_rec_idle;
        Rectangle frame_rec_running;
        int frame_speed;
        int current_frame_idle;
        int current_frame_running;
        Vector2 shift_vector;

        int money;

        int seeds;
        float plant_CD;
        float remaining_plant_CD;
        bool can_plant;

        Player(Vector2 xy,Texture2D idlePassed,Texture2D runningPassed);
        ~Player();

        void update(float &delta, SpinachVec & spinach_vec);
        void move(const float &delta);
        void draw();
        void plant(SpinachVec &spinachVec,Vector2 plantpos);
        void shoot(BulletVec &bullet_vec, Vector2 &facing,Gun gun);
        void changeDir();
};

#endif