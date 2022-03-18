///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/05   //
//   @Edited:  22/03/17   //
///=--------------------=///



// Initialize the player data
//     Uses:
//   - Player
void InitializePlayer(void) {
    // Initializing Camera
    player->camera.target   = (Vector3){startingX, 0.0f,            startingZ};
    player->camera.position = (Vector3){startingX, positionYOffset, startingZ+positionZOffset};
    player->camera.up       = (Vector3){0.0f,1.0f,0.0f};
    player->camera.fovy     = 20.0f;
    
    DB_Errorlog("(S): Initialized player\n");
    return;
    DB_Errorlog("(F): Initialized player\n");
}