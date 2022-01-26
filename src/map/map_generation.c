///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Functions

// Generates the map
void LoadMapData(Gamestate *gamestate) {
    // Setup base directory location
    char directory[200] = {0};
    strcat(directory,"data/maps/");
    strcat(directory,gamestate->mapLocalization[0]);
    
    // Grab Provinces map
    char provincesLoc[200] = {0};
    strcpy(provincesLoc,directory);
    strcat(provincesLoc,"/map/provinces.png");
    if(!FileExists(provincesLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Province map does not exist at (%s)\n", provincesLoc);
        DB_Errorlog(gamestate, str);
        DB_CrashError(gamestate);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Province map loaded from (%s)\n", provincesLoc);
        DB_Errorlog(gamestate, str);
    }
    gamestate->map.provincesImg = LoadImage(provincesLoc);
    
    // Grab Terrain map
    char terrainLoc[200] = {0};
    strcpy(terrainLoc,directory);
    strcat(terrainLoc,"/map/terrain.png");
    if(!FileExists(terrainLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Terrain map does not exist at (%s)\n", terrainLoc);
        DB_Errorlog(gamestate, str);
        DB_CrashError(gamestate);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Terrain map loaded from (%s)\n", terrainLoc);
        DB_Errorlog(gamestate, str);
    }
    gamestate->map.terrainImg = LoadImage(terrainLoc);
    
    /// Generate chunks
    u32 mapWidth   = gamestate->map.provincesImg.width;
    u32 mapHeight  = gamestate->map.provincesImg.height;
    
    // Testing map size
    bool sizeTest = true;
    if(mapWidth%250)  sizeTest = false;
    if(mapHeight%250) sizeTest = false;
    if(!sizeTest) {
        DB_Errorlog(gamestate, "(F): Province map is incorrect size\n");
        DB_CrashError(gamestate);
    }
    
    // Grab Heightmap
    char heightmapLoc[200] = {0};
    strcpy(heightmapLoc,directory);
    strcat(heightmapLoc,"/map/heightmap.png");
    if(!FileExists(heightmapLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Height map does not exist at (%s)\n", heightmapLoc);
        DB_Errorlog(gamestate, str);
        DB_CrashError(gamestate);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Height map loaded from (%s)\n", heightmapLoc);
        DB_Errorlog(gamestate, str);
    }
    Image heightmap = LoadImage(heightmapLoc);
    
    // Pre-calc
    float mapWidthDivided   = 0;
    float mapHeightDivided  = 0;
    float chunkWidthDivided = 0;
    
    switch(gamestate->optionsData->mapLOD) {
        case 1:
        mapWidthDivided   = (float)mapWidth  * 0.20f;
        mapHeightDivided  = (float)mapHeight * 0.20f;
        chunkWidthDivided = 250.0f           * 0.20f;
        break;
        
        case 2:
        mapWidthDivided   = (float)mapWidth  * 0.50f;
        mapHeightDivided  = (float)mapHeight * 0.50f;
        chunkWidthDivided = 250.0f           * 0.50f;
        break;
        
        case 3:
        mapWidthDivided   = (float)mapWidth  * 0.80f;
        mapHeightDivided  = (float)mapHeight * 0.80f;
        chunkWidthDivided = 250.0f           * 0.80f;
        break;
        
        case 4:
        mapWidthDivided   = (float)mapWidth;
        mapHeightDivided  = (float)mapHeight;
        chunkWidthDivided = 250.0f;
        break;
    }
    
    // Resizing heightmap
    ImageResize(&heightmap, mapWidthDivided, mapHeightDivided);
    
    // Generating chunks
    u32 chunkTotal = (mapWidth/250) * (mapHeight/250);
    gamestate->map.numChunks = chunkTotal;
    
    gamestate->map.chunks = (Chunk*)calloc(chunkTotal, sizeof(Chunk));
    if(gamestate->map.chunks == 0) {
        DB_Errorlog(gamestate, "(F): Failed to allocated memory for chunks.\n");
        DB_CrashError(gamestate);
    }
    
    for(int i = 0; i < chunkTotal; i++) {
        if(gamestate->optionsData->mapLOD != 0) {
            // Location
            gamestate->map.chunks[i].location = (Vector3){
                (float)(i%(mapWidth/250)),
                0.0f,
                (float)(i/(mapWidth/250))};
            
            // Cropping heightmap
            int positionX =  (int)(i*chunkWidthDivided) % (int)mapWidthDivided;
            int positionY = ((int)(i*chunkWidthDivided) / (int)mapWidthDivided) * (int)chunkWidthDivided;
            Image croppedHeightmap = ImageCopy(heightmap);
            ImageCrop(&croppedHeightmap, (Rectangle){
                          positionX,
                          positionY,
                          (int)chunkWidthDivided+1, (int)chunkWidthDivided+1});
            
            // Mesh and Model
            gamestate->map.chunks[i].mesh  = GenMeshHeightmap(croppedHeightmap, (Vector3){
                                                                  1.0f+(1.0f/chunkWidthDivided),
                                                                  0.2f,
                                                                  1.0f+(1.0f/chunkWidthDivided)});
            gamestate->map.chunks[i].model = LoadModelFromMesh(gamestate->map.chunks[i].mesh);
            
            // Unload
            UnloadImage(croppedHeightmap);
        } else {
            // Location
            gamestate->map.chunks[i].location = (Vector3){
                (float)(i%(mapWidth/250))+0.5f,
                0.0f,
                (float)(i/(mapWidth/250))+0.5f};
            
            // Generate planes
            gamestate->map.chunks[i].mesh  = GenMeshPlane(1.0f, 1.0f, 1, 1);
            gamestate->map.chunks[i].model = LoadModelFromMesh(gamestate->map.chunks[i].mesh);
        }
        
        // Texture
        Image textureImg = ImageCopy(gamestate->map.provincesImg);
        ImageCrop(&textureImg, (Rectangle){
                      (int)(i*250)%mapWidth,
                      (int)((i*250)/mapWidth)*250,
                      250, 250});
        gamestate->map.chunks[i].texture = LoadTextureFromImage(textureImg);
        gamestate->map.chunks[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = gamestate->map.chunks[i].texture;
        
        // Unload
        UnloadImage(textureImg);
    }
    UnloadImage(heightmap);
    
    DB_Errorlog(gamestate, "(S): Generated map.\n");
}

// Frees the map
void FreeMap(Gamestate *gamestate) {
    if(gamestate->map.chunks == 0) {
        DB_Errorlog(gamestate, "(S): No chunks to free.\n");
        return;
    }
    
    // Free data in chunks
    for(int i = 0; i < gamestate->map.numChunks; i++) {
        UnloadModel(gamestate->map.chunks[i].model);
        UnloadTexture(gamestate->map.chunks[i].texture);
    }
    
    // Free chunks
    free(gamestate->map.chunks);
    gamestate->map.chunks = 0;
    gamestate->map.numChunks = 0;
    
    // Free images
    UnloadImage(gamestate->map.provincesImg);
    UnloadImage(gamestate->map.terrainImg);
    
    DB_Errorlog(gamestate, "(S): Freed Chunks.\n");
}