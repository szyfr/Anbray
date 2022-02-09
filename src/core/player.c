///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 22/01/05    //
///=-------------------=///



/// Constants
const float mouseWheelModifier =  1.50f;
const float fovyMinimum        =  4.00f;
const float fovyMaximum        = 20.00f;
const float startingX          = 13.25f;
const float startingZ          =  1.50f;
const float positionYOffset    =  5.00f;
const float positionZOffset    =  2.50f;

const float cameraZMinimum     =  0.00f;
const float cameraZMaximumOff  =  0.25f;


/// Functions

// Initialize the player data
//     Uses:
//   - Player
void InitializePlayer(void) {
    // Initializing Camera
    player->camera.target   = (Vector3){startingX, 0.0f,            startingZ};
    player->camera.position = (Vector3){startingX, positionYOffset, startingZ + positionZOffset};
    player->camera.up       = (Vector3){0.0f,1.0f,0.0f};
    player->camera.fovy     = 20.0f;
    
    DB_Errorlog("(S): Initialized player\n");
    return;
    DB_Errorlog("(F): Initialized player\n");
}

//  Polls controls and moves player
//     Uses:
//   - Map
//   - Player
void PlayerControls(void) {
    float movementMod = (0.1f * (player->camera.fovy/20));
    
    // Checking input
    if(IsKeyDown(KEY_W)) {
        player->camera.target.z   -= movementMod;
        player->camera.position.z -= movementMod;
    }
    if(IsKeyDown(KEY_S)) {
        player->camera.target.z   += movementMod;
        player->camera.position.z += movementMod;
    }
    if(IsKeyDown(KEY_A)) {
        player->camera.target.x   -= movementMod;
        player->camera.position.x -= movementMod;
    }
    if(IsKeyDown(KEY_D)) {
        player->camera.target.x   += movementMod;
        player->camera.position.x += movementMod;
    }
    
    // Jumping on map edge
    float chunkWidth = map->provincesImg.width/250;
    if(player->camera.target.x < 0) {
        player->camera.target.x   = chunkWidth;
        player->camera.position.x = chunkWidth;
    }
    if(player->camera.target.x > chunkWidth) {
        player->camera.target.x   = 0;
        player->camera.position.x = 0;
    }
    
    // Clamping to map z axis
    float chunkHeight = (map->provincesImg.height/250)-cameraZMaximumOff;
    player->camera.target.z   = Clamp(player->camera.target.z, cameraZMinimum, chunkHeight);
    player->camera.position.z = Clamp(player->camera.position.z, cameraZMinimum + positionZOffset, chunkHeight + positionZOffset);
    
    // Zoom
    float mouseWheel = GetMouseWheelMove();
    if(mouseWheel) {
        player->camera.fovy -= (mouseWheel / mouseWheelModifier);
        player->camera.fovy  = Clamp(player->camera.fovy, fovyMinimum, fovyMaximum);
    }
}