#include <iostream>
#include <raylib.h>
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/spinach.hpp"
#include "../include/bullet.hpp"

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "title");
    SetTargetFPS(60);

    float delta;

    Player player(Vector2{400,300});
    
    SpinachVec spinachVec;

    BulletVec bullets;


    Camera2D camera = {0};
    camera.target = (Vector2){ player.pos.x, player.pos.y};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (WindowShouldClose() == false){
        delta = GetFrameTime();
// logic
//Player movement
        player.dir = Vector2{0,0};
        if (IsKeyDown(KEY_W)) player.dir.y = -1;
        if (IsKeyDown(KEY_A)) player.dir.x = -1;
        if (IsKeyDown(KEY_S)) player.dir.y = 1;
        if (IsKeyDown(KEY_D)) player.dir.x = 1;
        
        player.move(delta);
//Planting
        if (IsKeyDown(KEY_E)) player.plant(spinachVec);

        player.update(delta);
// Bullet
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            bullets.add(player.pos,Vector2Normalize(Vector2{(float) GetMouseX()-screenWidth/2,(float) GetMouseY()-screenHeight/2}));
            cout<<GetMouseX()<<' '<<GetMouseY()<<' '<< player.pos.x <<' '<<player.pos.y<<endl;
        }
       
        bullets.update(delta);

        
        camera.target = (Vector2){ player.pos.x, player.pos.y};

// draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
            player.draw();
            spinachVec.draw();
            bullets.draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}