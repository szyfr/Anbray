///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Grabs the map localization file
//     Uses:
//   - Options
char *GetRawMapLocalization(char *mapname, u32 *rawRead) {
    // Ready variables
    char location[200] = {0};
    strcat(location,"data/maps/");
    strcat(location,mapname);
    strcat(location,"/localization/");
    
    // Read language settings
    switch(options->language) {
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
        DB_Errorlog(str);
        
        // Grabs english by default
        memset(location, 0, 200);
        strcat(location,"data/maps/");
        strcat(location,mapname);
        strcat(location,"/localization/english.bin");
        
        if(!FileExists(location)) DB_CrashError("(F): Could not find English localization\n");
    }
    
    // Grab data
    return LoadFileData(location, rawRead);
}