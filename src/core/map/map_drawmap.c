///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/07   //
//   @Edited:  22/03/12   //
///=--------------------=///



//  Draws the map
//     Uses:
//   - Map
void DrawMap(void) {
    DrawChunks(false, map->edge, -map->edge-3);
    DrawChunks(false, 0.0f,       0.0f);
    DrawChunks(true,  2.0f,       map->chunkWidth);
}