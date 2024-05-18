#include <iostream>
#include <raylib.h>
#include "raymath.h"

#include "../include/player.hpp"
#include "../include/spinach.hpp"
#include "../include/bullet.hpp"
#include "../include/enemy.hpp"
#include "../include/adfunctions.hpp"


using namespace std;

#define DAY 0
#define NIGHT 1

int main () {
       

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "title");
    //LOAD TEXTURES
    Texture2D settxt= LoadTexture("assets/settings.png");
    Texture2D popeye_idle = LoadTexture("assets/Player/PlayerIdleexport.png");
    Texture2D popeye_running = LoadTexture("assets/Player/PlayerRunningexport.png");
    SetTargetFPS(60);

     

    float delta;

    Player player(Vector2{400,300},popeye_idle,popeye_running);
    
    SpinachVec spinach_vec;

    EnemyVec enemy_vec;

    BulletVec bullet_vec;

    Camera2D camera = {0};
    camera.target = (Vector2){ player.pos.x, player.pos.y};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int daytime = DAY;
    // Initial Menu

    Rectangle playbutton = {screenWidth/4,3*screenHeight/4,screenWidth/2,screenHeight/8};
    int playgame = 0;





    while (WindowShouldClose() == false){
        
        if(playgame==0){   
            while(! didClick(playbutton)){

                BeginDrawing();
                    ClearBackground(BLUE);
                    DrawRectangleRounded(playbutton,0.5,4,BLACK);
                    DrawTexture(settxt,150,150,WHITE); 
                EndDrawing();
            
                WaitTime(0.1);
                cout<<GetMouseX()<<' '<<GetMouseY()<<' '<<playbutton.x<<' '<<playbutton.y<<endl;
            }
            playgame=1;
        }
        

// Bullet
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 facing = Vector2Normalize(Vector2Subtract(GetMousePosition(),Vector2{screenWidth/2,screenHeight/2}));
            player.shoot(bullet_vec, facing);
        }
       
        bullet_vec.update(delta, enemy_vec.enemies);
    
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

        if (IsKeyPressed(KEY_E)) {
            if ( daytime == DAY ) player.plant(spinach_vec,nearTile(player.pos,32));
        }
        if (IsKeyPressed(KEY_F)) {
            if ( daytime == NIGHT ) enemy_vec.add(new Enemy(player.pos));
        }
        if ( IsKeyPressed(KEY_N) ) {
            if (daytime == DAY) daytime = NIGHT;
            else {
                daytime = DAY;
                spinach_vec.grow();
            }
        }

        player.update(delta, spinach_vec);
        enemy_vec.update(delta, spinach_vec);
        enemy_vec.move(delta);

        spinach_vec.update();
        
        BeginMode2D(camera);
            DrawRectangleLines(0,0,1920,1080,BLUE);
            player.draw();
            bullet_vec.draw();
            spinach_vec.draw();
            enemy_vec.draw();
        EndMode2D();

        DrawText(TextFormat("Money: %i", player.money), 10, 10, 20, BLACK);
        DrawText(TextFormat("Seed: %i", player.seeds), 10, 30, 20, BLACK);


            player.update(delta, spinach_vec);
            enemy_vec.update(delta, spinach_vec);
            enemy_vec.move(delta);

            spinach_vec.update();

            
            camera.target = (Vector2){ player.pos.x, player.pos.y};

    // draw
            BeginDrawing();
            if ( daytime == DAY) {
                ClearBackground(YELLOW);
            } else { ClearBackground(DARKBLUE);}

            BeginMode2D(camera);
                DrawRectangleLines(0,0,800,600,BLUE);
                player.draw();
                bullet_vec.draw();
                spinach_vec.draw();
                enemy_vec.draw();
            EndMode2D();

            DrawText(TextFormat("Money: %i", player.money), 10, 10, 20, BLACK);
            DrawText(TextFormat("Seed: %i", player.seeds), 10, 30, 20, BLACK);


            EndDrawing();
            }
    
    

    UnloadTexture(settxt);
    UnloadTexture(popeye_idle);
    UnloadTexture(popeye_running);
    CloseWindow();
    return 0;
}
