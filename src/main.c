///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/17   //
///=--------------------=///



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
#include "../include/include_struct.h"

static IVector3 *test;
static Vector3   center;
static u32       testCount;
const  float testFloat = 250.0f;

#include "../include/constants.h"
#include "../include/globals.h"

#include "../include/prototypes.h"
#include "../include/include_func.h"




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
        
        // mapmodes
        if(IsKeyPressed(KEY_Q)) ChangeMapmode(surface);
        if(IsKeyPressed(KEY_W)) ChangeMapmode(terrain);
        if(IsKeyPressed(KEY_E)) ChangeMapmode(nation);
        if(IsKeyPressed(KEY_R)) ChangeMapmode(race);
        if(IsKeyPressed(KEY_T)) ChangeMapmode(culture);
        if(IsKeyPressed(KEY_Y)) ChangeMapmode(religion);
        
        
        // Draw
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(player->camera);
        
        if(gamestate->state == STATE_MAP) {
            if(options->messageLogging) DrawGrid(100,1);
            
            DrawMap();
            
            
        }
        
        for(int i = 0; i < testCount; i++) {
            if(i != testCount-1) DrawLine3D(
                                            (Vector3){
                                                ((float)test[i].x+0.5f)/testFloat,
                                                ((float)test[i].y+0.5f)/12,
                                                ((float)test[i].z+0.5f)/testFloat},
                                            (Vector3){
                                                ((float)test[i+1].x+0.5f)/testFloat,
                                                ((float)test[i+1].y+0.5f)/12,
                                                ((float)test[i+1].z+0.5f)/testFloat},
                                            BLACK);
            else DrawLine3D(
                            (Vector3){
                                ((float)test[i].x+0.5f)/testFloat,
                                ((float)test[i].y+0.5f)/12,
                                ((float)test[i].z+0.5f)/testFloat},
                            (Vector3){
                                ((float)test[0].x+0.5f)/testFloat,
                                ((float)test[0].y+0.5f)/12,
                                ((float)test[0].z+0.5f)/testFloat},
                            BLACK);
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