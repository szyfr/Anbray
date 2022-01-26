///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Functions

// Grabs the core localization file
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
        char str[55] = {0};
        sprintf(str, "(F): File (%s) does not exist\n",location);
        DB_Errorlog(gamestate, str);
        
        // Grabs english by default
        memset(location, 0, 200);
        strcat(location,"data/localization/english.bin");
        
        if(!FileExists(location)) {
            DB_Errorlog(gamestate, "(F): Could not find English localization\n");
            DB_CrashError(gamestate);
        }
    }
    
    // Grab data
    return LoadFileData(location, rawRead);
}

// Grabs the map localization file
char *GetRawMapLocalization(Gamestate *gamestate, char *mapname, u32 *rawRead) {
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
        char str[55] = {0};
        sprintf(str, "(F): File (%s) does not exist\n",location);
        DB_Errorlog(gamestate, str);
        
        // Grabs english by default
        memset(location, 0, 200);
        strcat(location,"data/maps/");
        strcat(location,mapname);
        strcat(location,"/localization/english.bin");
        
        if(!FileExists(location)) {
            DB_Errorlog(gamestate, "(F): Could not find English localization\n");
            DB_CrashError(gamestate);
        }
    }
    
    // Grab data
    return LoadFileData(location, rawRead);
}

// Grabs the map name from its localization file
char *GrabMapName(char *file) {
    // Changes first newline to a null-character
    char *first = strchr(file,'\n');
    *first = '\0';
    
    // Changes second newline to a null-character
    char *second = strchr(first+1,'\n');
    *second = '\0';
    
    // Creates new memory space for string asnd copies first entry into it
    char *str = calloc(strlen(first+1)+1, sizeof(char));
    strcpy(str, first+1);
    
    // Changes null-characters back into a newline and frees the memory
    *first = '\n';
    *second = '\n';
    UnloadFileData(file);
    
    return str;
}

// Loads the localization strings from file
void LoadLocalization(Gamestate *gamestate, char *mapname) {
    // ErrorCheck
    if(!mapname) {
        if(gamestate->coreLocalization != 0) {
            DB_Errorlog(gamestate, "(F): Attempted loading core localization while already loaded\n");
            return;
        }
    } else {
        if(gamestate->mapLocalization != 0) {
            DB_Errorlog(gamestate, "(F): Attempted loading map localization while already loaded\n");
            return;
        }
    }
    
    // Read file
    u32 rawRead = 0;
    char *rawFileData = {0};
    
    if(!mapname) rawFileData = GetRawCoreLocalization(gamestate, &rawRead);
    else         rawFileData = GetRawMapLocalization(gamestate, mapname, &rawRead);
    
    
    // Get the total count of members
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
    if(!mapname) {
        gamestate->coreLocalization = localArr;
        
        if(localArr != 0) DB_Errorlog(gamestate, "(S): Initialized core localization.\n");
        else              DB_Errorlog(gamestate, "(F): Initialized core localization.\n");
    } else {
        gamestate->mapLocalization  = localArr;
        
        if(localArr != 0) DB_Errorlog(gamestate, "(S): Initialized map localization.\n");
        else              DB_Errorlog(gamestate, "(F): Initialized map localization.\n");
    }
    UnloadFileData(rawFileData);
}

// Frees the localization
void FreeLocalization(Gamestate *gamestate, bool core) {
    if(core) {
        if(gamestate->coreLocalization == 0) {
            DB_Errorlog(gamestate, "(S): No core localization to free.\n");
            return;
        }
    } else {
        if(gamestate->coreLocalization == 0) {
            DB_Errorlog(gamestate, "(S): No map localization to free.\n");
            return;
        }
    }
    
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
        free(array[i]);
    }
    
    // Free array
    if(core) {
        free(gamestate->coreLocalization);
        gamestate->coreLocalization = 0;
        DB_Errorlog(gamestate, "(S): Freed core localization\n");
    } else {
        free(gamestate->mapLocalization);
        gamestate->mapLocalization = 0;
        DB_Errorlog(gamestate, "(S): Freed map localization\n");
    }
}