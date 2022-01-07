///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



#define DEBUG

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
#include "../include/generic_defines.h"
#include "../include/map.h"
#include "../include/population.h"
#include "../include/province_modifiers.h"
#include "../include/province.h"
#include "../include/gamestate.h"

#include "player.c"
#include "map/map_generation.c"
#include "map/map_drawing.c"
#include "gui/mainmenu_gui.c"
//TODO: include these in a seperate header
#include "utilities/population_linked_list.c"
#include "utilities/province_linked_list.c"
#include "utilities/province_modifier_linked_list.c"

#include "utilities/localization.c"


/// Main
int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1080, 720, "Anbray");
    SetTargetFPS(60);
    
    Gamestate *gamestate = (Gamestate*)calloc(1, sizeof(Gamestate));
    InitializePlayer(gamestate);
    
    LoadCoreLocalization(gamestate);
    
    printf("After Loading: %p\n",gamestate->coreLocalization[0]);
    
    while(!WindowShouldClose()) {
        printf("In Logic: %p\n",gamestate->coreLocalization[0]);
        // Logic
        if(gamestate->state == STATE_MAP) {
            PlayerControls(gamestate);
        }
        
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        printf("In Draw: %p\n",gamestate->coreLocalization[0]);
        
        // Draw 3D
        BeginMode3D(gamestate->camera);
        
        printf("In 3D: %p\n",gamestate->coreLocalization[0]);
        
        if(gamestate->state == STATE_MAP) {
            if(gamestate->debug) DrawGrid(100,1);
            
            DrawMap(gamestate);
        }
        
        EndMode3D();
        
        
        // Draw 2D
        DrawMainMenu(gamestate);
        
        
        // Draw Debug
        if(gamestate->debug) {
            DrawFPS(0,0);
            char buffer[20] = {0};
            sprintf(buffer, "%2.f,%2.f,%2.f\n %2.f",
                    gamestate-> camera.target.x,
                    gamestate->camera.target.y,
                    gamestate->camera.target.z,
                    gamestate->camera.fovy);
            DrawText(buffer, 0, 20, 20, BLACK);
        }
        
        EndDrawing();
    }
    
    return 0;
}