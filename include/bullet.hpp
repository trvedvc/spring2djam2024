#ifndef BULLET_HPP
#define BULLET_HPP

#include "raylib.h"

#include "player.hpp"
#include "enemy.hpp"

using namespace std;

class Bullet {
    public:
        Vector2 pos;
        float speed;
        Vector2 dir;
        float time;

        Bullet(Vector2 xy,Vector2 facing);

        bool update(float &delta, vector<Enemy*> &enemies);
        void draw();
        void redefine(Vector2 xy,Vector2 facing);
};

class BulletVec {
    public:
        vector<Bullet *> bullets;
        
        BulletVec();
        ~BulletVec();

        void update(float &delta, vector<Enemy*> &enemies);
        void add(Vector2 xy,Vector2 facing);
        void draw();
};  


#endif