///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/07    //
///=-------------------=///



/// Constants
const float maximumDistance = 3.25f;

/// Functions
void DrawSingleChunk(Gamestate *gamestate, u32 chunk, float xOffset) {
    DrawModel(gamestate->map.chunks[chunk].model,
              (Vector3){
                  gamestate->map.chunks[chunk].location.x + xOffset, gamestate->map.chunks[chunk].location.y, gamestate->map.chunks[chunk].location.z},
              1.0f, WHITE);
}

void DrawChunks(Gamestate *gamestate, bool lessThan, float range, float xOffset) {
    for(int i = 0; i < gamestate->map.numChunks; i++) {
        float disX = pow((gamestate->map.chunks[i].location.x + xOffset) - gamestate->camera.target.x,2.0);
        float disZ = pow(gamestate->map.chunks[i].location.z - gamestate->camera.target.z,2.0);
        float distance = sqrtf(disX+disZ);
        
        if(distance <= maximumDistance) {
            // If range less than
            if(gamestate->map.chunks[i].location.x <= range && lessThan) {
                DrawSingleChunk(gamestate, i, xOffset);
            }
            // If range greater than
            if(gamestate->map.chunks[i].location.x >= range && !lessThan) {
                DrawSingleChunk(gamestate, i, xOffset);
            }
        }
    }
}

void DrawMap(Gamestate *gamestate) {
    u32 chunkWidth = gamestate->map.provincesImg.width / 250;
    float rightEdge = chunkWidth - 3;
    
    DrawChunks(gamestate, false, rightEdge, -rightEdge-3);
    DrawChunks(gamestate, false, 0.0f,       0.0f);
    DrawChunks(gamestate, true,  2.0f,       chunkWidth);
}