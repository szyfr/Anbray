///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
char *GetRawCoreLocalization(Gamestate *gamestate, u32 *rawRead) {
    // Ready variables
    char location[200] = {0};
    strcat(location,"data/localization/");
    
    // Read language settings
    switch(gamestate->optionsData->language) {
        case english:
        strcat(location,"english.bin");
        break;
        
        case french:
        strcat(location,"french.bin");
        break;
        
        case italian:
        strcat(location,"italian.bin");
        break;
        
        case german:
        strcat(location,"german.bin");
        break;
        
        case spanish:
        strcat(location,"spanish.bin");
        break;
    }
    
    // Check for file
    if(!FileExists(location)) {
        if(gamestate->debug) printf("File (%s) does not exist\n",location);
        
        // Grabs english by default
        memset(location, 0, 200);
        strcat(location,"data/localization/english.bin");
    }
    
    // Grab data
    return LoadFileData(location, rawRead);
}

///
char *GetRawMapLocalization(Gamestate *gamestate, char *mapname,  u32 *rawRead) {
    // Ready variables
    char location[200] = {0};
    strcat(location,"data/maps/");
    strcat(location,mapname);
    strcat(location,"/localization/");
    
    // Read language settings
    switch(gamestate->optionsData->language) {
        case english:
        strcat(location,"english.bin");
        break;
        
        case french:
        strcat(location,"french.bin");
        break;
        
        case italian:
        strcat(location,"italian.bin");
        break;
        
        case german:
        strcat(location,"german.bin");
        break;
        
        case spanish:
        strcat(location,"spanish.bin");
        break;
    }
    
    // Check for file
    if(!FileExists(location)) {
        if(gamestate->debug) printf("File (%s) does not exist\n",location);
        
        // Grabs english by default
        memset(location, 0, 200);
        strcat(location,"data/maps/");
        strcat(location,mapname);
        strcat(location,"/localization/english.bin");
    }
    
    // Grab data
    return LoadFileData(location, rawRead);
}

///
void LoadLocalization(Gamestate *gamestate, char *mapname) {
    // ErrorCheck
    if(!mapname) {
        if(gamestate->coreLocalization != 0) {
            printf("Tried to re-load core localization.");
            return;
        }
    } else {
        if(gamestate->mapLocalization != 0) {
            printf("Tried to re-load map localization.");
            return;
        }
    }
    
    // Read file
    u32 rawRead = 0;
    char *rawFileData = {0};
    
    if(!mapname) rawFileData = GetRawCoreLocalization(gamestate, &rawRead);
    else         rawFileData = GetRawMapLocalization(gamestate, mapname, &rawRead);
    
    
    // Get the total count of members
    gamestate->coreLength = 0;
    gamestate->mapLength  = 0;
    for(int i = 0; i < rawRead; i++) {
        if(rawFileData[i] == 0x0A) {
            if(!mapname) gamestate->coreLength++;
            else         gamestate->mapLength++;
            rawFileData[i] = 0x00;
        }
    }
    
    // Create array
    char **localArr = {0};
    if(!mapname) localArr = (char **)calloc(gamestate->coreLength, sizeof(char*));
    else         localArr = (char **)calloc(gamestate->mapLength,  sizeof(char*));
    
    // Copy each string into own ptr
    char *ptr = rawFileData;
    u16 length;
    if(!mapname) length = gamestate->coreLength;
    else         length = gamestate->mapLength;
    
    for(int i = 0; i < length; i++) {
        localArr[i] = (char*)calloc(strlen(ptr)+1,sizeof(char));
        strcpy(localArr[i],ptr);
        ptr += strlen(ptr)+1;
    }
    
    // Free
    if(!mapname) gamestate->coreLocalization = localArr;
    else         gamestate->mapLocalization  = localArr;
    UnloadFileData(rawFileData);
}

//
void FreeLocalization(Gamestate *gamestate, bool core) {
    // Ready variables
    u16 length;
    char **array;
    if(core) {
        length = gamestate->coreLength;
        array  = gamestate->coreLocalization;
    } else {
        length = gamestate->mapLength;
        array  = gamestate->mapLocalization;
    } 
    
    // Free each string
    for(int i = 0; i < length; i++) {
        //printf("Freeing (%p): %s\n",array[i],array[i]);
        free(array[i]);
    }
    
    // Free array
    if(core) {
        free(gamestate->coreLocalization);
        gamestate->coreLocalization = 0;
    } else {
        free(gamestate->mapLocalization);
        gamestate->mapLocalization = 0;
    }
}