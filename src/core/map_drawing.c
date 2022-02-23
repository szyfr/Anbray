///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Constants
const float maximumDistance = 4.0f;

/// Functions

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

//  Draws all chunks in view
//     Uses:
//   - Map
//   - Player
void DrawChunks(bool lessThan, float range, float xOffset) {
    for(int i = 0; i < map->numChunks; i++) {
        float disX = pow((map->chunks[i].location.x + xOffset) - player->camera.target.x, 2.0);
        float disZ = pow(map->chunks[i].location.z             - player->camera.target.z, 2.0);
        float distance = sqrtf(disX+disZ);
        
        if(distance <= maximumDistance) {
            // If range less than
            if(map->chunks[i].location.x <= range &&  lessThan) DrawSingleChunk(i, xOffset);
            // If range greater than
            if(map->chunks[i].location.x >= range && !lessThan) DrawSingleChunk(i, xOffset);
        }
    }
}

//  Draws the map
//     Uses:
//   - Map
void DrawMap(void) {
    DrawChunks(false, map->edge, -map->edge-3);
    DrawChunks(false, 0.0f,       0.0f);
    DrawChunks(true,  2.0f,       map->chunkWidth);
}