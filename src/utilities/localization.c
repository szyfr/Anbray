///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



///
// TODO: have settings define language
void LoadCoreLocalization(Gamestate *gamestate) {
    u32 rawRead = 0;
    char *rawFileData = LoadFileData("data/localization/english.bin", &rawRead);
    
    // Get the total count of members
    gamestate->coreLength = 0;
    for(int i = 0; i < rawRead; i++) if(rawFileData[i] == 0x00) gamestate->coreLength++;
    
    // Create array
    char *localArr[gamestate->coreLength];
    
    // Copy each string into own ptr
    // TODO: Localization array losing strings
    char *ptr = rawFileData;
    for(int i = 0; i < gamestate->coreLength; i++) {
        localArr[i] = (char*)calloc(1,strlen(ptr));
        strcpy(localArr[i],ptr);
        ptr += strlen(ptr)+1;
    }
    
    gamestate->coreLocalization = localArr;
    printf("While loading: %p\n",gamestate->coreLocalization[0]);
    UnloadFileData(rawFileData);
}