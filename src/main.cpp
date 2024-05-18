#include <iostream>
#include <raylib.h>

#include "../include/player.hpp"
#include "../include/spinach.hpp"
#include "../include/enemy.hpp"

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "title");
    SetTargetFPS(60);

    float delta;

    Player player(Vector2{400,300});
    
    SpinachVec spinach_vec;

    EnemyVec enemy_vec;

    Camera2D camera = {0};
    camera.target = (Vector2){ player.pos.x, player.pos.y};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (WindowShouldClose() == false){
        delta = GetFrameTime();
// logic
        player.dir = Vector2{0,0};
        if (IsKeyDown(KEY_W)) player.dir.y = -1;
        if (IsKeyDown(KEY_A)) player.dir.x = -1;
        if (IsKeyDown(KEY_S)) player.dir.y = 1;
        if (IsKeyDown(KEY_D)) player.dir.x = 1;
        player.move(delta);

        if (IsKeyDown(KEY_E)) player.plant(spinach_vec);
        if (IsKeyDown(KEY_F)) enemy_vec.add(new Enemy(player.pos));


        player.update(delta);
        enemy_vec.update(delta, spinach_vec);
        enemy_vec.move(delta);

        spinach_vec.update();

        camera.target = (Vector2){ player.pos.x, player.pos.y};

// draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
            DrawRectangleLines(0,0,800,600,BLUE);
            player.draw();
            spinach_vec.draw();
            enemy_vec.draw();
        EndMode2D();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}