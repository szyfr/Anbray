///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/13    //
///=-------------------=///



/// Functions

//  Draws pause menu
//     Uses:
//   - Gamestate
//   - GUI
//   - Localization
void DrawPauseMenu(void) {
    if (gui->pmFlags & (1 << 0) && gamestate->state == STATE_MAP) {
        u32 top    = (options->resolutionHeight/2)-180;
        u32 bottom = (options->resolutionHeight/2)+180;
        u32 left   = (options->resolutionWidth/2) -100;
        u32 right  = (options->resolutionWidth/2) +100;
        
        GuiPanel((Rectangle){left, top, 200, 360});
        
        // Resume
        if(GuiButton((Rectangle){left+10, top+10, 180, 40}, localization->coreLocalization[9])) {
            gui->pmFlags &= ~(1 << 0);
        }
        
        // Save
        if(GuiButton((Rectangle){left+10, top+70, 180, 40}, localization->coreLocalization[10])) {
            // TODO: SAVE
        }
        
        // Load
        if(GuiButton((Rectangle){left+10, top+130, 180, 40}, localization->coreLocalization[11])) {
            // TODO: LOAD
        }
        
        // Options
        if(GuiButton((Rectangle){left+10, top+190, 180, 40}, localization->coreLocalization[1])) {
            gui->omFlags |=  (1 << 0);
        }
        
        // Main Menu
        if(GuiButton((Rectangle){left+10, top+250, 180, 40}, localization->coreLocalization[13])) {
            FreeLocalization(false);
            FreeMap();
            gamestate->state = STATE_MAINMENU;
        }
        
        // Quit
        if(GuiButton((Rectangle){left+10, top+310, 180, 40}, localization->coreLocalization[2])) QuitGame();
    }
}