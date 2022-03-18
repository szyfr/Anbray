///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Loads the localization strings from file
//     Uses:
//   - Localization
void LoadLocalization(char *mapname) {
    // ErrorCheck
    if(!mapname) {
        if(localization->coreLocalization != 0) {
            DB_Errorlog("(F): Attempted loading core localization while already loaded\n");
            return;
        }
    } else {
        if(localization->mapLocalization != 0) {
            DB_Errorlog("(F): Attempted loading map localization while already loaded\n");
            return;
        }
    }
    
    // Read file
    u32 rawRead = 0;
    char *rawFileData = {0};
    
    if(!mapname) rawFileData = GetRawCoreLocalization(&rawRead);
    else         rawFileData = GetRawMapLocalization(mapname, &rawRead);
    
    
    // Get the total count of members
    for(int i = 0; i < rawRead; i++) {
        if(rawFileData[i] == 0x0A) {
            if(!mapname) localization->coreLength++;
            else         localization->mapLength++;
            rawFileData[i] = 0x00;
        }
    }
    
    // Create array
    char **localArr = {0};
    if(!mapname) localArr = (char **)calloc(localization->coreLength, sizeof(char*));
    else         localArr = (char **)calloc(localization->mapLength,  sizeof(char*));
    
    // Copy each string into own ptr
    char *ptr = rawFileData;
    u16 length;
    if(!mapname) length = localization->coreLength;
    else         length = localization->mapLength;
    
    for(int i = 0; i < length; i++) {
        localArr[i] = (char*)calloc(strlen(ptr)+1,sizeof(char));
        strcpy(localArr[i],ptr);
        ptr += strlen(ptr)+1;
    }
    
    // Free
    if(!mapname) {
        localization->coreLocalization = localArr;
        
        if(localArr != 0) DB_Errorlog("(S): Initialized core localization.\n");
        else              DB_Errorlog("(F): Initialized core localization.\n");
    } else {
        localization->mapLocalization  = localArr;
        
        if(localArr != 0) DB_Errorlog("(S): Initialized map localization.\n");
        else              DB_Errorlog("(F): Initialized map localization.\n");
    }
    UnloadFileData(rawFileData);
}