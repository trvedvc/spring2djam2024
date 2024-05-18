#include <iostream>
#include <raylib.h>
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/spinach.hpp"
#include "../include/bullet.hpp"
#include "../include/enemy.hpp"

using namespace std;

#define DAY 0
#define NIGHT 1

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "title");
    SetTargetFPS(60);

    float delta;

    Player player(Vector2{400,300});
    
    SpinachVec spinach_vec;

    EnemyVec enemy_vec;

    BulletVec bullets;


    Camera2D camera = {0};
    camera.target = (Vector2){ player.pos.x, player.pos.y};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int daytime = DAY;

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

// Bullet
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            bullets.add(player.pos,Vector2Normalize(Vector2{(float) GetMouseX()-screenWidth/2,(float) GetMouseY()-screenHeight/2}));
        }
       
        bullets.update(delta);

        if ( IsKeyPressed(KEY_N) ) {
            if (daytime == DAY) daytime = NIGHT;
            else {
                daytime = DAY;
                spinach_vec.grow();
            }
        }

        if (IsKeyPressed(KEY_E)) {
            if ( daytime == DAY ) player.plant(spinach_vec);
        }
        if (IsKeyPressed(KEY_Q)) {
            if ( daytime == DAY ) player.pickUp(spinach_vec);
        }
        if (IsKeyPressed(KEY_F)) {
            if ( daytime == NIGHT ) enemy_vec.add(new Enemy(player.pos));
        }


        player.update(delta, spinach_vec);
        enemy_vec.update(delta, spinach_vec);
        enemy_vec.move(delta);

        spinach_vec.update();

        
        camera.target = (Vector2){ player.pos.x, player.pos.y};

// draw
        BeginDrawing();
        if ( daytime == DAY) {
            ClearBackground(DARKGREEN);
        } else { ClearBackground(DARKBLUE);}

        BeginMode2D(camera);
            DrawRectangleLines(0,0,800,600,BLUE);
            player.draw();
            bullets.draw();
            spinach_vec.draw();
            enemy_vec.draw();
        EndMode2D();

        DrawText(TextFormat("Money: %i", player.money), 10, 10, 20, BLACK);
        DrawText(TextFormat("Seed: %i", player.seeds), 10, 30, 20, BLACK);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}