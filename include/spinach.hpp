#ifndef SPINACH_HPP
#define SPINACH_HPP

#include <vector>

#include "raylib.h"

using namespace std;

class Spinach {
    public:
        Vector2 pos;
        float health;

        void draw();

        Spinach(Vector2 xy);
        ~Spinach();
};

class SpinachVec {
    public:
        vector<Spinach *> spinaches;
        
        SpinachVec();
        ~SpinachVec();

        void add(Spinach * spinach);
        void draw();
        void update();
};

#endif