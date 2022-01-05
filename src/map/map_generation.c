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
    
    gamestate->map.chunks = (Chunk*)calloc(chunkTotal, sizeof(Chunk));
    
    for(int i = 0; i < chunkTotal; i++) {
        // option->heightmapLOD
        // TODO: Map LOD
        //    -0 No detail
        //    -1 Full detail
        //    -2 75%
        //    -3 50%
        //    -4 25%
        // If LOD is lower than map, resize image
        // TODO: 25% LOD has issues lining up the chunks
        if(mapData->heightmapDivider) {
            // Pre-calc
            float mapWidthDivided   = mapWidth * mapData->heightmapDivider;
            float chunkWidthDivided = 250 * mapData->heightmapDivider;
            
            // Location
            gamestate->map.chunks[i].location = (Vector3){
                (float)(i%(mapWidth/250)),
                0.0f,
                (float)(i/(mapWidth/250))};
            
            // Grab Heightmap
            char heightmapLoc[200] = {0};
            strcpy(heightmapLoc,directory);
            // TODO: Change this to just heightmap.png once LOD settings are done
            strcat(heightmapLoc,"/map/heightmapLOD3.png");
            Image heightmap = LoadImage(heightmapLoc);
            int positionX =  (int)(i*chunkWidthDivided) % (int)mapWidthDivided;
            int positionY = ((int)(i*chunkWidthDivided) / (int)mapWidthDivided) * (int)chunkWidthDivided;
            ImageCrop(&heightmap, (Rectangle){
                          positionX,
                          positionY,
                          chunkWidthDivided+1, chunkWidthDivided+1});
            
            // Mesh and Model
            gamestate->map.chunks[i].mesh  = GenMeshHeightmap(heightmap, (Vector3){
                                                                  1.0f+(1.0f/chunkWidthDivided),
                                                                  0.2f,
                                                                  1.0f+(1.0f/chunkWidthDivided)});
            gamestate->map.chunks[i].model = LoadModelFromMesh(gamestate->map.chunks[i].mesh);
            
            // Unload
            UnloadImage(heightmap);
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
    
    UnloadFileData((char*)mapData);
}