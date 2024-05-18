#include <iostream>
#include <cmath>

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>


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