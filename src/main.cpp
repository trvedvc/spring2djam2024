#include <iostream>
#include <raylib.h>

#include "../include/player.hpp"
#include "../include/spinach.hpp"

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "title");
    SetTargetFPS(60);

    float delta;

    Player player(Vector2{400,300});
    
    SpinachVec spinachVec;

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

        if (IsKeyDown(KEY_E)) player.plant(spinachVec);

        player.update(delta);

        camera.target = (Vector2){ player.pos.x, player.pos.y};

// draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
            player.draw();
            spinachVec.draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}