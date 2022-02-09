///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/14    //
///=-------------------=///



/// Functions

// Save the options and apply them
//     Uses:
//   - DebugLogger
//   - Options
//   - Localization
//   - Map
void CommitOptionsData(void) {
    // Set fullscreen
    if(options->fullscreen) {
        if(!IsWindowFullscreen()) ToggleFullscreen();
    } else {
        if(IsWindowFullscreen())  ToggleFullscreen();
    }
    
    // Set window size
    SetWindowSize(options->resolutionWidth, options->resolutionHeight);
    
    // Set localization language
    //TODO: Check to see if the localization language was changed, and THEN if it did, reload
    if(localization->coreLocalization != 0) {
        FreeLocalization(true);
        LoadLocalization(0);
    }
    if(localization->mapLocalization != 0) {
        printf("Commit: %p\n",localization->mapLocalization[0]);
        char *str = (char*)calloc(strlen(localization->mapLocalization[0])+1,sizeof(char));
        strcpy(str,localization->mapLocalization[0]);
        
        FreeLocalization(false);
        LoadLocalization(str);
        
        free(str);
    }
    
    // Restart map
    if(map->chunks != 0) {
        FreeMap();
        LoadMapData();
    }
    
    // Logging
    if(debugLogger->errorlog != 0) DB_Errorlog("(S): Committed options changes.\n");
    
    SaveFileData("data/options.bin", (void*)options, sizeof(OptionsData)-1);
}

//  Initialize the options
//     Uses:
//   - GUI
//   - Options
void InitializeOptions(void) {
    u32 rawRead = 0;
    
    // Check for existing options file
    if(FileExists("data/options.bin")) {
        options = (OptionsData*)LoadFileData("data/options.bin", &rawRead);
        
        // Run checks
        if(options->resolutionWidth  > GetMonitorWidth(GetCurrentMonitor()) || options->resolutionHeight > GetMonitorHeight(GetCurrentMonitor())) {
            
            options->resolutionWidth  =    1280;
            options->resolutionHeight =     720;
        }
        if(options->mapLOD  > 4)  options->mapLOD    =       0;
        if(options->language > 4) options->language  = english;
    } else {
        // Generate new file
        options = (OptionsData*)calloc(1,sizeof(OptionsData));
        options->resolutionWidth  =    1280;
        options->resolutionHeight =     720;
        options->fullscreen       =   false;
        options->mapLOD           =       3;
        options->language         = english;
        options->messageLogging   =    true;
    }
    
    // Set GUI elements to new settings
    switch(options->resolutionWidth) {
        default:
        case 1280:
        gui->resolutionActive = 0;
        break;
        case 1920:
        gui->resolutionActive = 1;
        break;
        case 2560:
        if(options->resolutionHeight == 1080) gui->resolutionActive = 2;
        else                                  gui->resolutionActive = 3;
        break;
        case 3840:
        gui->resolutionActive = 4;
        break;
        case 7680:
        gui->resolutionActive = 5;
        break;
    }
    gui->fullscreenCheck = options->fullscreen;
    gui->languageActive  = options->language;
    gui->LOD             = options->mapLOD;
    gui->messageCheck    = options->messageLogging;
    
    // Commit file and save
    CommitOptionsData();
}