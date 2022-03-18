///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Frees the localization
//     Uses:
//   - Localization
void FreeLocalization(bool core) {
    // Error checking
    if(core) {
        if(localization->coreLocalization == 0) {
            DB_Errorlog("(S): No core localization to free.\n");
            return;
        }
    } else {
        if(localization->coreLocalization == 0) {
            DB_Errorlog("(S): No map localization to free.\n");
            return;
        }
    }
    
    // Ready variables
    u16 length;
    char **array;
    if(core) {
        length = localization->coreLength;
        array  = localization->coreLocalization;
    } else {
        length = localization->mapLength;
        array  = localization->mapLocalization;
    } 
    
    // Free each string
    for(int i = 0; i < length; i++) {
        free(array[i]);
    }
    
    // Free array
    if(core) {
        free(localization->coreLocalization);
        localization->coreLocalization = 0;
        DB_Errorlog("(S): Freed core localization\n");
    } else {
        free(localization->mapLocalization);
        localization->mapLocalization = 0;
        DB_Errorlog("(S): Freed map localization\n");
    }
}