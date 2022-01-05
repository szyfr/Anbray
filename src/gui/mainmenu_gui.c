///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// DrawMainMenu(gamestate);
//   Draws the gui elements of the main menu and tracks the flags
void DrawMainMenu(Gamestate *gamestate) {
    if(gamestate->state == STATE_MAINMENU) {
        // New game button
        if(GuiButton((Rectangle){10,200,200,100}, "New Game")) {
            if(!gamestate->mmFlags & (1 << 0)) gamestate->mmFlags |=  (1 << 0);
            else                               gamestate->mmFlags &= ~(1 << 0);
        }
        
        // Map selection list
        if(gamestate->mmFlags & (1 << 0)) {
            int count = 0;
            char **directoryList = GetDirectoryFiles("data/maps", &count);
            
            for(int i = 0; i < count-2; i++) {
                
                char location[200] = {0};
                strcat(location,"data/maps/");
                strcat(location,directoryList[i+2]);
                strcat(location,"/MapData.bin");
                
                int read = 0;
                MapData *file = (MapData*)LoadFileData(location,&read);
                
                if(GuiButton((Rectangle){210,200+(i*20),200,20}, file->mapName)) {
                    int count = strlen(directoryList[i+2]);
                    char *name = calloc(1,count);
                    strcpy(name, directoryList[i+2]);
                    gamestate->mapName = directoryList[i+2];
                    
                    LoadMapData(gamestate);
                    
                    gamestate->state = STATE_MAP;
                }
                
                UnloadFileData((char*)file);
            }
            ClearDirectoryFiles();
        }
    }
}