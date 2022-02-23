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


/// Includes <Game>
#include "../include/structures.h"
#include "../include/prototypes.h"
#include "../include/globals.h"
#include "../include/includes.h"


/// Main
int main() {
    InitializeGameData();
    
    while(!WindowShouldClose()) {
        // Logic
        if(gamestate->state == STATE_MAP) {
            PlayerControls();
        }
        if(IsKeyPressed(KEY_ESCAPE)) {
            if(gui->pmFlags & (1 << 0)) gui->pmFlags &= ~(1 << 0);
            else                        gui->pmFlags |=  (1 << 0);
        }
        
        
        // Draw
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(player->camera);
        
        if(gamestate->state == STATE_MAP) {
            if(options->messageLogging) DrawGrid(100,1);
            
            DrawMap();
            
            
        }
        
        EndMode3D();
        
        DrawProvinceMenu();
        
        // Draw 2D
        DrawMainMenu();
        
        // Draw Pause Menu
        DrawPauseMenu();
        
        // Options menu
        DrawOptionsMenu();
        
        
        
        // Draw Debug
        if(options->messageLogging) {
            DrawFPS(0,0);
            char buffer[20] = {0};
            sprintf(buffer, "%2.f,%2.f,%2.f\n %2.f\n",
                    player->camera.target.x,
                    player->camera.target.y,
                    player->camera.target.z,
                    player->camera.fovy);
            DrawText(buffer, 0, 20, 20, BLACK);
        }
        
        EndDrawing();
    }
    
    QuitGame();
    
    return 0;
}