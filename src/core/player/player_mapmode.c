///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 22/01/05   //
//   @Edited:  22/03/17   //
///=--------------------=///



// Initialize the player data
//     Uses:
//   - Map
void ChangeMapmode(Mapmode mode) {
    // Copy povince map
    Image newImage = ImageCopy(map->provincesImg);
    
    // Edit the copy
    switch(mode) {
        case surface:
        break;
        
        case terrain:
        break;
        
        case nation:
        break;
        
        case race:
        break;
        
        case culture:
        break;
        
        case religion:
        break;
        
    }
    
    //for() {
    //CropImageToChunk(Image image, u32 posX, u32 posY, Chunk *chunk);
    //}
}