#include <cmath>
#include <iostream>
#define M_PI 3.14159265358979323846

#include "raylib.h"
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/gun.hpp"

using namespace std;

Gun::Gun(Vector2 mid_point_passed,Texture2D gun_txt_passed,Texture2D gun_txt_diag_pass)
{
    texture_size={636,628};

    mid_point=mid_point_passed;
    radius=318;
    gun_txt=gun_txt_passed;
    gun_txt_diag=gun_txt_diag_pass;

    texture_centre = Vector2Subtract(mid_point,Vector2Scale(texture_size,0.5));
}

Gun::~Gun()
{
}
void Gun::update(Vector2 mouse_vec){
    pos= Vector2Scale(Vector2Normalize(Vector2Subtract(mid_point,mouse_vec)),-radius);
    last_point= Vector2Add(pos,mid_point);
    angle=Vector2Angle(pos,{-1,0});
    
}
void Gun::draw(){
    //DrawCircleV(last_point,20,RED);
    if(abs(angle)<M_PI/8){
        DrawTextureRec(gun_txt,{0,280,236,80},{texture_centre.x,texture_centre.y+280},WHITE);
    }
    else if((angle>3*M_PI/8)&&(angle<5*M_PI/8)){
        DrawTextureRec(gun_txt,{280,410,55,216},{texture_centre.x+280,texture_centre.y+410},WHITE);
    }
    else if(abs(angle)>7*M_PI/8){
        DrawTextureRec(gun_txt,{400,280,236,80},{texture_centre.x+400,texture_centre.y+280},WHITE); 
    }
    else if((angle<-3*M_PI/8)&&(angle>-5*M_PI/8)){
        DrawTextureRec(gun_txt,{280,0,55,216},{texture_centre.x+280,texture_centre.y},WHITE);   
    }
    else if((angle<-5*M_PI/8)&&(angle>-7*M_PI/8)){
        DrawTextureRec(gun_txt,{367,30,219,220},{texture_centre.x+367,texture_centre.y+30},WHITE);  
    }
    else if((angle>5*M_PI/8)&&(angle<7*M_PI/8)){
        DrawTextureRec(gun_txt,{380,370,220,210},{texture_centre.x+380,texture_centre.y+370},WHITE);  
    }
    else if((angle>M_PI/8)&&(angle<3*M_PI/8)){
        DrawTextureRec(gun_txt,{40,380,220,210},{texture_centre.x+40,texture_centre.y+380},WHITE);  
    }
    else if((angle<-M_PI/8)&&(angle>-3*M_PI/8)){
        DrawTextureRec(gun_txt,{50,30,220,210},{texture_centre.x+50,texture_centre.y+30},WHITE);  
    }


    
}
