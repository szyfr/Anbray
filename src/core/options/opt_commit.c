///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/14   //
//   @Edited:  22/03/17   //
///=--------------------=///



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