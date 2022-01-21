///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/14    //
///=-------------------=///


/// Prototypes
// TODO: figure out if i can do this in a better way
void FreeMap(Gamestate *gamestate);
void LoadMapData(Gamestate *gamestate);

/// Functions

// Save the options and apply them
void CommitOptionsData(Gamestate *gamestate) {
    // Set fullscreen
    if(gamestate->optionsData->fullscreen) {
        if(!IsWindowFullscreen()) ToggleFullscreen();
    } else {
        if(IsWindowFullscreen())  ToggleFullscreen();
    }
    
    // Set window size
    SetWindowSize(gamestate->optionsData->resolutionWidth, gamestate->optionsData->resolutionHeight);
    
    // Set localization language
    //TODO: Check to see if the localization language was changed, and THEN if it did, reload
    if(gamestate->coreLocalization != 0) {
        FreeLocalization(gamestate,true);
        LoadLocalization(gamestate, 0);
    }
    if(gamestate->mapLocalization != 0) {
        char *str = (char*)calloc(strlen(gamestate->mapLocalization[0])+1,sizeof(char));
        strcpy(str,gamestate->mapLocalization[0]);
        
        FreeLocalization(gamestate,false);
        LoadLocalization(gamestate, str);
        
        free(str);
    }
    
    // Restart map
    if(gamestate->map.chunks != 0) {
        FreeMap(gamestate);
        LoadMapData(gamestate);
    }
    
    // Logging
    if(gamestate->errorlog != 0) DB_Errorlog(gamestate, "(S): Committed options changes.\n");
    
    SaveFileData("data/options.bin", (void*)gamestate->optionsData, sizeof(OptionsData)-1);
}

// Initialize the options
void InitOptions(Gamestate *gamestate) {
    u32 rawRead = 0;
    
    // Check for existing options file
    if(FileExists("data/options.bin")) {
        gamestate->optionsData = (OptionsData*)LoadFileData("data/options.bin", &rawRead);
        
        // Run checks
        if(gamestate->optionsData->resolutionWidth  > GetMonitorWidth(GetCurrentMonitor()) || gamestate->optionsData->resolutionHeight > GetMonitorHeight(GetCurrentMonitor())) {
            
            gamestate->optionsData->resolutionWidth  =    1280;
            gamestate->optionsData->resolutionHeight =     720;
        }
        if(gamestate->optionsData->mapLOD  > 4) gamestate->optionsData->mapLOD    =       0;
        if(gamestate->optionsData->language > 4) gamestate->optionsData->language = english;
        
        CommitOptionsData(gamestate);
        return;
    }
    
    // Generate new file
    gamestate->optionsData = (OptionsData*)calloc(1,sizeof(OptionsData));
    gamestate->optionsData->resolutionWidth  =    1280;
    gamestate->optionsData->resolutionHeight =     720;
    gamestate->optionsData->fullscreen       =   false;
    gamestate->optionsData->mapLOD           =       3;
    gamestate->optionsData->language         = english;
    gamestate->optionsData->messageLogging   =    true;
    
    // Commit file and save
    CommitOptionsData(gamestate);
}