///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/13    //
///=-------------------=///



///
void DrawPauseMenu(Gamestate *gamestate) {
    if (gamestate->pmFlags & (1 << 0) && gamestate->state == STATE_MAP) {
        u32 top    = (gamestate->optionsData->resolutionHeight/2)-180;
        u32 bottom = (gamestate->optionsData->resolutionHeight/2)+180;
        u32 left   = (gamestate->optionsData->resolutionWidth/2) -100;
        u32 right  = (gamestate->optionsData->resolutionWidth/2) +100;
        
        GuiPanel((Rectangle){left, top, 200, 360});
        
        // Resume
        if(GuiButton((Rectangle){left+10, top+10, 180, 40}, gamestate->coreLocalization[9])) {
            gamestate->pmFlags &= ~(1 << 0);
        }
        
        // Save
        if(GuiButton((Rectangle){left+10, top+70, 180, 40}, gamestate->coreLocalization[10])) {
            // TODO: SAVE
        }
        
        // Load
        if(GuiButton((Rectangle){left+10, top+130, 180, 40}, gamestate->coreLocalization[11])) {
            // TODO: LOAD
        }
        
        // Options
        if(GuiButton((Rectangle){left+10, top+190, 180, 40}, gamestate->coreLocalization[1])) {
            gamestate->omFlags |=  (1 << 0);
        }
        
        // Main Menu
        if(GuiButton((Rectangle){left+10, top+250, 180, 40}, gamestate->coreLocalization[13])) {
            FreeLocalization(gamestate,false);
            FreeMap(gamestate);
            gamestate->state = STATE_MAINMENU;
        }
        
        // Quit
        if(GuiButton((Rectangle){left+10, top+310, 180, 40}, gamestate->coreLocalization[2])) QuitGame(gamestate);
    }
}