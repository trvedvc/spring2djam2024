#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>

using namespace std;

 bool didClick (Rectangle rec){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if((GetMouseX()>=rec.x)&&(GetMouseX()<=(rec.x+rec.width))){
                if ((GetMouseY()>=rec.y)&&(GetMouseY()<=(rec.y+rec.height)))
                {
                    return true;
                }
                
            }
        }
        return false;
}
Vector2 nearTile(Vector2 original, int size){
    Vector2 retvec = original;
    int remx = fmod((original.x),(float)size);
    int remy = fmod((original.y),(float)size);
    if (remx>size/2){retvec.x += size-remx;}
    else{retvec.x -= remx;}
    if (remy>size/2){retvec.y += size-remy;}
    else{retvec.y -= remy;}
    retvec.x=round(retvec.x);
    retvec.y=round(retvec.y);
    return retvec;
}

Vector2 randomCoordinates(){
    Vector2 vec;
    int r = 1920;
    float alpha = rand() % 361;
    vec.x = r*cos(alpha*PI/180);
    vec.y = r*sin(alpha*PI/180);
    cout << alpha << ' ' << vec.x << ' '<< vec.y<< endl;
    return vec;
}