///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Structures
typedef struct {
    char mapName[32];
    u32 width;
    u32 height;
    float heightmapDivider;
    //  0 - Doesn't even look for Heightmap
    //  1 - Heightmap is equal
} MapData;

typedef struct {
    Vector3 location;
    
    Mesh    mesh;
    Model   model;
    Texture texture;
} Chunk;

typedef struct {
    Image provincesImg;
    Image terrainImg;
    
    u32 numChunks;
    Chunk *chunks;
} Map;