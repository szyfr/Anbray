///=--------------------=///
//   @Author:  Szyfr      //
//   @Created: 21/12/30   //
//   @Edited:  22/03/12   //
///=--------------------=///



// 
//     Uses:
//   - Map
void CropImageToChunk(Image image, u32 posX, u32 posY, Chunk *chunk) {
    // Copy input image
    Image textureImg = ImageCopy(image);
    
    // Crop copy
    ImageCrop(&textureImg, (Rectangle){ posX, posY, 250, 250});
    
    // Convert to texture
    chunk->texture = LoadTextureFromImage(textureImg);
    chunk->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = chunk->texture;
    
    // Unload
    UnloadImage(textureImg);
}