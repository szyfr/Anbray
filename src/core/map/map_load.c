///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/12   //
///=--------------------=///



// Generates the map
//     Uses:
//   - Map
//   - Options
void LoadMapData(void) {
    // Setup base directory location
    char directory[200] = {0};
    strcat(directory,"data/maps/");
    strcat(directory,localization->mapLocalization[0]);
    
    // Grab Provinces map
    char provincesLoc[200] = {0};
    strcpy(provincesLoc,directory);
    strcat(provincesLoc,"/map/provinces.png");
    if(!FileExists(provincesLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Province map does not exist at (%s)\n", provincesLoc);
        DB_CrashError(str);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Province map loaded from (%s)\n", provincesLoc);
        DB_Errorlog(str);
    }
    map->provincesImg = LoadImage(provincesLoc);
    
    // Pre-calc
    map->chunkWidth = map->provincesImg.width / 250;
    map->edge       = map->chunkWidth - 3;
    
    // Grab Terrain map
    char terrainLoc[200] = {0};
    strcpy(terrainLoc, directory);
    strcat(terrainLoc, "/map/terrain.png");
    if(!FileExists(terrainLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Terrain map does not exist at (%s)\n", terrainLoc);
        DB_CrashError(str);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Terrain map loaded from (%s)\n", terrainLoc);
        DB_Errorlog(str);
    }
    map->terrainImg = LoadImage(terrainLoc);
    
    /// Generate chunks
    u32 mapWidth   = map->provincesImg.width;
    u32 mapHeight  = map->provincesImg.height;
    
    // Testing map size
    bool sizeTest = true;
    if(mapWidth%250)  sizeTest = false;
    if(mapHeight%250) sizeTest = false;
    if(!sizeTest) DB_CrashError("(F): Province map is incorrect size\n");
    
    // Grab Heightmap
    char heightmapLoc[200] = {0};
    strcpy(heightmapLoc,directory);
    strcat(heightmapLoc,"/map/heightmap.png");
    if(!FileExists(heightmapLoc)) {
        char str[100] = {0};
        sprintf(str, "(F): Height map does not exist at (%s)\n", heightmapLoc);
        DB_CrashError(str);
    } else {
        char str[100] = {0};
        sprintf(str, "(S): Height map loaded from (%s)\n", heightmapLoc);
        DB_Errorlog(str);
    }
    Image heightmap = LoadImage(heightmapLoc);
    
    // Pre-calc
    float mapWidthDivided   = 0;
    float mapHeightDivided  = 0;
    float chunkWidthDivided = 0;
    
    switch(options->mapLOD) {
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
    map->numChunks = chunkTotal;
    
    map->chunks = (Chunk*)calloc(chunkTotal, sizeof(Chunk));
    if(map->chunks == 0) DB_CrashError("(F): Failed to allocated memory for chunks.\n");
    
    for(int i = 0; i < chunkTotal; i++) {
        if(options->mapLOD != 0) {
            // Location
            map->chunks[i].location = (Vector3){
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
            map->chunks[i].mesh  = GenMeshHeightmap(croppedHeightmap, (Vector3){
                                                        1.0f+(1.0f/chunkWidthDivided),
                                                        0.2f,
                                                        1.0f+(1.0f/chunkWidthDivided)});
            map->chunks[i].model = LoadModelFromMesh(map->chunks[i].mesh);
            
            // Unload
            UnloadImage(croppedHeightmap);
        } else {
            // Location
            map->chunks[i].location = (Vector3){
                (float)(i%(mapWidth/250))+0.5f,
                0.0f,
                (float)(i/(mapWidth/250))+0.5f};
            
            // Generate planes
            map->chunks[i].mesh  = GenMeshPlane(1.0f, 1.0f, 1, 1);
            map->chunks[i].model = LoadModelFromMesh(map->chunks[i].mesh);
        }
        
        CropImageToChunk(map->provincesImg,
                         (int)(i*250)%mapWidth,
                         (int)((i*250)/mapWidth)*250,
                         &map->chunks[i]);
    }
    UnloadImage(heightmap);
    
    CalculateBorder();
    
    DB_Errorlog("(S): Generated map.\n");
}