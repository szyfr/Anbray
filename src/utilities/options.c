///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/14    //
///=-------------------=///


/// Prototypes
// TODO: figure out if i can do this in a better way
void FreeMap(Gamestate *gamestate);
void LoadMapData(Gamestate *gamestate);

///
void CommitOptionsData(Gamestate *gamestate) {
    if(gamestate->optionsData->fullscreen) {
        if(!IsWindowFullscreen()) ToggleFullscreen();
    } else {
        if(IsWindowFullscreen())  ToggleFullscreen();
    }
    
    SetWindowSize(gamestate->optionsData->resolutionWidth, gamestate->optionsData->resolutionHeight);
    
    if(gamestate->coreLocalization != 0) {
        FreeLocalization(gamestate,true);
        LoadLocalization(gamestate, 0);
    }
    if(gamestate->mapLocalization != 0) {
        FreeLocalization(gamestate,false);
        LoadLocalization(gamestate, gamestate->mapLocalization[0]);
    }
    
    if(gamestate->map.chunks != 0) {
        FreeMap(gamestate);
        LoadMapData(gamestate);
    }
}

void InitOptions(Gamestate *gamestate) {
    u32 rawRead = 0;
    
    // Check for existing options file
    if(FileExists("data/options.bin")) {
        if(gamestate->debug) printf("Options file already exists\n");
        
        // Load file
        gamestate->optionsData = (OptionsData*)LoadFileData("data/options.bin", &rawRead);
        CommitOptionsData(gamestate);
        
        return;
    }
    if(gamestate->debug) printf("Options file doesn't exist\n");
    
    // Generate new file
    gamestate->optionsData = (OptionsData*)calloc(1,sizeof(OptionsData));
    gamestate->optionsData->resolutionWidth  =    1280;
    gamestate->optionsData->resolutionHeight =     720;
    gamestate->optionsData->fullscreen       =   false;
    gamestate->optionsData->mapLOD           =       3;
    gamestate->optionsData->language         = english;
    
    // Commit file and save
    CommitOptionsData(gamestate);
    SaveFileData("data/options.bin", (void*)gamestate->optionsData, sizeof(OptionsData)-1);
}