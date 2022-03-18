///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/17   //
///=--------------------=///



/// Structures
typedef struct {
    u32 x;
    u32 y;
    u32 z;
} IVector3;

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
    
    ProvinceList *provinces;
    
    // Pre-calculated variables
    u32   chunkWidth;
    float edge;
} Map;