///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Functions

// Draws the gui elements of the main menu and tracks the flags
//     Uses:
//   - Gamestate
//   - GUI
//   - Localization
void DrawMainMenu(void) {
    if(gamestate->state == STATE_MAINMENU) {
        // New game button
        if(GuiButton((Rectangle){10,200,150,75}, localization->coreLocalization[0])) {
            if(!gui->mmFlags & (1 << 0)) gui->mmFlags |=  (1 << 0);
            else                         gui->mmFlags &= ~(1 << 0);
        }
        // Options button
        if(GuiButton((Rectangle){10,300,150,75}, localization->coreLocalization[1])) {
            if (gui->omFlags & (1 << 0)) gui->omFlags &= ~(1 << 0);
            else                         gui->omFlags |=  (1 << 0);
        }
        // Quit button
        if(GuiButton((Rectangle){10,400,150,75}, localization->coreLocalization[2])) QuitGame();
        
        // Map selection list
        if(gui->mmFlags & (1 << 0)) {
            int count = 0;
            char **directoryList = GetDirectoryFiles("data/maps", &count);
            
            for(int i = 0; i < count-2; i++) {
                int read = 0;
                char *localName = GrabMapName(GetRawMapLocalization(directoryList[i+2], &read));
                
                if(GuiButton((Rectangle){410,200+(i*20),200,20}, localName)) {
                    if(!gui->omFlags & (1 << 0)) {
                        LoadLocalization(directoryList[i+2]);
                        LoadMapData();
                        gamestate->state = STATE_MAP;
                    }
                }
                free(localName);
            }
            ClearDirectoryFiles();
        }
    }
}