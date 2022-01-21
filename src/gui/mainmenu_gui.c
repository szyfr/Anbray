///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Functions

// Draws the gui elements of the main menu and tracks the flags
void DrawMainMenu(Gamestate *gamestate) {
    if(gamestate->state == STATE_MAINMENU) {
        // New game button
        if(GuiButton((Rectangle){10,200,150,75}, gamestate->coreLocalization[0])) {
            if(!gamestate->mmFlags & (1 << 0)) gamestate->mmFlags |=  (1 << 0);
            else                               gamestate->mmFlags &= ~(1 << 0);
        }
        // Options button
        if(GuiButton((Rectangle){10,300,150,75}, gamestate->coreLocalization[1])) {
            if (gamestate->omFlags & (1 << 0)) gamestate->omFlags &= ~(1 << 0);
            else                               gamestate->omFlags |=  (1 << 0);
        }
        // Quit button
        if(GuiButton((Rectangle){10,400,150,75}, gamestate->coreLocalization[2])) QuitGame(gamestate);
        
        // Map selection list
        if(gamestate->mmFlags & (1 << 0)) {
            int count = 0;
            char **directoryList = GetDirectoryFiles("data/maps", &count);
            
            for(int i = 0; i < count-2; i++) {
                int read = 0;
                char *localName = GrabMapName(GetRawMapLocalization(gamestate, directoryList[i+2], &read));
                
                if(GuiButton((Rectangle){410,200+(i*20),200,20}, localName)) {
                    if(!gamestate->omFlags & (1 << 0)) {
                        free(localName);
                        LoadLocalization(gamestate, directoryList[i+2]);
                        LoadMapData(gamestate);
                        gamestate->state = STATE_MAP;
                    }
                }
                free(localName);
            }
            ClearDirectoryFiles();
        }
    }
}