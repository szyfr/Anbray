///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/13    //
///=-------------------=///



///
void DrawOptionsMenu(Gamestate *gamestate) {
    if (gamestate->omFlags & (1 << 0)) {
        u32 top    = (gamestate->optionsData->resolutionHeight/2)-250;
        u32 bottom = (gamestate->optionsData->resolutionHeight/2)+250;
        u32 left   = (gamestate->optionsData->resolutionWidth/2) -200;
        u32 right  = (gamestate->optionsData->resolutionWidth/2) +200;
        
        GuiPanel((Rectangle){left, top, 400, 500});
        
        // Language
        if(GuiDropdownBox((Rectangle){left+100, top+135, 200, 25},
                          "English\nFrench\nItalian\nGerman\nSpanish",
                          &gamestate->languageActive,
                          gamestate->omFlags & (1 << 2))) {
            if (gamestate->omFlags & (1 << 2)) gamestate->omFlags &= ~(1 << 2);
            else                               gamestate->omFlags |=  (1 << 2);
        }
        
        // Map Level of Detail
        GuiLabel((Rectangle){left+100, top+65, 200, 25}, gamestate->coreLocalization[4]);
        gamestate->LOD = (int)GuiSlider((Rectangle){left+100, top+90, 200, 25}, gamestate->coreLocalization[5], gamestate->coreLocalization[6], gamestate->LOD, 0.0f, 4.0f);
        
        // Fullscreen toggle
        gamestate->fullscreenCheck = GuiCheckBox((Rectangle){left+275, top+20, 25, 25}, gamestate->coreLocalization[3], gamestate->fullscreenCheck);
        
        // Resolution dropdown
        if(GuiDropdownBox((Rectangle){left+50, top+20, 200, 25},
                          "1280x720\n1920x1080\n2560x1080\n2560x1440\n3840x2160\n7680x4320",
                          &gamestate->resolutionActive,
                          gamestate->omFlags & (1 << 1))) {
            if (gamestate->omFlags & (1 << 1)) gamestate->omFlags &= ~(1 << 1);
            else                               gamestate->omFlags |=  (1 << 1);
        }
        
        // Message log Toggle
        gamestate->messageCheck = GuiCheckBox((Rectangle){left+310, bottom-45, 25, 25}, gamestate->coreLocalization[12], gamestate->messageCheck);
        
        // Apply button
        if(GuiButton((Rectangle){left+100, bottom-90, 200, 25}, gamestate->coreLocalization[7])) {
            switch(gamestate->resolutionActive) {
                case 0: //720p
                gamestate->optionsData->resolutionWidth  = 1280;
                gamestate->optionsData->resolutionHeight =  720;
                break;
                
                case 1: //1080p
                gamestate->optionsData->resolutionWidth  = 1920;
                gamestate->optionsData->resolutionHeight = 1080;
                break;
                
                case 2: //1080p UWS
                gamestate->optionsData->resolutionWidth  = 2560;
                gamestate->optionsData->resolutionHeight = 1080;
                break;
                
                case 3: //2K
                gamestate->optionsData->resolutionWidth  = 2560;
                gamestate->optionsData->resolutionHeight = 1440;
                break;
                
                case 4: //4K
                gamestate->optionsData->resolutionWidth  = 3840;
                gamestate->optionsData->resolutionHeight = 2160;
                break;
                
                case 5: //8K
                gamestate->optionsData->resolutionWidth  = 7680;
                gamestate->optionsData->resolutionHeight = 4320;
                break;
            }
            
            gamestate->optionsData->fullscreen = gamestate->fullscreenCheck;
            
            gamestate->optionsData->mapLOD = (int)gamestate->LOD;
            
            gamestate->optionsData->language = gamestate->languageActive;
            
            gamestate->optionsData->messageLogging = gamestate->messageCheck;
            
            CommitOptionsData(gamestate);
        }
        if(GuiButton((Rectangle){left+100, bottom-45, 200, 25}, gamestate->coreLocalization[8])) {
            gamestate->omFlags &= ~(1 << 0);
        }
    }
}