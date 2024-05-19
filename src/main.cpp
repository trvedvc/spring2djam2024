#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include <stdio.h>
#include <math.h>

#include "../include/player.hpp"
#include "../include/spinach.hpp"
#include "../include/bullet.hpp"
#include "../include/enemy.hpp"
#include "../include/adfunctions.hpp"
#include "../include/gun.hpp"



using namespace std;

#define DAY 0
#define NIGHT 1


int main () {
       

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const Vector2 mid_point = {screenWidth/2,screenHeight/2};

    InitAudioDevice();    

    InitWindow(screenWidth, screenHeight, "title");
    //LOAD TEXTURES
    Texture2D settxt= LoadTexture("assets/settings.png");
    Texture2D popeye_idle = LoadTexture("assets/Player/PlayerIdleexport.png");
    Texture2D popeye_running = LoadTexture("assets/Player/PlayerRunningexport.png");
    Texture2D gun_txt = LoadTexture("assets/Player/WWIIRifleexport.png");
    Texture2D gun_txt_diag = LoadTexture("assets/Player/WWIIriflediag.png");

    Texture2D spinach_texture = LoadTexture("assets/Spinach/spinach.png");
    Texture2D grass = LoadTexture("assets/Grass.png");
    Texture2D cabin = LoadTexture("assets/Cabin.png");

    Texture2D slug_die = LoadTexture("assets/slugdie.png");
    Texture2D slug_eat = LoadTexture("assets/slugeat.png");

    Texture2D slug_run = LoadTexture("assets/slugrun.png");
    
    //LOAD sounds
    Sound bg_music = LoadSound("sounds/Popeye Soundtrack.wav");
    Sound shot_nr = LoadSound("sounds/MosinNagantShootFXwithoutbolt.wav");
    
    Sound smoke_s = LoadSound("sounds/PopeyePipe.wav");
    Sound walk_s = LoadSound("sounds/PopeyeWalking.wav");

    Texture2D pepek = LoadTexture("assets/pepek.png");
    Texture2D credits = LoadTexture("assets/credits");

    SetTargetFPS(60);

    float delta;
    int day = 1;
    bool game_over = false;
    bool show_credits = false;

    Player player(Vector2{400,300},popeye_idle,popeye_running,shot_nr);
    
    SpinachVec spinach_vec;

    EnemyVec enemy_vec;

    BulletVec bullet_vec;

    Gun mosin(mid_point,gun_txt,gun_txt_diag);

    Camera2D camera = {0};
    camera.target = (Vector2){ player.pos.x, player.pos.y};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int daytime = DAY;
    vector<Color> day_tint = {WHITE, DARKBLUE};
    // Initial Menu

    Vector2 facing;

    Rectangle playbutton = {screenWidth/4,3*screenHeight/4,screenWidth/2,screenHeight/8};
    int playgame = 0;
    //PlaySound(bg_music);



    while (WindowShouldClose() == false){
        
        if(playgame==0){   
            //while(! didClick(playbutton)){
            while(! IsKeyPressed(KEY_F)){

                BeginDrawing();
                    ClearBackground(DARKGREEN);
                    DrawTexture(pepek, 0,0, WHITE);
                    DrawText("Press F to play", 600, 800, 100, WHITE);

                    //DrawRectangleRounded(playbutton,0.5,4,BLACK);
                    //DrawTexture(settxt,150,150,WHITE); 
                EndDrawing();
            
                WaitTime(0.1);
               
            }
            playgame=1;
        }
        
// Bullet
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            facing = Vector2Normalize(Vector2Subtract(GetMousePosition(),Vector2{screenWidth/2,screenHeight/2}));
            player.shoot(bullet_vec, facing,mosin);
            
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

            if (Vector2Length(player.dir)>0 && (!IsSoundPlaying(walk_s))){
                PauseSound(smoke_s);
                PlaySound(walk_s);
            }
            else if(!IsSoundPlaying(smoke_s)&&Vector2Length(player.dir)==0){
                PlaySound(smoke_s);
            }

    //Planting

        if (IsKeyPressed(KEY_E)) {
            if ( daytime == DAY ) player.plant(spinach_vec,nearTile(player.pos,32), spinach_texture);
        }

        if (IsKeyPressed(KEY_F)) {
            if (game_over) {
                show_credits = true;
            }
        }

        if ( IsKeyPressed(KEY_R) ) {
            if (daytime == DAY) {
                daytime = NIGHT;
                for ( int i = 0; i < day*5*0.3; i++) {
                    enemy_vec.add(new Enemy(randomCoordinates(),slug_run, slug_die, slug_eat));
                }
            }
            mosin.tint =day_tint[daytime];
            player.tint = day_tint[daytime];
            for ( Spinach * spinach : spinach_vec.spinaches) {
                spinach->tint = day_tint[daytime];
            }
        }

        if (daytime == NIGHT) {
            if (enemy_vec.enemies.empty()) {
                spinach_vec.grow();
                daytime = DAY;
                day++;
            } 
            player.tint = day_tint[daytime];
            mosin.tint =day_tint[daytime];
            for ( Spinach * spinach : spinach_vec.spinaches) {
                spinach->tint = day_tint[daytime];
            }
        }

        player.update(delta, spinach_vec);

        enemy_vec.update(delta, spinach_vec);
        enemy_vec.move(delta);

        mosin.update(GetMousePosition());
       
        spinach_vec.update();

        
        camera.target = (Vector2){ player.pos.x, player.pos.y};

// draw
        BeginDrawing();
        if ( daytime == DAY) {
            ClearBackground(DARKGREEN);
        } else { ClearBackground(DARKBLUE);}

        BeginMode2D(camera);
            for (int i = -1; i < 1; i++) {
                for (int j = -1; j < 1; j++) {
                    DrawTexture(grass, i*1920, j*1080, day_tint[daytime]);
                }
            }
            //DrawTexture(trees, 0, 0, day_tint[daytime]);
            DrawTexture(cabin, 0, 0, day_tint[daytime]);

            //DrawRectangleLines(0,0,800,600,BLUE);
            player.draw();
            bullet_vec.draw();
            spinach_vec.draw();
            enemy_vec.draw();
        EndMode2D();
        
        mosin.draw();

        //DrawText(TextFormat("Money: %i", player.money), 10, 10, 20, BLACK);
        DrawText(TextFormat("Seeds: %i", player.seeds), 1650, 150, 50, WHITE);
        DrawText(TextFormat("Day %i", day), 1700, 100, 50, WHITE);
        DrawText(TextFormat("Score %i", player.score), 1650, 920, 50, WHITE);

        DrawText("WASD to move!", 100, 960, 20, WHITE);
        DrawText("ESC to quit! :C", 100, 1000, 20, WHITE);
        if (daytime == DAY) {
            DrawText("Press R when ready!", 100, 100, 50, WHITE);
            DrawText("Press E to plant!", 100, 920, 20, WHITE);

            if (day == 1) {
                DrawText("Press E to plant!", 100, 200, 50, WHITE);
            }
            if (day == 2) {
                DrawText("Spinach is ready to harvest after 2 days!", 100, 200, 40, WHITE);
            }
            if (day == 3) {
                DrawText("On spinach harvest, you get 1 or 2 seeds!", 100, 200, 40, WHITE);
            }
        }else{
            DrawText("Left Click to shoot!", 100, 920, 20, WHITE);
            DrawText("Protect your spinach from slugs!", 100, 100, 50, WHITE);

        }

        if ( player.seeds == 0 && spinach_vec.spinaches.empty()) {
            game_over = true;
            DrawText("GAME OVER", 500, 300, 100, WHITE);
            DrawText(TextFormat("SCORE: %i", player.score), 500, 650, 90, WHITE);
            DrawText("Press F to continue", 600, 800, 100, WHITE);
        }

        if (show_credits) {
            DrawTexture(credits, 0, 0, WHITE);
        }

        EndDrawing();

    }

    UnloadTexture(settxt);
    UnloadTexture(popeye_idle);
    UnloadTexture(popeye_running);
    UnloadTexture(gun_txt);
    UnloadTexture(gun_txt_diag);
    UnloadTexture(spinach_texture);
    UnloadTexture(grass);
    UnloadTexture(cabin);
    UnloadTexture(slug_run);
    UnloadTexture(slug_die);
    UnloadTexture(slug_eat);
    UnloadTexture(pepek);
    UnloadTexture(credits);
    CloseWindow();
    return 0;
}
