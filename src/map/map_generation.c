///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// 
// TODO: Change MapData to not have the maps height and width.
//       They are already pulled from the image file itself
void LoadMapData(Gamestate *gamestate) {
    // Setup base directory location
    char directory[200] = {0};
    strcat(directory,"data/maps/");
    strcat(directory,gamestate->mapName);
    
    // Grab MapData.bin
    char location[200] = {0};
    strcpy(location,directory);
    strcat(location,"/MapData.bin");
    
    // Read MapData.bin
    int read = 0;
    MapData *mapData = (MapData*)LoadFileData(location,&read);
    
    if(!mapData && gamestate->debug) {
        printf("Failed to load MapData.bin\n");
        return;
    }
    
    // Grab Provinces map
    char provincesLoc[200] = {0};
    strcpy(provincesLoc,directory);
    strcat(provincesLoc,"/map/provinces.png");
    gamestate->map.provincesImg = LoadImage(provincesLoc);
    
    // Grab Terrain map
    char terrainLoc[200] = {0};
    strcpy(terrainLoc,directory);
    strcat(terrainLoc,"/map/terrain.png");
    gamestate->map.terrainImg = LoadImage(terrainLoc);
    
    
    /// Generate chunks
    u32 mapWidth   = gamestate->map.provincesImg.width;
    u32 mapHeight  = gamestate->map.provincesImg.height;
    
    // Testing map size
    bool sizeTest = false;
    if(mapWidth%250)  sizeTest = true;
    if(mapHeight%250) sizeTest = true;
    if(sizeTest && gamestate->debug) {
        printf("Province map is incorrect size\n");
        gamestate->state = STATE_MAINMENU;
        gamestate->mmFlags = 0;
    }
    
    // Generating chunks
    u32 chunkTotal = (mapWidth/250) * (mapHeight/250);
    gamestate->map.numChunks = chunkTotal;
    
    Chunk *chunks = (Chunk*)calloc(chunkTotal, sizeof(Chunk));
    
    for(int i = 0; i < chunkTotal; i++) {
        chunks[i].location = (Vector3){
            (float)(i%(mapWidth/250)),
            0.0f,
            (float)(i/(mapWidth/250))};
        
        // || reliefMap
        if(mapData->heightmapDivider) {
            // Grab Heightmap
            char heightmapLoc[200] = {0};
            strcpy(heightmapLoc,directory);
            strcat(heightmapLoc,"/map/height.png");
            Image heightmap = LoadImage(heightmapLoc);
            ImageCrop(&heightmap, (Rectangle){
                          (int)chunks[i].location.x,
                          (int)chunks[i].location.z,
                          250/mapData->heightmapDivider, 250/mapData->heightmapDivider});
            
            // Mesh and Model
            chunks[i].mesh  = GenMeshHeightmap(heightmap, (Vector3){1.0f, 1.0f, 1.0f});
            chunks[i].model = LoadModelFromMesh(chunks[i].mesh);
            
            // Texture
            Image textureImg = ImageCopy(gamestate->map.provincesImg);
            ImageCrop(&textureImg, (Rectangle){
                          (int)chunks[i].location.x,
                          (int)chunks[i].location.z,
                          250, 250});
            chunks[i].texture = LoadTextureFromImage(textureImg);
            chunks[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = chunks[i].texture;
            
            // Unload
            UnloadImage(heightmap);
            UnloadImage(textureImg);
        }
        
        
    }
    
    gamestate->map.chunks = chunks;
    
    UnloadFileData((char*)mapData);
}