///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Grabs the map name from its localization file
//     Uses:
//   - NONE
char *GrabMapName(char *file) {
    // Changes first newline to a null-character
    char *first = strchr(file,'\n');
    *first = '\0';
    
    // Changes second newline to a null-character
    char *second = strchr(first+1,'\n');
    *second = '\0';
    
    // Creates new memory space for string and copies first entry into it
    char *str = calloc(strlen(first+1)+1, sizeof(char));
    strcpy(str, first+1);
    
    // Changes null-characters back into a newline and frees the memory
    *first = '\n';
    *second = '\n';
    UnloadFileData(file);
    
    return str;
}