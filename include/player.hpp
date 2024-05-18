#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"

#include "spinach.hpp"

using namespace std;

class Player {
    public:
        Vector2 pos;
        float speed;
        Vector2 dir;

        int money;

        int seeds;
        float plant_CD;
        float remaining_plant_CD;
        bool can_plant;

        Player(Vector2 xy);
        ~Player();

        void update(float &delta, SpinachVec & spinach_vec);
        void move(const float &delta);
        void draw();
        void plant(SpinachVec &spinachVec);
        
};

#endif