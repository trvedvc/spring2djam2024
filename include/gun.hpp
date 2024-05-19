#ifndef GUN_HPP
#define GUN_HPP

#include "raylib.h"

#include "player.hpp"
#include "bullet.hpp"
using namespace std;

class Gun
{
public:
    Gun(const Vector2 mid_point,Texture2D gun_txt,Texture2D gun_txt_diag_pass);
    ~Gun();

    Vector2 pos;
    Texture2D skin;
    Vector2 last_point;
    Vector2 mid_point;
    int radius;
    float angle;

    Texture2D gun_txt;
    Texture2D gun_txt_diag;
    Vector2 texture_size;
    Vector2 texture_centre;



    void update(Vector2 mouse_vec);
    void draw();

  

};


#endif