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
void InitializePlayer(Gamestate *gamestate) {
    // Initializing Camera
    gamestate->camera.target   = (Vector3){startingX, 0.0f,            startingZ};
    gamestate->camera.position = (Vector3){startingX, positionYOffset, startingZ + positionZOffset};
    gamestate->camera.up       = (Vector3){0.0f,1.0f,0.0f};
    gamestate->camera.fovy     = 20.0f;
    
    DB_Errorlog(gamestate, "(S): Initialized player\n");
    return;
    DB_Errorlog(gamestate, "(F): Initialized player\n");
}

void PlayerControls(Gamestate *gamestate) {
    float movementMod = (0.1f * (gamestate->camera.fovy/20));
    
    // Checking input
    if(IsKeyDown(KEY_W)) {
        gamestate->camera.target.z   -= movementMod;
        gamestate->camera.position.z -= movementMod;
    }
    if(IsKeyDown(KEY_S)) {
        gamestate->camera.target.z   += movementMod;
        gamestate->camera.position.z += movementMod;
    }
    if(IsKeyDown(KEY_A)) {
        gamestate->camera.target.x   -= movementMod;
        gamestate->camera.position.x -= movementMod;
    }
    if(IsKeyDown(KEY_D)) {
        gamestate->camera.target.x   += movementMod;
        gamestate->camera.position.x += movementMod;
    }
    
    // Jumping on map edge
    float chunkWidth = gamestate->map.provincesImg.width/250;
    if(gamestate->camera.target.x < 0) {
        gamestate->camera.target.x   = chunkWidth;
        gamestate->camera.position.x = chunkWidth;
    }
    if(gamestate->camera.target.x > chunkWidth) {
        gamestate->camera.target.x   = 0;
        gamestate->camera.position.x = 0;
    }
    
    // Clamping to map z axis
    float chunkHeight = (gamestate->map.provincesImg.height/250)-cameraZMaximumOff;
    gamestate->camera.target.z   = Clamp(gamestate->camera.target.z, cameraZMinimum, chunkHeight);
    gamestate->camera.position.z = Clamp(gamestate->camera.position.z, cameraZMinimum + positionZOffset, chunkHeight + positionZOffset);
    
    // Zoom
    float mouseWheel = GetMouseWheelMove();
    if(mouseWheel) {
        gamestate->camera.fovy -= (mouseWheel / mouseWheelModifier);
        gamestate->camera.fovy  = Clamp(gamestate->camera.fovy, fovyMinimum, fovyMaximum);
    }
}