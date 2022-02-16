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
    float movementMod = (0.065f * (player->camera.fovy/20));
    
    // Checking input (Keys)
    if(IsKeyDown(KEY_UP)) {
        player->camera.target.z   -= movementMod;
        player->camera.position.z -= movementMod;
    }
    if(IsKeyDown(KEY_DOWN)) {
        player->camera.target.z   += movementMod;
        player->camera.position.z += movementMod;
    }
    if(IsKeyDown(KEY_LEFT)) {
        player->camera.target.x   -= movementMod;
        player->camera.position.x -= movementMod;
    }
    if(IsKeyDown(KEY_RIGHT)) {
        player->camera.target.x   += movementMod;
        player->camera.position.x += movementMod;
    }
    
    // Checking input (Mouse)
    Vector2 mouseDelta = GetMouseDelta();
    if(IsMouseButtonDown(2)) {
        mouseDelta.x *= movementMod / 20;
        mouseDelta.y *= movementMod / 20;
        
        player->camera.target.x   -= mouseDelta.x;
        player->camera.position.x -= mouseDelta.x;
        player->camera.target.z   -= mouseDelta.y;
        player->camera.position.z -= mouseDelta.y;
    }
    
    // Province interaction
    if(IsMouseButtonPressed(0)) {
        
        Ray mouseRay = GetMouseRay(GetMousePosition(), player->camera);
        RayCollision col = {0};
        
        for(int i = 0; i < map->numChunks; i++) {
            float disX = pow((map->chunks[i].location.x + 0.0f) - player->camera.target.x, 2.0);
            float disZ = pow(map->chunks[i].location.z          - player->camera.target.z, 2.0);
            float distance = sqrtf(disX+disZ);
            
            
            if(distance <= 4) {
                Matrix mat = MatrixTranslate(map->chunks[i].location.x, 0, map->chunks[i].location.z);
                col = GetRayCollisionMesh(mouseRay, map->chunks[i].mesh, mat);
            }
            
            if(col.hit) break;
        }
        //printf("Collision:\nHit: %i\nDist: %i\nPoint: %f,%f,%f\n", col.hit, col.distance, col.point.x, col.point.y, col.point.z);
        if(col.hit) {
            float chunkWidth  = map->provincesImg.width/250;
            float chunkHeight = map->provincesImg.height/250;
            Vector3 pixel = (Vector3){
                floor((col.point.x / chunkWidth * map->provincesImg.width)),
                0,
                floor((col.point.z / chunkHeight * map->provincesImg.height))};
            Color col = GetImageColor(map->provincesImg, (int)pixel.x, (int)pixel.z);
            
            player->selectedProvince = GrabProvinceMember(map->provinces, ColorToU32(col));
            
        }
    }
    
    // Zoom
    float mouseWheel = GetMouseWheelMove();
    if(mouseWheel) {
        player->camera.fovy -= (mouseWheel / mouseWheelModifier);
        player->camera.fovy  = Clamp(player->camera.fovy, fovyMinimum, fovyMaximum);
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
}