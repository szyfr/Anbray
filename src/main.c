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
//#include "../include/globals.h"
#include "../include/includes.h"


/// Main
int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1280, 720, "Anbray");
    SetTargetFPS(60);
    SetExitKey(KEY_END);
    
    Gamestate *gamestate = (Gamestate*)calloc(1, sizeof(Gamestate));
    
    InitOptions(gamestate);
    DB_InitializeErrorlog(gamestate);
    
    InitializePlayer(gamestate);
    LoadLocalization(gamestate, 0);
    
    
    //*
    // TESTING
    PopulationList *list = CreatePopulationList();
    
    PopulationMember *mem = CreatePopulationMember();
    mem->population = 1000;
    mem->race       = 0;
    mem->culture    = 0;
    mem->religion   = 0;
    AddToPopulationList(list, mem);
    
    mem = CreatePopulationMember();
    mem->population = 200;
    mem->race       = 0;
    mem->culture    = 0;
    mem->religion   = 0;
    AddToPopulationList(list, mem);
    
    mem = CreatePopulationMember();
    mem->population = 1200;
    mem->race       = 0;
    mem->culture    = 1;
    mem->religion   = 0;
    AddToPopulationList(list, mem);
    
    ReadPopulationMembers(gamestate, list);
    
    DeletePopulationList(list);
    list = 0;
    ReadPopulationMembers(gamestate, list);
    //*/
    
    
    while(!WindowShouldClose()) {
        // Logic
        if(gamestate->state == STATE_MAP) {
            PlayerControls(gamestate);
        }
        if(IsKeyPressed(KEY_ESCAPE)) {
            if(gamestate->pmFlags & (1 << 0)) gamestate->pmFlags &= ~(1 << 0);
            else                              gamestate->pmFlags |=  (1 << 0);
        }
        
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(gamestate->camera);
        
        if(gamestate->state == STATE_MAP) {
            if(gamestate->optionsData->messageLogging) DrawGrid(100,1);
            
            DrawMap(gamestate);
            
            
        }
        
        EndMode3D();
        
        
        // Draw 2D
        DrawMainMenu(gamestate);
        
        // Draw Pause Menu
        DrawPauseMenu(gamestate);
        
        // Options menu
        DrawOptionsMenu(gamestate);
        
        
        
        // Draw Debug
        if(gamestate->optionsData->messageLogging) {
            DrawFPS(0,0);
            char buffer[20] = {0};
            sprintf(buffer, "%2.f,%2.f,%2.f\n %2.f\n",
                    gamestate-> camera.target.x,
                    gamestate->camera.target.y,
                    gamestate->camera.target.z,
                    gamestate->camera.fovy);
            if(gamestate->state == STATE_MAP) {
                sprintf(buffer, "%s\n",
                        gamestate->mapLocalization[0]);
            }
            DrawText(buffer, 0, 20, 20, BLACK);
        }
        
        EndDrawing();
    }
    
    QuitGame(gamestate);
    
    return 0;
}