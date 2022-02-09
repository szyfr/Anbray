///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/13    //
///=-------------------=///



/// Functions

//  Draws options menu
//     Uses:
//   - GUI
//   - Localization
//   - Options
void DrawOptionsMenu(void) {
    if (gui->omFlags & (1 << 0)) {
        u32 top    = (options->resolutionHeight/2)-250;
        u32 bottom = (options->resolutionHeight/2)+250;
        u32 left   = (options->resolutionWidth/2) -200;
        u32 right  = (options->resolutionWidth/2) +200;
        
        GuiPanel((Rectangle){left, top, 400, 500});
        
        // Language
        if(GuiDropdownBox((Rectangle){left+100, top+135, 200, 25},
                          "English\nFrench\nItalian\nGerman\nSpanish",
                          &gui->languageActive,
                          gui->omFlags & (1 << 2))) {
            if (gui->omFlags & (1 << 2)) gui->omFlags &= ~(1 << 2);
            else                         gui->omFlags |=  (1 << 2);
        }
        
        // Map Level of Detail
        GuiLabel((Rectangle){left+100, top+65, 200, 25}, localization->coreLocalization[4]);
        gui->LOD = (int)GuiSlider((Rectangle){left+100, top+90, 200, 25}, localization->coreLocalization[5], localization->coreLocalization[6], gui->LOD, 0.0f, 4.0f);
        
        // Fullscreen toggle
        gui->fullscreenCheck = GuiCheckBox((Rectangle){left+275, top+20, 25, 25}, localization->coreLocalization[3], gui->fullscreenCheck);
        
        // Resolution dropdown
        if(GuiDropdownBox((Rectangle){left+50, top+20, 200, 25},
                          "1280x720\n1920x1080\n2560x1080\n2560x1440\n3840x2160\n7680x4320",
                          &gui->resolutionActive,
                          gui->omFlags & (1 << 1))) {
            if (gui->omFlags & (1 << 1)) gui->omFlags &= ~(1 << 1);
            else                         gui->omFlags |=  (1 << 1);
        }
        
        // Message log Toggle
        gui->messageCheck = GuiCheckBox((Rectangle){left+310, bottom-45, 25, 25}, localization->coreLocalization[12], gui->messageCheck);
        
        // Apply button
        if(GuiButton((Rectangle){left+100, bottom-90, 200, 25}, localization->coreLocalization[7])) {
            switch(gui->resolutionActive) {
                case 0: //720p
                options->resolutionWidth  = 1280;
                options->resolutionHeight =  720;
                break;
                
                case 1: //1080p
                options->resolutionWidth  = 1920;
                options->resolutionHeight = 1080;
                break;
                
                case 2: //1080p UWS
                options->resolutionWidth  = 2560;
                options->resolutionHeight = 1080;
                break;
                
                case 3: //2K
                options->resolutionWidth  = 2560;
                options->resolutionHeight = 1440;
                break;
                
                case 4: //4K
                options->resolutionWidth  = 3840;
                options->resolutionHeight = 2160;
                break;
                
                case 5: //8K
                options->resolutionWidth  = 7680;
                options->resolutionHeight = 4320;
                break;
            }
            
            options->fullscreen = gui->fullscreenCheck;
            
            options->mapLOD = (int)gui->LOD;
            
            options->language = gui->languageActive;
            
            options->messageLogging = gui->messageCheck;
            
            CommitOptionsData();
        }
        if(GuiButton((Rectangle){left+100, bottom-45, 200, 25}, localization->coreLocalization[8])) {
            gui->omFlags &= ~(1 << 0);
        }
    }
}