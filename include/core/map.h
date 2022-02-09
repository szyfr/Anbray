///=-------------------=///
//    @Author: Szyfr     //
//    @Date: 21/12/30    //
///=-------------------=///



/// Structures
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