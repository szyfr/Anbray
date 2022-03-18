///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



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