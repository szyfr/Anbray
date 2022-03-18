///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



//  Draws a singular chunk at the offset
//     Uses:
//   - Map
void DrawSingleChunk(u32 chunk, float xOffset) {
    if(map->chunks == 0) {
        char str[50] = {0};
        sprintf(str, "Attempted to load chunk[%i], but map is empty\n", chunk);
        
        DB_CrashError(str);
    }
    
    DrawModel(map->chunks[chunk].model,
              (Vector3){
                  map->chunks[chunk].location.x + xOffset,
                  map->chunks[chunk].location.y,
                  map->chunks[chunk].location.z },
              1.0f, WHITE);
}