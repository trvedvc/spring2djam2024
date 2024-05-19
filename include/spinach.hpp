#ifndef SPINACH_HPP
#define SPINACH_HPP

#include <vector>

#include "raylib.h"

using namespace std;

class Spinach {
    public:
        Vector2 pos;
        float health;
        Rectangle rec;
        bool picked;

        int phase;

        Texture2D texture;
        int cur_frame;
        Rectangle frame_rec;
        int frame_counter;
        int frame_speed;
        bool is_growing;
        Color tint;

        Spinach(Vector2 xy, Texture2D spinach_texture);
        ~Spinach();

        void draw();
        void grow();

};

class SpinachVec {
    public:
        vector<Spinach *> spinaches;
        Sound eat_s;
        SpinachVec(Sound eat);
        ~SpinachVec();

        void add(Spinach * spinach);
        void draw();
        void update();
        void grow();
};

#endif