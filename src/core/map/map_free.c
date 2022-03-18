///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Frees the map
//     Uses:
//   - Map
void FreeMap(void) {
    if(map->chunks == 0) {
        DB_Errorlog("(S): No chunks to free.\n");
        return;
    }
    
    // Delete province list
    DeleteProvinceList(map->provinces);
    
    // Free data in chunks
    for(int i = 0; i < map->numChunks; i++) {
        UnloadModel(map->chunks[i].model);
        UnloadTexture(map->chunks[i].texture);
    }
    
    // Free chunks
    free(map->chunks);
    map->chunks = 0;
    map->numChunks = 0;
    
    // Free images
    UnloadImage(map->provincesImg);
    UnloadImage(map->terrainImg);
    
    DB_Errorlog("(S): Freed Chunks.\n");
}