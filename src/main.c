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

#include "player.c"
#include "map/map_generation.c"
#include "gui/mainmenu_gui.c"


/// Main
int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1080, 720, "Anbray");
    SetTargetFPS(60);
    
    Gamestate *gamestate = (Gamestate*)calloc(1, sizeof(Gamestate));
    
    InitializePlayer(gamestate);
    
    
    while(!WindowShouldClose()) {
        if(gamestate->state == STATE_MAP) {
            PlayerControls(gamestate);
        }
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(gamestate->camera);
        
        if(gamestate->state == STATE_MAP) {
            
            // TODO: Wrap map
            for(int i = 0; i < gamestate->map.numChunks; i++) {
                DrawModel(gamestate->map.chunks[i].model,
                          gamestate->map.chunks[i].location,
                          1.0f, WHITE);
            }
        }
        
        EndMode3D();
        
        
        // Draw 2D
        DrawMainMenu(gamestate);
        
        
        // Draw Debug
        DrawFPS(0,0);
        char buffer[20] = {0};
        sprintf(buffer, "%2.f,%2.f,%2.f\n %2.f",
                gamestate-> camera.target.x,
                gamestate->camera.target.y,
                gamestate->camera.target.z,
                gamestate->camera.fovy);
        DrawText(buffer, 0, 20, 20, BLACK);
        
        EndDrawing();
    }
    
    return 0;
}