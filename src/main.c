///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Includes <System>
#define RAYGUI_IMPLEMENTATION

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>
#include <raygui.h>
#include <raymath.h>

#include "../include/generic_defines.h"



/// Includes <Game>
#include "../include/map.h"
#include "../include/gamestate.h"

#include "map/map_generation.c"
#include "gui/mainmenu_gui.c"


/// Main
int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1080, 720, "Anbray");
    SetTargetFPS(60);
    
    Gamestate *gamestate = (Gamestate*)calloc(1, sizeof(Gamestate));
    
    gamestate->debug = true;
    
    /*
    gamestate->camera.position = (Vector3){0.0f,-5.0f,-5.0f};
    gamestate->camera.up       = (Vector3){0.0f,-1.0f,0.0f};
    gamestate->camera.fovy     = 50.0f;
*/
    
    gamestate->camera.position = (Vector3){0.0f,5.0f,5.0f};
    gamestate->camera.up       = (Vector3){0.0f,1.0f,0.0f};
    gamestate->camera.fovy     = 50.0f;
    
    
    
    while(!WindowShouldClose()) {
        if(IsKeyDown(KEY_W)) {
            gamestate->camera.target.z   += 0.2f;
            gamestate->camera.position.z += 0.2f;
        }
        if(IsKeyDown(KEY_S)) {
            gamestate->camera.target.z   -= 0.2f;
            gamestate->camera.position.z -= 0.2f;
        }
        if(IsKeyDown(KEY_A)) {
            gamestate->camera.target.x   -= 0.2f;
            gamestate->camera.position.x -= 0.2f;
        }
        if(IsKeyDown(KEY_D)) {
            gamestate->camera.target.x   += 0.2f;
            gamestate->camera.position.x += 0.2f;
        }
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(gamestate->camera);
        
        if(gamestate->state == STATE_MAP) DrawGrid(100, 1);
        
        
        // TODI: they don't show up?
        for(int i = 0; i < gamestate->map.numChunks; i++) {
            DrawModel(gamestate->map.chunks[i].model,
                      gamestate->map.chunks[i].location,
                      1.0f, WHITE);
        }
        
        
        EndMode3D();
        
        
        // Draw 2D
        DrawMainMenu(gamestate);
        
        // TODO: crashes game
        DrawTexture(gamestate->map.chunks[0].texture,0,0,WHITE);
        
        
        // Draw Debug
        DrawFPS(0,0);
        char buffer[20] = {0};
        sprintf(buffer, "%2.f,%2.f,%2.f",
                gamestate-> camera.target.x,
                gamestate->camera.target.y,
                gamestate->camera.target.z);
        DrawText(buffer, 0, 20, 20, BLACK);
        
        EndDrawing();
    }
    
    return 0;
}